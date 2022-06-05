#ifndef CHAIN_H
#define CHAIN_H

struct Chain
{
  BlocoMinerado block;
  struct Chain *next;
};
typedef struct Chain Chain;

void InsertInChain(Chain **chain, BlocoMinerado *prevMinedBlock, MTRand *randOrigin, int *blocksAmount, int *minedBlocks, Chain *mainChain);
void storeChain(Chain *chain, char *fileName);

#endif