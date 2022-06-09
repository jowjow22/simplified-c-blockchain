#ifndef CHAIN_H
#define CHAIN_H

struct Chain
{
  BlocoMinerado block;
  struct Chain *next;
};
typedef struct Chain Chain;

struct Header
{
  long int accountsBalance[255];
  long int minedBLocksUntilNow;
  MTRand randOrigin;
};
typedef struct Header Header;

void InsertInChain(Chain **chain, BlocoMinerado *prevMinedBlock, MTRand *randOrigin, int *blocksAmount, int *minedBlocks, Chain *mainChain, long int accountsBalance[]);
void storeChain(Chain *chain, char *fileName, int storeAmount);

void storeHeaders(long int accountsBalance[], MTRand *randOrigin);
BlocoMinerado *readLastStoredBlockData();

#endif