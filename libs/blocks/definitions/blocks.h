#include "../../hash/definitions/hashLib.h"
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

struct listOfBLocks
{
  BlocoMinerado block;
  struct listOfBLocks *next;
};
typedef struct listOfBLocks listOfBLocks;

struct stackOfBlocks
{
  BlocoMinerado *head;
  struct listOfBLocks *tail;
};
typedef struct stackOfBlocks stackOfBlocks;

BlocoNaoMinerado *newUnminedBlock(BlocoNaoMinerado *blocoAnterior, unsigned char *hashAnterior, int accountsBalance[255]);

BlocoMinerado *createNewMinedBlock(BlocoNaoMinerado bloco, HASH hash);

void fillRandonUnminedBlock(BlocoNaoMinerado *bloco, unsigned char *hashAnterior, int accountsBalance[255]);

#endif