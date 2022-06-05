#include "definitions/rand.h"

int generateRandNumberBetween(MTRand *randOrigin, int endNumber)
{
  return genRand(randOrigin) * endNumber;
}

unsigned char randTransactionAdressNumber(MTRand *randOrigin)
{

  return (unsigned char)generateRandNumberBetween(randOrigin, 1000);
}

unsigned char randBitcoinAmount(MTRand *randOrigin)
{
  return (unsigned char)generateRandNumberBetween(randOrigin, 50);
}

int randTransactionsAmount(MTRand *randOrigin)
{
  return (int)generateRandNumberBetween(randOrigin, 181);
}