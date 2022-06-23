#include "definitions/hashLib.h"

void calcHash(unsigned char *block, HASH hash)
{
  SHA256(block, sizeof(BlocoNaoMinerado), hash);
}

int threadWhoFounded = 10000;

void *threadMineration(void *args)
{
  MinerationArgs *minerationArgs = (MinerationArgs *)args;

  BlocoNaoMinerado blockToMine = *(minerationArgs->blockToMine);
  HASH testHash;
  int id = minerationArgs->threadId;
  unsigned int threadEnd = minerationArgs->rangeEnd, threadStart = minerationArgs->rangeStart;
  sleep(1);
  for (unsigned int j = threadStart; j < threadEnd; j++)
  {
    if (threadWhoFounded <= id)
    {
      pthread_exit(NULL);
    }
    blockToMine.nonce = j;
    calcHash((unsigned char *)&(blockToMine), testHash);
    if (testHash[0] == 0 && testHash[1] == 0 && testHash[2] == 0 && testHash[3] == 0)
    {
      threadWhoFounded = id;
      if (minerationArgs->blockToMine->nonce == 0)
      {

        minerationArgs->blockToMine->nonce = j;
      }
      if (minerationArgs->blockToMine->nonce >= j)
      {

        minerationArgs->blockToMine->nonce = j;
      }
    }
  }
  pthread_exit(NULL);
}

void *threadMineration3(void *args)
{
  MinerationArgs *minerationArgs = (MinerationArgs *)args;

  BlocoNaoMinerado blockToMine = *(minerationArgs->blockToMine);
  HASH testHash;
  int id = minerationArgs->threadId;
  unsigned int threadEnd = minerationArgs->rangeEnd, threadStart = minerationArgs->rangeStart;
  sleep(1);
  for (unsigned int j = threadStart; j < threadEnd; j++)
  {
    if (threadWhoFounded <= id)
    {
      pthread_exit(NULL);
    }
    blockToMine.nonce = j;

    calcHash((unsigned char *)&blockToMine, testHash);

    if (testHash[0] == 0 && testHash[1] == 0 && testHash[2] == 0)
    {

      threadWhoFounded = id;
      if (minerationArgs->blockToMine->nonce == 0)
      {
        minerationArgs->blockToMine->nonce = blockToMine.nonce;
      }

      if (minerationArgs->blockToMine->nonce >= j)
      {
        minerationArgs->blockToMine->nonce = blockToMine.nonce;
      }
    }
  }
  pthread_exit(NULL);
}

BlocoMinerado *MineBlock(BlocoNaoMinerado *blockToMine)
{
  HASH TestHash, hash;
  pthread_t threads[5];
  for (int i = 0; i < 5; i++)
  {

    MinerationArgs *minerationArgs = (MinerationArgs *)malloc(sizeof(MinerationArgs));
    blockToMine->nonce = 0;
    minerationArgs->blockToMine = blockToMine;

    minerationArgs->threadId = i;
    minerationArgs->rangeStart = (unsigned int)i * 858993459;
    minerationArgs->rangeEnd = (unsigned int)(i + 1) * 858993459;
    pthread_create(&(threads[i]), NULL, threadMineration, (void *)minerationArgs);
  }
  for (int i = 0; i < 5; i++)
  {
    pthread_join(threads[i], NULL);
  }
  calcHash((unsigned char *)blockToMine, TestHash);
  if (TestHash[0] != 0 || TestHash[1] != 0 || TestHash[2] != 0 || TestHash[3] != 0)
  {
    printf("Block failed mine!\n");
    printf("reducing complexity...\n");

    for (int i = 0; i < 5; i++)
    {
      HASH TestHash, hash;

      MinerationArgs *minerationArgs = (MinerationArgs *)malloc(sizeof(MinerationArgs));
      blockToMine->nonce = 0;
      minerationArgs->blockToMine = blockToMine;

      minerationArgs->threadId = i;
      minerationArgs->rangeStart = (unsigned int)i * 858993459;
      minerationArgs->rangeEnd = (unsigned int)(i + 1) * 858993459;
      pthread_create(&(threads[i]), NULL, threadMineration3, (void *)minerationArgs);
    }
    for (int i = 0; i < 5; i++)
    {
      pthread_join(threads[i], NULL);
    }
  }
  printf("Nonce: %u\n", blockToMine->nonce);
  calcHash((unsigned char *)blockToMine, hash);
  BlocoMinerado *blockMined = (BlocoMinerado *)malloc(sizeof(BlocoMinerado));
  memccpy(blockMined->hash, hash, sizeof(blockMined->hash), sizeof(blockMined->hash));
  blockMined->bloco = *blockToMine;

  printf("Block mined!\n");
  threadWhoFounded = 10000;
  return blockMined;
}