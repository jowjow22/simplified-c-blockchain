#ifndef CHAIN_H
#define CHAIN_H

struct Chain
{
  BlocoMinerado block;
  struct Chain *next;
};
typedef struct Chain Chain;

void InsertInChain(Chain **chain, LastStoredBlockData *prevMinedBlock, MTRand *randOrigin, int *blocksAmount, int *minedBlocks, Chain *mainChain, unsigned char *accountsBalance);
void storeChain(Chain *chain, char *fileName);

void storeHeaderOflastBlock(BlocoMinerado block, unsigned char *accountsBalance);
LastStoredBlockData *readLastStoredBlockData();

#endif