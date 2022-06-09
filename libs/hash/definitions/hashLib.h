#ifndef HASHLIB_H
#define HASHLIB_H

void calcHash(unsigned char *block, HASH hash);

void printHash(HASH hash);

BlocoMinerado *MineBlock(BlocoNaoMinerado *blockToMine);

#endif