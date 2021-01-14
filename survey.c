#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

typedef enum {LITERAL, HEX, DEC, BIN, NIHIL} record_type_t;

typedef struct{
  record_type_t   type;
  char          *literal;
  int             num_digits;
  } record_t;

// Prototypes
void print_record( record_t );


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
              printf("number\n");
              break;
            case 'h':
              if( strlen( buf ) )
                {
                  int value;
                  value = atoi( buf );
                  printf("create hex number with %d digits\n", value);
                  buf[0]= '\0';
                }
              start =false;
              break;
            case 'd':
              if( strlen( buf ) )
                {
                  printf("create dec number \"%s\"\n", buf);
                  buf[0]= '\0';
                }
              start =false;
              break;
            case 'b':
              if( strlen( buf ) )
                {
                  printf("create bin number \"%s\"\n", buf);
                  buf[0]= '\0';
                }
              start =false;
              break;
            case 'n':
              if( strlen( buf ) )
                {
                  printf("create nihil number \"%s\"\n", buf);
                  buf[0]= '\0';
                }
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
      printf("literal\n");
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
