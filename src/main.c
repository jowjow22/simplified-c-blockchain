#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "openssl/crypto.h"
#include "openssl/sha.h"
#include "../libs/mtwister/mtwister.c"
#include "../libs/rand/rand.c"
#include "../libs/blocks/blocks.c"
#include "../libs/hash/hashLib.c"

int main()
{
  MTRand randOrigin = seedRand(SEED);
  int accountsBalance[255];
  memset(accountsBalance, 0, sizeof(int));

  listOfBLocks *chain = NULL;

  stackOfBlocks stack;

  stack.head = NULL;
  stack.tail = NULL;

  int blocksToMine = scanf("%d", &blocksToMine);

  mineBlocks(&chain, stack.tail, stack.head, blocksToMine, accountsBalance);

  // printChain(chain);

  return 0;
}