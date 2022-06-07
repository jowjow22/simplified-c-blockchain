#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "openssl/crypto.h"
#include "openssl/sha.h"
#include "../libs/mtwister/mtwister.c"
#include "../libs/rand/rand.c"
#include "../libs/blocks/blocks.c"
#include "../libs/hash/hashLib.c"
#include "../libs/chain/chain.c"

int main()
{
  unsigned char accountsBalance[255];
  MTRand randOrigin = seedRand(SEED);
  memset(accountsBalance, 0, sizeof(accountsBalance));

  int hasFileChain = 0, blocksAmount = 100, minedBlocks = 0;

  Chain *chain = NULL;

  printf("Deseja Baixar a Chain? (1 - Sim / 0 - Não)\n");

  scanf("%d", &hasFileChain);

  printf("Digite a quantidade de blocos que deseja minerar: \n");

  scanf("%d", &blocksAmount);

  if (hasFileChain)
  {
    LastStoredBlockData *lastStoredBlockData = readLastStoredBlockData(accountsBalance);
    if (lastStoredBlockData != NULL)
    {
      InsertInChain(&chain, lastStoredBlockData, &randOrigin, &blocksAmount, &minedBlocks, chain, hasFileChain, accountsBalance);
    }
  }
  else
  {
    LastStoredBlockData *lastStoredBlockData = (LastStoredBlockData *)malloc(sizeof(LastStoredBlockData));
    lastStoredBlockData->number = -1;
    InsertInChain(&chain, lastStoredBlockData, &randOrigin, &blocksAmount, &minedBlocks, chain, hasFileChain, accountsBalance);
  }

  printChain(chain);

  printf("chain armazenada\n");

  return 0;
}