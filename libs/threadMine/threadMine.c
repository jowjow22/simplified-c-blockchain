#include "definitions/threadMine.h"

void *threadMineration(void *args)
{
  MinerationArgs *minerationArgs = (MinerationArgs *)args;

  pthread_mutex_lock(minerationArgs->mutex);
  BlocoNaoMinerado blockToMine = *(minerationArgs->blockToMine);
  HASH testHash;
  int id = minerationArgs->threadId;
  unsigned int threadEnd = minerationArgs->rangeEnd, threadStart = minerationArgs->rangeStart;
  pthread_mutex_unlock(minerationArgs->mutex);
  sleep(1);
  for (unsigned int j = threadStart; j < threadEnd + 1; j++)
  {
    blockToMine.nonce = j;
    calcHash((unsigned char *)&(blockToMine), testHash);
    if (testHash[0] == 0 && testHash[1] == 0 && testHash[2] == 0 && testHash[3] == 0)
    {
      *(minerationArgs->isMined) = 1;
      cls();
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

void *threadMineration3(void *args)
{
  MinerationArgs *minerationArgs = (MinerationArgs *)args;

  pthread_mutex_lock(minerationArgs->mutex);
  BlocoNaoMinerado blockToMine = *(minerationArgs->blockToMine);
  HASH testHash;
  int id = minerationArgs->threadId;
  unsigned int threadEnd = minerationArgs->rangeEnd, threadStart = minerationArgs->rangeStart;
  pthread_mutex_unlock(minerationArgs->mutex);
  sleep(1);
  for (unsigned int j = threadStart; j < threadEnd + 1; j++)
  {
    blockToMine.nonce = j;
    calcHash((unsigned char *)&(blockToMine), testHash);
    if (testHash[0] == 0 && testHash[1] == 0 && testHash[2] == 0)
    {
      *(minerationArgs->isMined) = 1;
      cls();
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