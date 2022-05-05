#include "openssl/crypto.h"
#include "openssl/sha.h"
#include "definitions/hashLib.h"

void calcHash(int val, unsigned char hash[HASH_SIZE])
{
  SHA256((unsigned char *)&val, sizeof(val), hash);
}

void printHash(unsigned char hash[])
{
  for (int i = 0; i < HASH_SIZE; i++)
  {
    printf("%02x", hash[i]);
  }
  printf("\n");
}