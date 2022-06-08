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

  int hasFileChain = 0, blocksAmount = 0, minedBlocks = 0, bricksAmount = 0, brickSize;

  Chain *chain = NULL;

  LastStoredBlockData *lastStoredBlockData = NULL;

  printf("Deseja Baixar a Chain? (1 - Sim / 0 - Não)\n");

  scanf("%d", &hasFileChain);

  printf("Digite a quantidade de blocos que deseja minerar, Colocar valores multiplos de 60 mil: \n");

  scanf("%d", &blocksAmount);

  bricksAmount = blocksAmount / 60000;

  while (bricksAmount > 0)
  {
    brickSize = 60000;
    free(chain);
    chain = NULL;
    if (bricksAmount < (blocksAmount / 60000))
    {
      hasFileChain = 1;
    }
    printf("FileChain: %d\n", hasFileChain);
    if (hasFileChain == 1)
    {
      lastStoredBlockData = readLastStoredBlockData(accountsBalance);
      if (lastStoredBlockData != NULL)
      {
        InsertInChain(&chain, lastStoredBlockData, &randOrigin, &brickSize, &minedBlocks, chain, hasFileChain, accountsBalance);
      }
    }
    else
    {
      lastStoredBlockData = (LastStoredBlockData *)malloc(sizeof(LastStoredBlockData));
      lastStoredBlockData->number = -1;
      InsertInChain(&chain, lastStoredBlockData, &randOrigin, &brickSize, &minedBlocks, chain, hasFileChain, accountsBalance);
    }
    bricksAmount--;
  }

  printf("chain armazenada\n");

  return 0;
}