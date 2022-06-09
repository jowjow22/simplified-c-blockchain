#include "openssl/crypto.h"
#include "openssl/sha.h"
#include "definitions/hashLib.h"

void calcHash(unsigned char *block, HASH hash)
{
  SHA256(block, sizeof(BlocoNaoMinerado), hash);
}

BlocoMinerado *MineBlock(BlocoNaoMinerado *blockToMine)
{
  HASH hash;
  calcHash((unsigned char *)blockToMine, hash);
  int isMined = 0;
  do
  {
    if (hash[0] == 0 && hash[1] == 0 && hash[2] == 0 && hash[3])
    {
      isMined = 1;
    }
    else
    {
      blockToMine->nonce += 1;
      printf("Nonce: %d\n", blockToMine->nonce);
      calcHash((unsigned char *)blockToMine, hash);
    }
  } while (isMined == 0);
  BlocoMinerado *minedBlock = NewMinedBlock();
  minedBlock->bloco = *blockToMine;
  memcpy(minedBlock->hash, hash, sizeof(minedBlock->hash));

  return minedBlock;
}