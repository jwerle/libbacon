
/**
 * `main.c' - libbacon
 *
 * copyright (c) 2014 joseph werle <joseph.werle@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bacon.h>

static void
usage () {
  fprintf(stderr, "usage: bacon [-hV] <action>\n");
}

static void
help () {

}

int
main (int argc, char **argv) {
  // emit usage with empty arguments
  if (1 == argc) { return usage(), 1; }

  // parse opts
  {
    char *opt = NULL;
    char tmp = 0;
    int i = 1;

    while ((opt = argv[i++])) {

      // flags
      if ('-' == opt[0]) {
        tmp = *opt++; // unused
        switch (*opt++) {
          case 'h':
            return usage(), help(), 0;

          case 'V':
            fprintf(stderr, "%s\n", BACON_VERSION);
            return 0;
        }
      } else {

        // actions
        {
          // decode
          if (0 == strcmp("decode", opt)) {

            break;
          }

          // encode
          if (0 == strcmp("encode", opt)) {
            break;
          }

          // error
          fprintf(stderr, "unknown command: `%s'\n", opt);
          usage();
        }
      }

    }
  }

  return 0;
}
