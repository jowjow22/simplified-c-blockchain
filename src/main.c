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
  int account[255];
  memset(account, 0, sizeof(account));

  MTRand randOrigin = seedRand(SEED);

  int hasFileChain = 0, blocksAmount = 100, minedBlocks = 0;

  Chain *chain = NULL;

  // printf("Deseja Baixar a Chain? (1 - Sim / 0 - Não)\n");

  // scanf("%d", &hasFileChain);

  // printf("Digite a quantidade de blocos que deseja minerar: \n");

  // scanf("%d", &blocksAmount);

  InsertInChain(&chain, &(chain->block), &randOrigin, &blocksAmount, &minedBlocks, chain);

  printf("chain armazenada\n");

  return 0;
}