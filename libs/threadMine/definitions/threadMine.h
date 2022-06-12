#ifndef THREADMINE_H
#define THREADMINE_H

#include "../../blocks/blocks.c"

typedef struct MinerationArgs
{
  BlocoNaoMinerado *blockToMine;
  unsigned int rangeStart;
  unsigned int rangeEnd;
  int threadId;
  int *isMined;
  int *hasBrokenOverflow;
} MinerationArgs;

void calcHash(unsigned char *block, HASH hash);

void *threadMineration(void *args);

#endif