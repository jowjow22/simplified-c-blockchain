#ifndef HASHLIB_H
#define HASHLIB_H

typedef struct MinerationArgs
{
  BlocoNaoMinerado *blockToMine;
} MinerationArgs;

void calcHash(unsigned char *block, HASH hash);

void printHash(HASH hash);

BlocoMinerado *MineBlock(BlocoNaoMinerado *blockToMine);

#endif