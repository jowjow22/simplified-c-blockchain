#include "definitions/chain.h"

void InsertInChain(Chain **chain, BlocoMinerado *prevMinedBlock, MTRand *randOrigin, int *blocksAmount, int *minedBlocks, Chain *mainChain)
{
  if (*minedBlocks == 15)
  {
    storeChain(mainChain, "chain.txt");
    *minedBlocks = 0;
    mainChain = *chain;
  }
  if (*blocksAmount == 0)
  {
    storeChain(mainChain, "chain.txt");
    return;
  }
  else if (*chain == NULL)
  {
    Chain *newSegment = (Chain *)malloc(sizeof(Chain));
    BlocoNaoMinerado *newBlock = NewUnminedBlock(prevMinedBlock, randOrigin);
    BlocoMinerado *minedBlock = MineBlock(newBlock);
    newSegment->block = *minedBlock;
    newSegment->next = NULL;
    *chain = newSegment;
    if (mainChain == NULL)
    {
      mainChain = *chain;
    }
  }
  *blocksAmount = *blocksAmount - 1;
  *minedBlocks = *minedBlocks + 1;
  InsertInChain(&((*chain)->next), &((*chain)->block), randOrigin, blocksAmount, minedBlocks, mainChain);
}

void printChain(Chain *chain)
{
  while (chain != NULL)
  {
    printf("Numero: %d\n", chain->block.bloco.numero);
    printf("Nonce: %d\n", chain->block.bloco.nonce);
    printf("Data: \n");
    for (int i = 0; i < 181; i += 3)
    {
      printf("%d %d %d\n", chain->block.bloco.data[i], chain->block.bloco.data[i + 1], chain->block.bloco.data[i + 2]);
    }
    printf("Hash anterior: ");
    printHash(chain->block.bloco.hashAnterior);
    printf("Hash: ");
    printHash(chain->block.hash);
    printf("\n==============================================\n");
    chain = chain->next;
  }
}

void storeChain(Chain *chain, char *fileName)
{
  FILE *file = fopen(fileName, "a");
  while (chain != NULL)
  {
    fprintf(file, "%d %d\n", chain->block.bloco.numero, chain->block.bloco.nonce);
    for (int i = 0; i < 181; i++)
    {
      fprintf(file, "%d ", chain->block.bloco.data[i]);
    }
    fprintf(file, "\n");
    for (int i = 0; i < HASH_SIZE; i++)
    {
      fprintf(file, "%02x", chain->block.bloco.hashAnterior[i]);
    }
    fprintf(file, "\n");
    for (int i = 0; i < HASH_SIZE; i++)
    {
      fprintf(file, "%02x", chain->block.hash[i]);
    }
    if (chain->next != NULL)
    {
      fprintf(file, "\n");
    }
    chain = chain->next;
  }
  fclose(file);
}