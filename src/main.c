#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "openssl/crypto.h"
#include "openssl/sha.h"
#include "../libs/mtwister/mtwister.c"
#include "../libs/rand/rand.c"
#include "../libs/blocks/blocks.c"
#include "../libs/hash/hashLib.c"
#include "../libs/chain/chain.c"
#include "./utils/cls.c"

int main()
{
  unsigned char accountsBalance[255];
  MTRand randOrigin = seedRand(SEED);
  memset(accountsBalance, 0, sizeof(accountsBalance));

  int blocksAmount = 0, minedBlocks = 0, bricksAmount = 0, brickSize, restOfBricks = 0, option;

  Chain *chain = NULL;

  LastStoredBlockData *lastStoredBlockData = NULL;

  do
  {
    cls();
    printf("1 - Inserir bloco\n");
    printf("2 - Buscar Saldo\n");
    printf("3 - Buscar endereco com mais bitcoins\n");
    printf("4 - Buscar hash de um bloco\n");
    printf("0 - Sair\n");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
      printf("Digite a quantidade de blocos que deseja minerar: \n");

      scanf("%d", &blocksAmount);

      restOfBricks = blocksAmount % 60000;

      if (blocksAmount >= 60000)
      {

        bricksAmount = blocksAmount / 60000;

        while (bricksAmount > 0)
        {
          cls();
          printf("Minerando blocos...\n");
          brickSize = 60000;
          free(chain);
          chain = NULL;

          lastStoredBlockData = readLastStoredBlockData(accountsBalance);
          InsertInChain(&chain, lastStoredBlockData, &randOrigin, &brickSize, &minedBlocks, chain, accountsBalance);
          bricksAmount--;
        }
      }

      if (restOfBricks > 0)
      {
        cls();
        free(chain);
        chain = NULL;
        printf("Minerando blocos...\n");
        lastStoredBlockData = readLastStoredBlockData(accountsBalance);
        InsertInChain(&chain, lastStoredBlockData, &randOrigin, &restOfBricks, &minedBlocks, chain, accountsBalance);
      }

      printf("chain armazenada\n");
      printf("Digite qualquer numeros para continuar\n");
      scanf("%d", &option);
      break;
    case 2:
      printf("Digite o endereco que deseja consultar o saldo: \n");
      int address;
      scanf("%d", &address);
      lastStoredBlockData = readLastStoredBlockData(accountsBalance);
      cls();
      printf("Saldo: %d\n", accountsBalance[address]);
      printf("Digite qualquer numero para continuar\n");
      scanf("%d", &option);
      break;
    case 3:
      lastStoredBlockData = readLastStoredBlockData(accountsBalance);
      int addressWithMostBitcoins = 0, max = 0;
      for (int i = 0; i < 255; i++)
      {
        if (accountsBalance[i] > max)
        {
          max = accountsBalance[i];
          addressWithMostBitcoins = i;
        }
      }
      cls();
      printf("Endereco com mais bitcoins: %d\n", addressWithMostBitcoins);
      printf("Digite qualquer numero para continuar\n");
      scanf("%d", &option);
      break;
    case 4:
      printf("Digite o numero do bloco que deseja consultar o hash: \n");
      int blockNumber;
      scanf("%d", &blockNumber);
      break;
    default:
      cls();
      printf("Finalizando...\n");
      break;
    }
  } while (option != 0);

  return 0;
}