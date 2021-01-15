
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef enum {LITERAL, HEX, DEC, BIN, NIHIL} record_type_t;

class Record{
    public:
      Record();

    public:
      record_type_t       type;
      std::string         literal;
      int                 num_digits;
  };

// Constructor
Record::Record(){
};


int make_number_record( string buf, record_type_t type, vector<Record> * );

int main (int argc, char **argv)
  {
  ////////////////////////////////////////////////////////////////////////////////
  // Parsing options
  ////////////////////////////////////////////////////////////////////////////////
    char *cformat = NULL;
    int index;
    int c;

    opterr = 0;

    while ((c = getopt (argc, argv, "c:")) != -1)
      switch (c)
        {
        case 'c':
          cformat = optarg;
          break;
        case '?':
          if (optopt == 'c')
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

    printf ("format = %s\n", cformat);

    for (index = optind; index < argc; index++)
      printf ("Non-option argument %s\n", argv[index]);

    ////////////////////////////////////////////////////////////////////////////////
    // Analyzing format
    ////////////////////////////////////////////////////////////////////////////////
    cout << "Analyzing format\n";
    string format = string( cformat );
    vector<Record> records;

    size_t  length = format.size();
    bool    start = false;
    string  buf;

    for (size_t i = 0; i < length; i++)
      {
        printf("%c:", format[i]);

        if ( format[i] == '%' )
          {
            if( !buf.empty() )
              {
                cout << buf;
                buf.clear();
              }
            printf("start\n");
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
                case 'h':
                  if( make_number_record( buf, HEX, &records ) )
                    return 1;
                  start =false;
                  break;
                case 'd':
                  if( make_number_record( buf, DEC, &records ) )
                    return 1;
                  start =false;
                  break;
                case 'b':
                  if( make_number_record( buf, BIN, &records ) )
                    return 1;
                  start =false;
                  break;
                case 'n':
                  if( make_number_record( buf, NIHIL, &records ) )
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
      {
        cout <<  buf << endl;
        buf.clear();
      }

    cout << records.size() << endl;
  return 0;
  } // main



int make_number_record( string buf, record_type_t type, vector<Record> *records )
  {
    if( !buf.empty() )
      {
        int value;
        value = std::stoi( buf, 0, 10 );
        Record  record;
        record.type = type;
        record.num_digits = value;
        records->push_back( record );
        printf("create number with %d digits\n", value);
        buf.clear();
      }
    else
      {
        printf("Invalid format\n");
        return 1;
      }
    return 0;
  }



