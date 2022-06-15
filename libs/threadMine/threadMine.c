#include "definitions/threadMine.h"

void *threadMineration(void *args)
{
  MinerationArgs *minerationArgs = (MinerationArgs *)args;

  BlocoNaoMinerado blockToMine = *(minerationArgs->blockToMine);
  HASH testHash;
  int id = minerationArgs->threadId;
  unsigned int threadEnd = minerationArgs->rangeEnd, threadStart = minerationArgs->rangeStart;
  sleep(1);
  for (unsigned int j = threadStart; j < threadEnd + 1; j++)
  {
    blockToMine.nonce = j;
    calcHash((unsigned char *)&(blockToMine), testHash);
    if (testHash[0] == 0 && testHash[1] == 0 && testHash[2] == 0 && testHash[3] == 0)
    {
      *(minerationArgs->isMined) = 1;
      cls();
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

  BlocoNaoMinerado blockToMine = *(minerationArgs->blockToMine);
  HASH testHash;
  int id = minerationArgs->threadId;
  unsigned int threadEnd = minerationArgs->rangeEnd, threadStart = minerationArgs->rangeStart;
  sleep(1);
  for (unsigned int j = threadStart; j < threadEnd + 1; j++)
  {
    blockToMine.nonce = j;
    calcHash((unsigned char *)&(blockToMine), testHash);
    if (testHash[0] == 0 && testHash[1] == 0 && testHash[2] == 0)
    {
      *(minerationArgs->isMined) = 1;
      cls();
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