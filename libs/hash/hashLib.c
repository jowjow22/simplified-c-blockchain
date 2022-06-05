#include "openssl/crypto.h"
#include "openssl/sha.h"
#include "definitions/hashLib.h"

void calcHash(unsigned char *block, HASH hash)
{
  SHA256((unsigned char *)block, sizeof(BlocoNaoMinerado), hash);
}

void printHash(HASH hash)
{
  for (int i = 0; i < HASH_SIZE; i++)
  {
    printf("%02x", hash[i]);
  }
  printf("\n");
}

BlocoMinerado *mineBlock(BlocoNaoMinerado *bloco)
{
  int isMined = 0;
  HASH hash;

  calcHash((unsigned char *)bloco, hash);

  do
  {
    if (hash[0] == 0 && hash[1] == 0)
    {
      isMined = 1;
    }
    else
    {
      bloco->nonce++;
      calcHash((unsigned char *)bloco, hash);
    }
  } while (isMined == 0);
  printf("\nBlock mined!\n");
  printHash(hash);
  return createNewMinedBlock(*bloco, hash);
}