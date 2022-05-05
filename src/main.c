#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "openssl/crypto.h"
#include "openssl/sha.h"
#include "../libs/mtwister/definitions/mtwister.h"
#include "../libs/blocks/definitions/blocks.h"
#include "../libs/hash/definitions/hashLib.h"
#include "../libs/hash/hashLib.c"

int main()
{
  // testing
  int k = 13;
  HASH hash;
  calcHash(k, hash);
  printHash(hash);
  return 0;
}