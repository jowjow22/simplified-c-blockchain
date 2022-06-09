#ifndef BLOCKS_H
#define BLOCKS_H

#define HASH_SIZE SHA256_DIGEST_LENGTH

typedef unsigned char HASH[HASH_SIZE];

struct BlocoNaoMinerado
{
  unsigned int numero;                              // 4
  unsigned int nonce;                               // 4
  unsigned char data[184];                          // nao alterar. Deve ser inicializado com zeros.
  unsigned char hashAnterior[SHA256_DIGEST_LENGTH]; // 32
};
typedef struct BlocoNaoMinerado BlocoNaoMinerado;

struct BlocoMinerado
{
  BlocoNaoMinerado bloco;
  unsigned char hash[SHA256_DIGEST_LENGTH]; // 32 bytes
};
typedef struct BlocoMinerado BlocoMinerado;

BlocoNaoMinerado *NewUnminedBlock(BlocoMinerado *prevMinedBlock, long int accountsBalance[], MTRand *randOrigin);

BlocoMinerado *NewMinedBlock();

void fillRandonUnminedBlockData(BlocoNaoMinerado *block, long int accountsBalance[], MTRand *randOrigin);
void printMinedBlock(BlocoMinerado *block);

#endif