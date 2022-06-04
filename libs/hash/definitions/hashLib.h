#ifndef HASHLIB_H
#define HASHLIB_H

#define HASH_SIZE SHA256_DIGEST_LENGTH

typedef unsigned char HASH[HASH_SIZE];

void calcHash(unsigned char *block, HASH hash);

void printHash(HASH hash);

void MineBlock(BlocoNaoMinerado *bloco, BlocoNaoMinerado *blocoAnterior, BlocoMinerado *blocoM, unsigned char *hashAnterior);

#endif