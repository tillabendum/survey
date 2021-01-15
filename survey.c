#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

const int MAX_NUM_RECORDS   = 100;
const int MAX_LITERAL_SIZE  = 100;

typedef enum {LITERAL, HEX, DEC, BIN, NIHIL} record_type_t;

typedef struct{
  record_type_t   type;
  char          *literal;
  int             num_digits;
  } record_t;

// Prototypes
void print_record( record_t );
int  make_number_record(char *, record_type_t, record_t *, int *);



int main (int argc, char **argv)
{
////////////////////////////////////////////////////////////////////////////////
// Parsing options
////////////////////////////////////////////////////////////////////////////////
  int aflag = 0;
  int bflag = 0;
  char *format = NULL;
  int index;
  int c;
  record_t records[MAX_NUM_RECORDS];
  int records_pointer = 0;

  opterr = 0;

  while ((c = getopt (argc, argv, "abc:")) != -1)
    switch (c)
      {
      case 'a':
        aflag = 1;
        break;
      case 'b':
        bflag = 1;
        break;
      case 'c':
        format = optarg;
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

  printf ("%d%d format = %s\n", aflag, bflag, format);

  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);

////////////////////////////////////////////////////////////////////////////////
// Analyzing format
////////////////////////////////////////////////////////////////////////////////

printf("Analyzing format:\n");
size_t length = strlen( format );

bool  start = false;
char buf[length + 1];
buf[0] = '\0';
for (size_t i = 0; i < length; i++)
  {
    printf("%c:", format[i]);

    if ( format[i] == '%' )
      {
        if( strlen( buf ) )
          {
            printf("create literal \"%s\"", buf);
            buf[0]= '\0';
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
              strncat(buf, format + i, 1);
              break;
            case 'h':
              if( make_number_record( buf, HEX, records, &records_pointer ) )
                return 1;
              start =false;
              break;
            case 'd':
              if( make_number_record( buf, DEC, records, &records_pointer ) )
                return 1;
              start =false;
              break;
            case 'b':
              if( make_number_record( buf, BIN, records, &records_pointer ) )
                return 1;
              start =false;
              break;
            case 'n':
              if( make_number_record( buf, NIHIL, records, &records_pointer ) )
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
      strncat(buf, format + i, 1);
      }
  }

if (start)
  {
    printf("non-terminated format");
    return 1;
  }
else if ( strlen( buf ) )
  {
    printf("create literal \"%s\"\n", buf);
    buf[0]= '\0';
  }


  printf("%d", records_pointer);

  return 0;
}



void print_record( record_t record)
  {
    if( record.type == LITERAL )
      printf("Literal:");
    else if ( record.type == HEX )
      printf("HEX:");
    else
      printf("UNKNOWN");
  }


int make_number_record(char *buf, record_type_t type, record_t* records, int *records_pointer )
  {
    if( strlen( buf ) )
      {
        int value;
        value = atoi( buf );
        if(*records_pointer < MAX_NUM_RECORDS)
          {
            record_t  record;
            record.type = type;
            record.num_digits = value;
            records[*records_pointer]= record;
            *records_pointer = *records_pointer + 1;
          }
        else
          {
            printf("records overflow");
            return 1;
          }

        printf("create number with %d digits\n", value);
        buf[0]= '\0';
      }
    else
      {
        printf("Invalid format\n");
        return 1;
      }
    return 0;
  }
/*
int make_word_record(char *buf, record_t* records, int *records_pointer )
  {
    if( strlen( buf ) )
      {
        int value;
        value = atoi( buf );
        if(*records_pointer < MAX_NUM_RECORDS)
          {
            record_t  record;
            record.type = LITERAL;
            strcpy( record.literal, buf );
            records[*records_pointer]= record;
            *records_pointer = *records_pointer + 1;
          }
        else
          {
            printf("records overflow");
            return 1;
          }

        printf("create number with %d digits\n", value);
        buf[0]= '\0';
      }
    else
      {
        printf("Invalid format\n");
        return 1;
      }
    return 0;
  }

*/
