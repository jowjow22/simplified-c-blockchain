#include "definitions/hashLib.h"

void calcHash(unsigned char *block, HASH hash)
{
  SHA256(block, sizeof(BlocoNaoMinerado), hash);
}

BlocoMinerado *MineBlock(BlocoNaoMinerado *blockToMine)
{
  HASH hash;
  MinerationArgs *minerationArgsEven = (MinerationArgs *)malloc(sizeof(MinerationArgs));
  MinerationArgs *minerationArgsOdd = (MinerationArgs *)malloc(sizeof(MinerationArgs));

  minerationArgsEven->blockToMine = blockToMine;
  int *isMined = (int *)malloc(sizeof(int));
  *isMined = 0;
  minerationArgsEven->isMined = isMined;
  minerationArgsOdd->isMined = isMined;

  minerationArgsOdd->blockToMine = blockToMine;

  minerationArgsEven->rangeStart = 0;
  minerationArgsOdd->rangeStart = 1;

  minerationArgsEven->threadId = 0;
  minerationArgsOdd->threadId = 1;

  BlocoMinerado *blockMined = (BlocoMinerado *)malloc(sizeof(BlocoMinerado));

  int hasBrokenOverflow = 0;

  do
  {
    if (hasBrokenOverflow == 0)
    {

      pthread_t threadEven;
      pthread_t threadOdd;
      pthread_create(&threadEven, NULL, threadMinerationComplexity4, (void *)minerationArgsEven);
      pthread_create(&threadOdd, NULL, threadMinerationComplexity4, (void *)minerationArgsOdd);
      pthread_join(threadEven, NULL);
      pthread_join(threadOdd, NULL);
      calcHash((unsigned char *)blockToMine, hash);
      if ((hash[0] != 0 || hash[1] != 0 || hash[2] != 0 || hash[3] != 0))
      {
        printf("Block failed mine!\n");
        hasBrokenOverflow = 1;
        printf("Retrying...\n");
      }
      else
      {
        printf("Block mined!\n");
      }
    }
    else
    {
      pthread_t threadEven;
      pthread_t threadOdd;
      pthread_create(&threadEven, NULL, threadMinerationComplexity3, (void *)minerationArgsEven);
      pthread_create(&threadOdd, NULL, threadMinerationComplexity3, (void *)minerationArgsOdd);
      pthread_join(threadEven, NULL);
      pthread_join(threadOdd, NULL);
      calcHash((unsigned char *)blockToMine, hash);
      if ((hash[0] != 0 || hash[1] != 0 || hash[2] != 0))
      {
        printf("Block failed mine!\n");
        hasBrokenOverflow = 1;
        printf("Retrying...\n");
      }
      else
      {
        hasBrokenOverflow = 0;
        printf("Block mined!\n");
      }
    }
    calcHash((unsigned char *)blockToMine, hash);
  } while (hasBrokenOverflow == 1);

  calcHash((unsigned char *)blockToMine, hash);
  memccpy(blockMined->hash, hash, sizeof(hash), sizeof(hash));
  blockMined->bloco = *blockToMine;

  free(minerationArgsEven);
  free(minerationArgsOdd);

  return blockMined;
}