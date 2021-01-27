
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef enum {LITERAL, HEX, DEC, UNSIGNED, BIN, NIHIL} record_type_t;

class Record{
    public:
      Record();

    public:
      string report( string*, size_t* );

    public:
      record_type_t       type;
      std::string         literal;
      int                 num_digits;
  };

// Constructor
Record::Record(){
};

// Report
string Record::report(string *buf, size_t *pos)
  {
    if( type == LITERAL )
      {
        return literal;
      }
    else
      {
        string  sub_buf;
        string  str;
        sub_buf = buf->substr( *pos, num_digits );
        *pos = *pos + num_digits;

        int sub_intv = std::stoi( sub_buf, 0, 2 );
        char converted[65];
        switch( type )
          {
            case HEX:
              sprintf( converted, "%x", sub_intv);
              str = string( converted );
              break;
            case DEC:
              if( sub_buf[0] == '1' )
                sub_intv = sub_intv - ( 1 << num_digits);
            case UNSIGNED:
              sprintf( converted, "%d", sub_intv);
              str = string( converted );
              break;
            case BIN:
              str = sub_buf;
              break;
            case NIHIL:
              str = "";
              break;
            case LITERAL:
              ; // to remove warning when built

          }
        return str;
      }
  };


int make_number_record( string *, record_type_t, vector<Record> * );
int make_literal_record( string *, vector<Record> *);
string toBinary(int);

int main (int argc, char **argv)
  {
  ////////////////////////////////////////////////////////////////////////////////
  // Parsing options
  ////////////////////////////////////////////////////////////////////////////////
    char *cformat = NULL;
    int c;

    opterr = 0;

    while ((c = getopt (argc, argv, "f:")) != -1)
      switch (c)
        {
        case 'f':
          cformat = optarg;
          break;
        case '?':
          if (optopt == 'f')
            fprintf (stderr, "Option -%c requires an argument.\n", optopt);
          else if (isprint (optopt))
            fprintf (stderr, "Unknown option `-%c'.\n", optopt);
          else
            fprintf (stderr,
                     "Unknown option character `\\x%x'.\n",
                     optopt);
          return 1;
        default:
          abort ();
        }


    int non_option_argument = (int)strtol(argv[optind], NULL, 0);

    ////////////////////////////////////////////////////////////////////////////////
    // Analyzing format
    ////////////////////////////////////////////////////////////////////////////////
    string format = string( cformat );
    vector<Record> records;

    size_t  length = format.size();
    bool    start = false;
    string  buf;

    for (size_t i = 0; i < length; i++)
      {
        if ( format[i] == '%' )
          {
            if( !buf.empty() )
              make_literal_record( &buf, &records );
            start = true;
          }
        else if ( start )
          {
            switch( format[i] )
              {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                  buf += format[i];
                  break;
                case 'x':
                case 'h':
                  if( make_number_record( &buf, HEX, &records ) )
                    return 1;
                  start =false;
                  break;
                case 'd':
                case 'i':
                  if( make_number_record( &buf, DEC, &records ) )
                    return 1;
                  start =false;
                  break;
                case 'u':
                  if( make_number_record( &buf, UNSIGNED, &records ) )
                    return 1;
                  start =false;
                  break;
                case 'b':
                  if( make_number_record( &buf, BIN, &records ) )
                    return 1;
                  start =false;
                  break;
                case 'n':
                  if( make_number_record( &buf, NIHIL, &records ) )
                    return 1;
                  start =false;
                  break;
                default:
                  printf("unexpected format\n");
                  return 1;
              }
          }
        else
          {
          buf += format[i];
          }
      }

    if (start)
      {
        printf("non-terminated format");
        return 1;
      }
    else if ( !buf.empty() )
      make_literal_record( &buf, &records );

    // Counting formatted bits
    size_t num_digits=0;
    for( size_t i = 0; i < records.size(); i++ )
      {
        if( records[i].type != LITERAL )
          num_digits += records[i].num_digits;
      }
    string bin_non_option = toBinary( non_option_argument );

    if( num_digits > bin_non_option.size() )
      {
        size_t num_padding_digits;
        num_padding_digits = num_digits - bin_non_option.size();
        for( size_t i = 0; i < num_padding_digits; i++ )
          bin_non_option = "0" + bin_non_option;
      }

////////////////////////////////////////////////////////////////////////////////
// Reporting
////////////////////////////////////////////////////////////////////////////////
    string  str;
    size_t     pos = 0;
    for( size_t i = 0; i < records.size(); i++ )
      str += records[i].report(&bin_non_option, &pos);

    cout << str << endl;
    return 0;
  } // main



int make_number_record( string *buf, record_type_t type, vector<Record> *records )
  {
    if( !buf->empty() )
      {
        int value;
        value = std::stoi( *buf, 0, 10 );
        Record  record;
        record.type = type;
        record.num_digits = value;
        records->push_back( record );
        buf->clear();
      }
    else
      {
        printf("Invalid format\n");
        return 1;
      }
    return 0;
  }

int make_literal_record( string *buf, vector<Record> *records )
  {
    Record  record;
    record.type = LITERAL;
    record.literal = *buf;
    records -> push_back( record );
    buf->clear();
    return 0;
  }

string toBinary(int n)
  {
    std::string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    return r;
  }

