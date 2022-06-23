#ifndef HASHLIB_H
#define HASHLIB_H

typedef struct MinerationArgs
{
  BlocoNaoMinerado *blockToMine;
  unsigned int rangeStart;
  unsigned int rangeEnd;
  int threadId;
} MinerationArgs;

void calcHash(unsigned char *block, HASH hash);

void *threadMineration(void *args);

void *threadMineration3(void *args);

void printHash(HASH hash);

BlocoMinerado *MineBlock(BlocoNaoMinerado *blockToMine);

#endif