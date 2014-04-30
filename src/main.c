
/**
 * `main.c' - libbacon
 *
 * copyright (c) 2014 joseph werle <joseph.werle@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <bacon.h>

static void
usage () {
  fprintf(stderr, "usage: bacon [-hV] <command> [alpha]\n");
}

static void
help () {
  fprintf(stderr, "\ncommands:\n");
  fprintf(stderr, "\n   encode     Encode stdin stream");
  fprintf(stderr, "\n   decode     Decode stdin stream");
  fprintf(stderr, "\n");
}

static char *
read_stdin () {
  size_t bsize = 1024;
  size_t size = 1;
  char buf[bsize];
  char *res = (char *) malloc(sizeof(char) * bsize);
  char *tmp = NULL;

  // memory issue
  if (NULL == res) { return NULL; }

  // cap
  res[0] = '\0';

  // read
  if (NULL != fgets(buf, bsize, stdin)) {
    // store
    tmp = res;
    // resize
    size += (size_t) strlen(buf);
    // realloc
    res = (char *) realloc(res, size);

    // memory issues
    if (NULL == res) {
      free(tmp);
      return NULL;
    }

    // yield
    strcat(res, buf);

    return res;
  }

  free(res);

  return NULL;
}

int
main (int argc, char **argv) {
  char *buf = NULL;
  char *alpha = NULL;
  char *out = NULL;

  // emit usage with empty arguments
  if (1 == argc) { return usage(), 1; }

  // parse opts
  {
    char *opt = NULL;
    char tmp = 0;

    opt = *argv++; // unused

    while ((opt = *argv++)) {

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
            goto decode;
          }

          // encode
          if (0 == strcmp("encode", opt)) {
            goto encode;
          }

          // error
          fprintf(stderr, "unknown command: `%s'\n", opt);
          usage();
        }
      }

    }
  }

#define op(name) {                               \
  alpha = *argv++;                               \
  buf = read_stdin();                            \
  if (NULL == buf) { return 1; }                 \
  out = bacon_ ## name(buf, alpha);              \
  printf("%s\n", out);                           \
  do {                                           \
    buf = read_stdin();                          \
    if (NULL == buf) { break; }                  \
    out = bacon_ ## name(buf, alpha);            \
    printf("%s\n", out);                         \
  } while (NULL != buf);                         \
}

decode:
  {
    if (1 == isatty(0)) { return 1; }
    else if (ferror(stdin)) { return 1; }
    else { op(decode); }
    return 0;
  }

encode:
  {
    if (1 == isatty(0)) { return 1; }
    else if (ferror(stdin)) { return 1; }
    else { op(encode); }
    return 0;
  }

#undef op
}
