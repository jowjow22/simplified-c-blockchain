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

// int *readHeader(char *fileName, int blocksAmount)
// {
//   Header header;
//   FILE *file = fopen(fileName, "r");
//   fgets((char *)&header, sizeof(header), file);
//   header.numOfMinedBlocks += blocksAmount;
//   printf("%d\n", header.numOfMinedBlocks);
//   return header.accountsBalance;
// }

// void storeHeader(char *fileName, int blocksAmount, unsigned char *accountsBalance)
// {
//   Header header;
//   FILE *file = fopen(fileName, "w");

//   header.numOfMinedBlocks = blocksAmount;

//   fprintf(file, "%d ", header.numOfMinedBlocks);
//   for (int i = 0; i < 255; i++)
//   {
//     fprintf(file, "%d ", header.accountsBalance[i]);
//   }
//   fprintf(file, "\n");
//   fclose(file);
// }

void readLastStoredBlock(Chain **chain, char *fileName)
{
  FILE *file = fopen(fileName, "r+");
  if (file == NULL)
  {
    *chain = NULL;
    return;
  }

  fseek(file, 0, SEEK_END);
  fseek(file, ((-sizeof(BlocoMinerado))*2)+175, SEEK_CUR);

  BlocoMinerado *block = (BlocoMinerado *)malloc(sizeof(BlocoMinerado));

  fscanf(file, "%d %d", &(block->bloco.numero), &(block->bloco.nonce));

  fseek(file, 8, SEEK_CUR);

  for (int i = 0; i < 184; i++)
  {
    block->bloco.data[i] = (unsigned char)strtol((fgetc(file)), NULL, 10); 
  }

  fseek(file, 8, SEEK_CUR);
  for (int i = 0; i < 32; i++)
  {
    fscanf(file, "%02x", &(block->bloco.hashAnterior[i]));
  }
  for (int i = 0; i < 32; i++)
  {
    fscanf(file, "%02x", &(block->hash[i]));
  }

  fclose(file);

  Chain *newSegment = (Chain *)malloc(sizeof(Chain));
  newSegment->block = *block;
  newSegment->next = NULL;
  *chain = newSegment;
}

void storeChain(Chain *chain, char *fileName)
{
  FILE *file = fopen(fileName, "w");
  while (chain != NULL)
  {
    fprintf(file, "%d %d ", chain->block.bloco.numero, chain->block.bloco.nonce);
    for (int i = 0; i < 183; i++)
    {
      fprintf(file, "%d", chain->block.bloco.data[i]);
    }
    fprintf(file, " ");
    for (int i = 0; i < HASH_SIZE; i++)
    {
      fprintf(file, "%02x", chain->block.bloco.hashAnterior[i]);
    }
    fprintf(file, " ");
    for (int i = 0; i < HASH_SIZE; i++)
    {
      fprintf(file, "%02x", chain->block.hash[i]);
    }
    fprintf(file, " ");
    if (chain->next != NULL)
    {
      fprintf(file, "\n");
    }
    chain = chain->next;
  }
  fclose(file);
}