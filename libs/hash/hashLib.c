#include "definitions/hashLib.h"

void calcHash(unsigned char *block, HASH hash)
{
  SHA256(block, sizeof(BlocoNaoMinerado), hash);
}

BlocoMinerado *MineBlock(BlocoNaoMinerado *blockToMine)
{
  HASH hash;
  calcHash((unsigned char *)blockToMine, hash);
  pthread_t threads[15];
  MinerationArgs *minerationArgs = (MinerationArgs *)malloc(sizeof(MinerationArgs));
  minerationArgs->blockToMine = blockToMine;
  BlocoMinerado *blockMined = (BlocoMinerado *)malloc(sizeof(BlocoMinerado));
  minerationArgs->isMined = (int*)malloc(sizeof(int));
  *(minerationArgs->isMined) = 0;
  minerationArgs->hasBrokenOverflow = (int*)malloc(sizeof(int));

do{
for (int i = 0; i < 15; i++) 
{
  if(i != 0){
  minerationArgs->threadId = i-1;
  minerationArgs->rangeStart = (i-1) * (286331153);
  minerationArgs->rangeEnd = i * (286331153);
  pthread_create(&threads[i], NULL, threadMineration, (void *)minerationArgs);
  }
  else 
  {
    minerationArgs->threadId = i;
    minerationArgs->rangeStart = 0;
    minerationArgs->rangeEnd = 286331153;
    pthread_create(&threads[i], NULL, threadMineration, (void *)minerationArgs);
  }
}

  for (int i = 0; i < 15; i++)
  {
    pthread_join(threads[i], NULL);
  }
  if(*(minerationArgs->hasBrokenOverflow) == 1){
    blockToMine->data[183] += 1;
    minerationArgs->blockToMine = blockToMine;
  }


}while(*(minerationArgs->hasBrokenOverflow) == 1);



  calcHash((unsigned char *)blockToMine, hash);
  memccpy(blockMined->hash, hash, sizeof(hash), sizeof(hash));
  blockMined->bloco = *blockToMine;

  free(minerationArgs);

  return blockMined;
}