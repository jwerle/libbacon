
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <bacon.h>

char *
bacon_encode (const char *src, const char *alpha) {
  char *enc = (char *) malloc(sizeof(char));
  char ch = 0;
  size_t size = 0;
  size_t len = (size_t) strlen(src);
  size_t alen = 0;
  int custom = 0;
  int i = -1; // source index
  int sep = 0;
  int idx = -1;

  // use default
  if (NULL == alpha) {
    alpha = BACON_ALPHA;
  } else { custom = 1; }

  alen = (size_t) strlen(alpha);

  while ((++i) < len) {

    ch = toupper(src[i]);

    // apply char replacements
    // if not custom alpha
    if (0 == custom) {
      switch (ch) {
        case 'J': ch = 'I'; break;
        case 'V': ch = 'U'; break;
      }
    }

    // search alphabet for index
    {
      char c = 0;

      // reset
      idx = -1;

      // search
      while ((++idx) < alen) {
        c = toupper(alpha[idx]);
        if (ch == c) { goto found; }
      }

      // not found
      idx = -1;
    }
found:

    // found
    if (idx > -1) {
      // needs space
      if (1 == sep) {
        enc[size++] = ' ';
      }

      // encode
      enc[size++] = idx & 0x10 ? 'B' : 'A';
      enc[size++] = idx & 0x08 ? 'B' : 'A';
      enc[size++] = idx & 0x04 ? 'B' : 'A';
      enc[size++] = idx & 0x02 ? 'B' : 'A';
      enc[size++] = idx & 0x01 ? 'B' : 'A';

      // reset
      sep = 0;
    } else if (i > 0) {
      // need space expect on first char
      sep = 1;
    }
  }

  // cap
  enc[size] = '\0';

  return enc;
}
