#include "definitions/chain.h"

void InsertInChain(Chain **chain, LastStoredBlockData *prevMinedBlock, MTRand *randOrigin, int *blocksAmount, int *minedBlocks, Chain *mainChain, unsigned char *accountsBalance)
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
    BlocoNaoMinerado *newBlock;
    if (prevMinedBlock->number != -1)
    {
      newBlock = NewUnminedBlock(prevMinedBlock, accountsBalance, randOrigin);
    }
    else
    {
      newBlock = NewUnminedBlock(NULL, accountsBalance, randOrigin);
    }
    BlocoMinerado *minedBlock = MineBlock(newBlock);
    newSegment->block = *minedBlock;
    newSegment->next = NULL;
    *chain = newSegment;
    if (mainChain == NULL)
    {
      mainChain = *chain;
    }
    prevMinedBlock->number = newSegment->block.bloco.numero;
    memcpy(prevMinedBlock->hash, newSegment->block.hash, HASH_SIZE);
  }
  *blocksAmount = *blocksAmount - 1;
  *minedBlocks = *minedBlocks + 1;
  if (*blocksAmount == 0)
  {
    storeHeaderOflastBlock((*chain)->block, accountsBalance);
  }
  InsertInChain(&((*chain)->next), prevMinedBlock, randOrigin, blocksAmount, minedBlocks, mainChain, accountsBalance);
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

void storeHeaderOflastBlock(BlocoMinerado block, unsigned char *accountsBalance)
{
  FILE *file = fopen("headers.txt", "w");
  fseek(file, 0, SEEK_SET);
  fprintf(file, "%d ", block.bloco.numero);
  for (int i = 0; i < HASH_SIZE; i++)
  {
    fprintf(file, "%02x", block.hash[i]);
  }
  fprintf(file, "\n");
  for (int i = 0; i < 255; i++)
  {
    fprintf(file, "%d\n", accountsBalance[i]);
  }
  fclose(file);
}
LastStoredBlockData *readLastStoredBlockData(unsigned char *accountsBalance)
{
  LastStoredBlockData *data = (LastStoredBlockData *)malloc(sizeof(LastStoredBlockData));
  FILE *file;
  if (file = fopen("headers.txt", "r"))
  {
    fscanf(file, "%d", &(data->number));
    for (int i = 0; i < HASH_SIZE; i++)
    {
      fscanf(file, "%02hhx", &(data->hash[i]));
    }
    for (int i = 0; i < 255; i++)
    {
      fscanf(file, "%hhd", &(accountsBalance[i]));
    }
    fclose(file);
  }
  else
  {
    data->number = -1;
  }
  return data;
}

void searchHashOfBlock(int number, unsigned char *hash)
{
  FILE *file;
  if (file = fopen("chain.txt", "r"))
  {
    fseek(file, ((sizeof(BlocoMinerado) * number) + (sizeof(int) * 185)), SEEK_SET);
  }
}

void storeChain(Chain *chain, char *fileName)
{
  FILE *file = fopen(fileName, "a");
  while (chain != NULL)
  {
    fprintf(file, "%d%d", chain->block.bloco.numero, chain->block.bloco.nonce);
    for (int i = 0; i < 183; i++)
    {
      fprintf(file, "%d", chain->block.bloco.data[i]);
    }
    for (int i = 0; i < HASH_SIZE; i++)
    {
      fprintf(file, "%02x", chain->block.bloco.hashAnterior[i]);
    }
    for (int i = 0; i < HASH_SIZE; i++)
    {
      fprintf(file, "%02x", chain->block.hash[i]);
    }
    chain = chain->next;
  }
  fclose(file);
}