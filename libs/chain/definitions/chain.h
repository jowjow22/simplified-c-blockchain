#ifndef CHAIN_H
#define CHAIN_H

struct Chain
{
  BlocoMinerado block;
  struct Chain *next;
};
typedef struct Chain Chain;

void InsertInChain(Chain **chain, BlocoMinerado *prevMinedBlock, MTRand *randOrigin, int *blocksAmount, int *minedBlocks, Chain *mainChain, int hasFileChain);
void readLastStoredBlock(Chain **chain, char *fileName);
void storeChain(Chain *chain, char *fileName, int hasFileChain);

#endif