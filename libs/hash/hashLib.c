#include "openssl/crypto.h"
#include "openssl/sha.h"
#include "definitions/hashLib.h"


void calcHash(unsigned char *block, HASH hash)
{
  SHA256((unsigned char *)block, sizeof(BlocoNaoMinerado), hash);
}

void printHash(HASH hash)
{
  for (int i = 0; i < HASH_SIZE; i++)
  {
    printf("%02x", hash[i]);
  }
  printf("\n");
}

void MineBlock(BlocoNaoMinerado *bloco, BlocoNaoMinerado *blocoAnterior, BlocoMinerado *blocoM, unsigned char *hashAnterior)
{
  if(bloco->numero != 0){
    fillRandonUnminedBlock(bloco, blocoAnterior, hashAnterior);
  }
  HASH hash;
  calcHash((unsigned char *)bloco, hash);
  int isMined = 0;
do{
    if(hash[0] == 0 && hash[1] == 0){
      isMined = 1;
    }
    else
    {
      bloco->nonce++;
      calcHash((unsigned char *)bloco, hash);
    }
  } while(isMined == 0);
  printf("\nBlock mined!\n");
  printHash(hash);
  blocoM->bloco = *bloco;
  *(blocoM)->hash = hash;
}