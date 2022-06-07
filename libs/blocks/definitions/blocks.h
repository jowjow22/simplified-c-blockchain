#ifndef BLOCKS_H
#define BLOCKS_H

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

struct LastStoredBlockData
{
  unsigned int number;
  unsigned char hash[SHA256_DIGEST_LENGTH];
};
typedef struct LastStoredBlockData LastStoredBlockData;

BlocoNaoMinerado *NewUnminedBlock(LastStoredBlockData *prevMinedBlock, unsigned char *accountsBalance);

BlocoMinerado *NewMinedBlock();

void fillRandonUnminedBlockData(BlocoNaoMinerado *block, unsigned char *accountsBalance);

#endif