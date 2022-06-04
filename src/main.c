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
  int account[255];
  memset(account, 0, sizeof(account));
  BlocoMinerado *blocoM = newMinedBlock();
  BlocoNaoMinerado *bloco = HeadUnminedBlock(); 

  MineBlock(bloco, NULL, blocoM, NULL);

  BlocoMinerado *blocoMnovo = newMinedBlock();
  BlocoNaoMinerado *bloconovo = newUnminedBlock(); 

  MineBlock(bloconovo, bloco, blocoMnovo, blocoM->hash);
  
  
  // HASH hash;

  // calcHash((unsigned char *)bloco, hash);
  // printHash(hash);

  // for (int i = 0; i < 1000; i++)
  // {
  //   printf("%u\n", randBitcoinAmount(&randOrigin));
  // }
  // for (int i = 0; i < 1000; i++)
  // {
  //   printf("%d\n", randTransactionAdressNumber(&randOrigin));
  // }
  // printf("tam: %d\n",(int)sizeof(BlocoMinerado));
  return 0;
}