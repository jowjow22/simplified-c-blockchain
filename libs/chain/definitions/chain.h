#ifndef CHAIN_H
#define CHAIN_H

struct Chain
{
  BlocoMinerado block;
  struct Chain *next;
};
typedef struct Chain Chain;

void InsertInChain(Chain **chain, LastStoredBlockData *prevMinedBlock, int *blocksAmount, int *minedBlocks, Chain *mainChain, int hasFileChain, unsigned char *accountsBalance);
void storeChain(Chain *chain, char *fileName, int hasFileChain);

void storeHeaderOflastBlock(BlocoMinerado block, unsigned char *accountsBalance);
LastStoredBlockData *readLastStoredBlockData();

#endif