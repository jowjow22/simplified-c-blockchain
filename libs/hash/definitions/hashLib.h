#ifndef HASHLIB_H
#define HASHLIB_H

typedef struct MinerationArgs
{
  BlocoNaoMinerado *blockToMine;
  BlocoMinerado *minedBlock;
  HASH hash;
  int isMined;
  int threadId;
  pthread_mutex_t mutex;
} MinerationArgs;

void calcHash(unsigned char *block, HASH hash);

void printHash(HASH hash);

BlocoMinerado *MineBlock(BlocoNaoMinerado *blockToMine);

#endif