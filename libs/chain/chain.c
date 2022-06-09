#include "definitions/chain.h"

void InsertInChain(Chain **chain, BlocoMinerado *prevMinedBlock, MTRand *randOrigin, int *blocksAmount, int *minedBlocks, Chain *mainChain, long int accountsBalance[])
{
  if (*minedBlocks == 15)
  {
    storeChain(mainChain, "chain.bin", 15);
    storeHeaders(accountsBalance, randOrigin);
    *minedBlocks = 0;
    mainChain = *chain;
  }
  if (*blocksAmount == 0)
  {
    storeChain(mainChain, "chain.bin", *minedBlocks);
    storeHeaders(accountsBalance, randOrigin);
    *minedBlocks = 0;
    return;
  }
  else if (*chain == NULL)
  {
    Chain *newSegment = (Chain *)malloc(sizeof(Chain));
    BlocoNaoMinerado *newBlock;
    if (prevMinedBlock->bloco.numero != -1)
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
    prevMinedBlock->bloco.numero = newSegment->block.bloco.numero;
    memcpy(prevMinedBlock->hash, newSegment->block.hash, HASH_SIZE);
  }
  *blocksAmount = *blocksAmount - 1;
  *minedBlocks = *minedBlocks + 1;
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
    printf("\n==============================================\n\n");
    chain = chain->next;
  }
}

void storeHeaders(long int *accountsBalance, MTRand *randOrigin)
{
  FILE *file = fopen("headers.bin", "wb");
  Header *header = (Header *)malloc(sizeof(Header));
  for (int i = 0; i < 255; i++)
  {
    header->accountsBalance[i] = accountsBalance[i];
  }
  header->randOrigin = *randOrigin;
  header->minedBLocksUntilNow = 0;
  fwrite(header, sizeof(Header), 1, file);
  fclose(file);
}

Header *readHeaders()
{
  Header *header = (Header *)malloc(sizeof(Header));
  FILE *file;
  if (file = fopen("headers.bin", "rb"))
  {
    fread(header, sizeof(Header), 1, file);
    fclose(file);
  }
  else
  {
    header->randOrigin = seedRand(SEED);
    memset(header->accountsBalance, 0, sizeof(header->accountsBalance));
  }
  return header;
}

BlocoMinerado *readLastStoredBlockData(long int *accountsBalance)
{
  BlocoMinerado *lastBlock = (BlocoMinerado *)malloc(sizeof(BlocoMinerado));
  FILE *file;
  if (file = fopen("chain.bin", "rb"))
  {
    fseek(file, -(sizeof(BlocoMinerado)), SEEK_END);
    fread(lastBlock, sizeof(BlocoMinerado), 1, file);
    fclose(file);
  }
  else
  {
    lastBlock->bloco.numero = -1;
  }
  return lastBlock;
}

BlocoMinerado *readBlockData(int numero)
{
  BlocoMinerado *block = (BlocoMinerado *)malloc(sizeof(BlocoMinerado));
  FILE *file;
  if (file = fopen("chain.bin", "rb"))
  {
    fseek(file, (sizeof(BlocoMinerado) * numero), SEEK_SET);
    fread(block, sizeof(BlocoMinerado), 1, file);
    fclose(file);
  }
  else
  {
    block->bloco.numero = -1;
  }
  return block;
}

void storeChain(Chain *chain, char *fileName, int storeAmount)
{

  BlocoMinerado *blocks = (BlocoMinerado *)malloc(sizeof(BlocoMinerado) * storeAmount);
  for (int i = 0; i < storeAmount; i++)
  {
    blocks[i] = chain->block;
    chain = chain->next;
  }
  FILE *file = fopen(fileName, "ab");

  fwrite(blocks, sizeof(BlocoMinerado), storeAmount, file);

  fclose(file);
  free(blocks);
  blocks = NULL;
}