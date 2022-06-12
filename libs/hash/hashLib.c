#include "openssl/crypto.h"
#include "openssl/sha.h"
#include "definitions/hashLib.h"

void calcHash(unsigned char *block, HASH hash)
{
  SHA256(block, sizeof(BlocoNaoMinerado), hash);
}

void *threadMineration1(void *args)
{
  MinerationArgs *minerationArgs = (MinerationArgs *)args;
  BlocoNaoMinerado blockToMine = *(minerationArgs->blockToMine);
  HASH testHash;

  unsigned int maxOfThread = 4294967295;

  for (unsigned int i = 0; i < maxOfThread; i += 2)
  {
    blockToMine.nonce = i;
    calcHash((unsigned char *)&(blockToMine), testHash);
    printf("Thread 1: nonce %d\n", i);
    if (testHash[0] == 0 && testHash[1] == 0 && testHash[2] == 0 && testHash[3] == 0)
    {
      printf("Block mined!\n");
      printf("Hash: ");
      printHash(testHash);
      minerationArgs->blockToMine->nonce = i;
      pthread_exit(NULL);
    }
  }
}
void *threadMineration2(void *args)
{
  MinerationArgs *minerationArgs = (MinerationArgs *)args;
  BlocoNaoMinerado blockToMine = *(minerationArgs->blockToMine);
  HASH testHash;

  unsigned int maxOfThread = 4294967295;

  for (unsigned int i = 1; i < maxOfThread; i += 2)
  {
    blockToMine.nonce = i;
    calcHash((unsigned char *)&(blockToMine), testHash);
    printf("Thread 2: nonce %d\n", i);
    if (testHash[0] == 0 && testHash[1] == 0 && testHash[2] == 0 && testHash[3] == 0)
    {
      printf("Block mined!\n");
      printf("Hash: ");
      printHash(testHash);
      minerationArgs->blockToMine->nonce = i;
      pthread_exit(NULL);
    }
  }
}

BlocoMinerado *MineBlock(BlocoNaoMinerado *blockToMine)
{
  HASH hash;
  calcHash((unsigned char *)blockToMine, hash);
  pthread_t threads[2];
  MinerationArgs *minerationArgs = (MinerationArgs *)malloc(sizeof(MinerationArgs));
  minerationArgs->blockToMine = blockToMine;
  BlocoMinerado *blockMined = (BlocoMinerado *)malloc(sizeof(BlocoMinerado));

 
  pthread_create(&threads[0], NULL, threadMineration1, (void *)minerationArgs);
  pthread_create(&threads[1], NULL, threadMineration2, (void *)minerationArgs);  
  
  for (int i = 0; i < 2; i++)
  {
      pthread_join(threads[i], NULL);
  }

  calcHash((unsigned char *)blockToMine, hash);
  memccpy(blockMined->hash, hash, sizeof(hash), sizeof(hash));
  blockMined->bloco = *blockToMine;

  free(minerationArgs);

  return blockMined;
}