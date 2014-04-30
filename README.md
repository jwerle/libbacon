libbacon
========

A C implementation of the Baconian Cipher ! BACON

Inspired by [bacon-cipher](https://github.com/mathiasbynens/bacon-cipher) !

## install

[clib](https://github.com/clibs/clib):

```sh
$ clib install jwerle/libbacon
```

source:

```sh
$ git clone git@github.com:jwerle/libbacon.git
$ cd libbacon
$ make
$ make install
```

## usage

**Command line utility:**

*encode:*

```sh
$ echo abc | bacon encode
AAAAAAAAABAAABA
```

```sh
$ { echo abc && echo def && echo ghi; }  | bacon encode
AAAAAAAAABAAABA
AAABBAABAAAABAB
AABBAAABBBABAAA
```

*decode:*

```sh
$ echo AAAAAAAAABAAABA | bacon decode
ABC
```

```sh
$ { echo 'AAAAAAAAABAAABA' && echo 'AAABBAABAAAABAB' && echo
'AABBAAABBBABAAA'; } | bacon decode
ABC
DEF
GHI
```

**C Library:**

*encode:*

```c
#include <bacon.h>
#include <stdio.h>

int
main (void) {
  printf("%s\n", bacon_encode("foo bar", NULL));
  return 0;
}
```

...yields:

```
AABABABBABABBAB AAAABAAAAABAAAA
```

*decode:*

```c
#include <bacon.h>
#include <stdio.h>

int
main (void) {
  char *buf = "AA AA AA AAA BAAAB AAAABBA ABAAA.ABAB#AABBA@AABB+BABAA/AABAAAABAABABABAA"
    "B_ABBABBAAABBABABBB AABBBBBAAAABAAABBAABABAAB<BBAABBBABAABABABBA>BBABABB"
    "B";

  printf("%s\n", bacon_decode(buf, NULL));
  return 0;
}
```

...yields:

```
A B CD E F G H IIKL MNO PQRST UUWX YZ
```

## api

See [bacon.h](https://github.com/jwerle/libbacon/blob/master/include/bacon.h)

## license

MIT
