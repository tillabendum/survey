
#include "main.h"
#include <unistd.h>
#include <iostream>

using namespace std;

int main (int argc, char **argv)
  {
  ////////////////////////////////////////////////////////////////////////////////
  // Parsing options
  ////////////////////////////////////////////////////////////////////////////////
    int aflag = 0;
    int bflag = 0;
    char *cformat = NULL;
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

    printf ("%d%d format = %s\n", aflag, bflag, cformat);

    for (index = optind; index < argc; index++)
      printf ("Non-option argument %s\n", argv[index]);

    ////////////////////////////////////////////////////////////////////////////////
    // Analyzing format
    ////////////////////////////////////////////////////////////////////////////////
    cout << "Analyzing format\n";
    string format = string( cformat );




    cout << format << endl;



  return 0;
  }
