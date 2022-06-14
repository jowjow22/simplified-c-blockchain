#include "definitions/hashLib.h"

void calcHash(unsigned char *block, HASH hash)
{
  SHA256(block, sizeof(BlocoNaoMinerado), hash);
}

BlocoMinerado *MineBlock(BlocoNaoMinerado *blockToMine)
{
  HASH hash;
  calcHash((unsigned char *)blockToMine, hash);
  MinerationArgs *minerationArgs = (MinerationArgs *)malloc(sizeof(MinerationArgs));
  minerationArgs->blockToMine = blockToMine;
  BlocoMinerado *blockMined = (BlocoMinerado *)malloc(sizeof(BlocoMinerado));
  minerationArgs->isMined = (int *)malloc(sizeof(int));
  *(minerationArgs->isMined) = 0;

  int hasBrokenOverflow = 0;

  pthread_t *threads = NULL;

  int i = 0;
  
    threads = malloc(sizeof(pthread_t) * 15);
    pthread_mutex_t mutex;
    minerationArgs->mutex = &mutex;
    pthread_mutex_init(&mutex, NULL);
    while (i < 15)
    {
      pthread_create(&(threads[i]), NULL, threadMineration, (void *)minerationArgs);
      minerationArgs->threadId = i;
      minerationArgs->rangeStart = (unsigned int)i * 286331153;
      minerationArgs->rangeEnd = (unsigned int)(i + 1) * 286331153;
      i++;
    }
    i = 0;
    while (i < 15)
    {
      pthread_join(threads[i], NULL);
      i++;
    }
    calcHash((unsigned char *)blockToMine, hash);
    if (hash[0] != 0 || hash[1] != 0 || hash[2] != 0 || hash[3] != 0)
    {
      printf("Block failed mine!\n");
      printf("Retrying...\n");
      free(threads);
      threads = NULL;
      free(minerationArgs);
      threads = malloc(sizeof(pthread_t) * 15);
      minerationArgs = (MinerationArgs *)malloc(sizeof(MinerationArgs));
      minerationArgs->blockToMine = blockToMine;
      i = 0;
      while (i < 15)
    {
      pthread_create(&(threads[i]), NULL, threadMineration3, (void *)minerationArgs);
      minerationArgs->threadId = i;
      minerationArgs->rangeStart = (unsigned int)i * 286331153;
      minerationArgs->rangeEnd = (unsigned int)(i + 1) * 286331153;
      i++;
    }
    i = 0;
    while (i < 15)
    {
      pthread_join(threads[i], NULL);
      i++;
    }
    }
    else
    {
      hasBrokenOverflow = 0;
      cls();
      printf("Block mined!\n");
    }
    pthread_mutex_destroy(&mutex);


  calcHash((unsigned char *)blockToMine, hash);
  memccpy(blockMined->hash, hash, sizeof(hash), sizeof(hash));
  blockMined->bloco = *blockToMine;

  free(minerationArgs);

  return blockMined;
}