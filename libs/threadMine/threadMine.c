#include "definitions/threadMine.h"

void *threadMinerationComplexity4(void *args)
{
  MinerationArgs *minerationArgs = (MinerationArgs *)args;

  BlocoNaoMinerado blockToMine = *(minerationArgs->blockToMine);
  HASH testHash;
  for (unsigned int j = minerationArgs->rangeStart; j < 4294967294; j += 2)
  {
    blockToMine.nonce = j;
    calcHash((unsigned char *)&(blockToMine), testHash);
    if (testHash[0] == 0 && testHash[1] == 0 && testHash[2] == 0 && testHash[3] == 0)
    {
      *(minerationArgs->isMined) = 1;
      printf("Block mined!\n");
      printf("Hash: ");
      printHash(testHash);
      minerationArgs->blockToMine->nonce = j;
      if (*(minerationArgs->isMined) == 1)
      {
        pthread_exit(NULL);
      }
    }
    if (*(minerationArgs->isMined) == 1)
    {
      pthread_exit(NULL);
    }
  }
}

void *threadMinerationComplexity3(void *args)
{
  MinerationArgs *minerationArgs = (MinerationArgs *)args;

  BlocoNaoMinerado blockToMine = *(minerationArgs->blockToMine);
  HASH testHash;
  int id = minerationArgs->threadId;
  sleep(1);
  for (unsigned int j = minerationArgs->rangeStart; j < 4294967295; j += 2)
  {
    blockToMine.nonce = j;
    calcHash((unsigned char *)&(blockToMine), testHash);
    if (testHash[0] == 0 && testHash[1] == 0 && testHash[2] == 0)
    {
      *(minerationArgs->isMined) = 1;
      printf("Block mined!\n");
      printf("Hash: ");
      printHash(testHash);
      minerationArgs->blockToMine->nonce = j;
      if (*(minerationArgs->isMined) == 1)
      {
        pthread_exit(NULL);
      }
    }
    if (*(minerationArgs->isMined) == 1)
    {
      pthread_exit(NULL);
    }
  }
}