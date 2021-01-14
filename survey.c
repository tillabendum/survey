#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

typedef struct{
  enum {LITERAL, HEX, DEC, BIN, NIHIL} type;
  char *literal;
  int  num_digits;
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
for (size_t i = 0; i < length; i++)
  {
    printf("%c:", format[i]);

    if ( format[i] == '%' )
      {
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
              printf("number\n");
              break;
            case 'h':
              printf("hex\n");
              start =false;
              break;
            case 'd':
              printf("dec\n");
              start =false;
              break;
            case 'b':
              printf("bin\n");
              start =false;
              break;
            case 'n':
              printf("nihil\n");
              start =false;
              break;
            default:
              printf("unexpected format\n");
              return 1;
          }
      }
    else
      {
      printf("literal\n");
      }
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
