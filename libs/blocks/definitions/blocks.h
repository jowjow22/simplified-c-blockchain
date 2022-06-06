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

struct Header
{
  int numOfMinedBlocks;
  int accountsBalance[255];
};
typedef struct Header Header;

BlocoNaoMinerado *NewUnminedBlock(BlocoMinerado *prevMinedBlock, MTRand *randOrigin);

BlocoMinerado *NewMinedBlock();

void fillRandonUnminedBlockData(BlocoNaoMinerado *block, MTRand *randOrigin);

#endif