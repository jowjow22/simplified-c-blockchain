#include "definitions/threadMine.h" 

void *threadMineration(void *args)
{
  MinerationArgs *minerationArgs = (MinerationArgs *)args;

  BlocoNaoMinerado blockToMine = *(minerationArgs->blockToMine);
  HASH testHash;

  int id =  minerationArgs->threadId;
  unsigned int threadEnd = minerationArgs->rangeEnd, threadStart = minerationArgs->rangeStart; 
  *(minerationArgs->hasBrokenOverflow) = 0;

  for (unsigned int i = threadStart; i < threadEnd+1; i++)
  {
    blockToMine.nonce = i;
    calcHash((unsigned char *)&(blockToMine), testHash);
    if (testHash[0] == 0 && testHash[1] == 0 && testHash[2] == 0 && testHash[3] == 0)
    {
      *(minerationArgs->isMined) = 1;
      cls();
      printf("Block mined!\n");
      printf("Hash: ");
      printHash(testHash);
      minerationArgs->blockToMine->nonce = i;
      if(*(minerationArgs->isMined) == 1)
      {
        pthread_exit(NULL);
      }
    }
    if(i == 4294967295)
    {
      *(minerationArgs->hasBrokenOverflow) = 1;
      pthread_exit(NULL);
    }
    if(*(minerationArgs->isMined) == 1)
    {
      pthread_exit(NULL);
    }
  }
}