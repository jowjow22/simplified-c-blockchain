#ifndef __RAND_H
#define __RAND_H

#define SEED 1234567

int generateRandNumberBetween(MTRand *randOrigin, int endNumber);
unsigned char randTransactionAdressNumber(MTRand *randOrigin);
unsigned char randBitcoinAmount(MTRand *randOrigin);
int randTransactionsAmount(MTRand *randOrigin);

#endif