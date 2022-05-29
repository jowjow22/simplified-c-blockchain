#include "../libs/rand/definitions/rand.h"

int generateRandNumberBetween(MTRand *randOrigin, int endNumber){
  return genRand(randOrigin) * endNumber;
}