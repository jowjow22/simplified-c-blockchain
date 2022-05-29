#include "../../mtwister/definitions/mtwister.h"
#include "../../mtwister/mtwister.c"

#ifndef __RAND_H
#define __RAND_H

#define SEED 1234567

int generateRandNumberBetween(MTRand *randOrigin, int endNumber);
unsigned char randTransactionAdressNumber();
unsigned char randBitcoinAmount(MTRand *randOrigin);
int randTransactionsAmount(MTRand *randOrigin);

#endif