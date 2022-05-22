#include "openssl/crypto.h"
#include "openssl/sha.h"
#include "definitions/hashLib.h"

void calcHash(unsigned char *block, HASH hash)
{
  SHA256((unsigned char *)&block, sizeof(BlocoNaoMinerado), hash);
}

void printHash(HASH hash)
{
  for (int i = 0; i < HASH_SIZE; i++)
  {
    printf("%02x", hash[i]);
  }
  printf("\n");
}