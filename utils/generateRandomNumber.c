#include <stdio.h>
#include "libs/mtwister/definitions/mtwister.h"

int randNum()
{
  MTRand r = seedRand(1337);
  int i;
  for (i = 0; i < 1000; i++)
  {
    return genRand(&r);
  }
}