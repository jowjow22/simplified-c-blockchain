#include "definitions/rand.h"

unsigned char randTransactionAdressNumber(MTRand *randOrigin)
{

  return (unsigned char)(genRand(randOrigin) * 1000);
}

unsigned char randBitcoinAmount(MTRand *randOrigin)
{
  return (unsigned char)(genRand(randOrigin) * 50);
}

int randTransactionsAmount(MTRand *randOrigin)
{
  return (int)(genRand(randOrigin) * 61);
}