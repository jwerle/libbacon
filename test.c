
/**
 * `test.c' - libbacon
 *
 * copyright (c) 2014 joseph werle <joseph.werle@gmail.com>
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ok.h>
#include <bacon.h>

#define test(name, e) {                   \
  if (!(e)) {                             \
    fprintf(stderr, "failed: %s\n", # e); \
    return 1;                             \
  } else {                                \
    ok(name);                             \
  }                                       \
}

#define texpect(fn, a, b) {              \
  printf("(%s): ", # fn);                \
  test(a, 0 == strcmp(fn(a, ALPHA), b)); \
}

static int
test_encode ();

static int
test_decode ();

int
main (void) {
  test("encode suite", 0 == test_encode());
  test("decode suite", 0 == test_decode());
  return 0;
}

static int
test_encode () {
#define ALPHA NULL

  texpect(bacon_encode,
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
      "AAAAAAAAABAAABAAAABBAABAAAABABAABBAAABBBABAAAABAAAABAABABABAABABBABBAAAB"
      "BABABBBAABBBBBAAAABAAABBAABABAABBBAABBBABAABABABBABBABABBB"
  );

  texpect(bacon_encode,
      "abcdefghijklmnopqrstuvwxyz",
      "AAAAAAAAABAAABAAAABBAABAAAABABAABBAAABBBABAAAABAAAABAABABABAABABBABBAAAB"
      "BABABBBAABBBBBAAAABAAABBAABABAABBBAABBBABAABABABBABBABABBB"
  );

  texpect(bacon_encode,
      "foo bar",
      "AABABABBABABBAB AAAABAAAAABAAAA"
  );

  texpect(bacon_encode,
      "FoO BaR",
      "AABABABBABABBAB AAAABAAAAABAAAA"
  );

  texpect(bacon_encode,
      "'!\"#$%&\'()*+,-./0123456789:;<=>?@[\\]^_`{|}~",
      ""
  );

  texpect(bacon_encode,
      "foo!\"#$%&\'()*+,-./0123456789:;<=>?@[\\]^_`{|}~bar",
      "AABABABBABABBAB AAAABAAAAABAAAA"
  );

#undef ALPHA

#define ALPHA "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

  texpect(bacon_encode,
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
      "AAAAAAAAABAAABAAAABBAABAAAABABAABBAAABBBABAAAABAABABABAABABBABBAAABBABAB"
      "BBAABBBBBAAAABAAABBAABABAABBBABAABABABBABBABABBBBBAAABBAAB"
  );

#undef ALPHA

#define ALPHA "abcdefghijklmnopqrstuvwxyz"

  texpect(bacon_encode,
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
      "AAAAAAAAABAAABAAAABBAABAAAABABAABBAAABBBABAAAABAABABABAABABBABBAAABBABAB"
      "BBAABBBBBAAAABAAABBAABABAABBBABAABABABBABBABABBBBBAAABBAAB"
  );

#undef ALPHA

  return 0;
}

static int
test_decode () {
  return 0;
}
