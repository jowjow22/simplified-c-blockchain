#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "openssl/crypto.h"
#include "openssl/sha.h"
#include "../libs/mtwister/mtwister.c"
#include "./utils/cls.c"
#include "../libs/rand/rand.c"
#include "../libs/blocks/blocks.c"
#include "../libs/hash/hashLib.c"
#include "../libs/chain/chain.c"

int main()
{
  long int accountsBalance[255];
  Header *header = readHeaders();

  int blocksAmount = 0, minedBlocks = 0, option;

  Chain *chain = NULL;

  BlocoMinerado *lastStoredBlockData = NULL;

  do
  {
    cls();
    printf("1 - Inserir bloco\n");
    printf("2 - Buscar Saldo\n");
    printf("3 - Buscar endereco com mais bitcoins\n");
    printf("4 - Buscar hash de um bloco\n");
    printf("5 - Buscar Saldo de todas as contas\n");
    printf("0 - Sair\n");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
      printf("Digite a quantidade de blocos que deseja minerar: \n");

      scanf("%d", &blocksAmount);

      cls();
      free(chain);
      chain = NULL;
      printf("Minerando blocos...\n");
      lastStoredBlockData = readLastStoredBlockData(accountsBalance);
      InsertInChain(&chain, lastStoredBlockData, &(header->randOrigin), &blocksAmount, &minedBlocks, chain, header->accountsBalance, &(header->minedBLocksUntilNow));

      printf("chain armazenada\n");
      printf("Digite quaisquer numeros para continuar\n");
      scanf("%d", &option);
      header = readHeaders();
      break;
    case 2:
      cls();
      printf("Digite o endereco que deseja consultar o saldo: \n");
      int address;
      scanf("%d", &address);
      memccpy(accountsBalance, header->accountsBalance, sizeof(header->accountsBalance), sizeof(header->accountsBalance));
      cls();
      printf("Saldo: %ld\n", accountsBalance[address]);
      printf("Digite quaisquer numeros para continuar\n");
      scanf("%d", &option);
      break;
    case 3:
      memccpy(accountsBalance, header->accountsBalance, sizeof(header->accountsBalance), sizeof(header->accountsBalance));
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
      printf("Quantidade de bitcoins desse endereco: %d\n", max);
      printf("Digite quaisquer numeros para continuar\n");
      scanf("%d", &option);
      break;
    case 4:
      printf("Digite o numero do bloco que deseja consultar o hash: \n");
      int blockNumber;
      header = readHeaders();

      scanf("%d", &blockNumber);
      if (blockNumber > header->minedBLocksUntilNow)
      {
        printf("Bloco ainda nao minerado\n");
        printf("Digite quaisquer numeros para continuar\n");
        scanf("%d", &option);
        break;
      }
      else
      {
        BlocoMinerado *block;
        block = readBlockData(blockNumber - 1);
        printMinedBlock(block);

        printf("Digite quaisquer numeros para continuar\n");
        scanf("%d", &option);
        break;
      }
    case 5:
      cls();
      memccpy(accountsBalance, header->accountsBalance, sizeof(header->accountsBalance), sizeof(header->accountsBalance));
      cls();
      for (int i = 0; i < 255; i++)
      {
        printf("Saldo da conta %d: %ld\n", i, accountsBalance[i]);
      }
      printf("Digite quaisquer numeros para continuar\n");
      scanf("%d", &option);
      break;
    default:
      cls();
      printf("Finalizando...\n");
      break;
    }
  } while (option != 0);

  return 0;
}