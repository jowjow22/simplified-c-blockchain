#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "openssl/crypto.h"
#include "openssl/sha.h"
#include "../libs/blocks/definitions/blocks.h"
#include "../libs/hash/hashLib.c"
#include "../libs/rand/rand.c"

int main()
{
  MTRand randOrigin = seedRand(SEED);
  BlocoNaoMinerado *bloco;
  bloco = malloc(sizeof(BlocoNaoMinerado));
  bloco->numero = 0;
  bloco->nonce = 0;
  memset(bloco->data, 0, sizeof(bloco->data));
  memset(bloco->hashAnterior, 0, sizeof(bloco->hashAnterior));

  HASH hash;

  calcHash((unsigned char *)bloco, hash);
  printHash(hash);

  for (int i = 0; i < 1000; i++)
  {
    printf("%u\n", randBitcoinAmount(&randOrigin));
  }
  return 0;
}