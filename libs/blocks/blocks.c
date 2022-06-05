#include "definitions/blocks.h"
#include "openssl/sha.h"

BlocoNaoMinerado *newUnminedBlock(BlocoNaoMinerado *blocoAnterior, unsigned char *hashAnterior, int accountsBalance[255])
{
    BlocoNaoMinerado *bloco =
        malloc(sizeof(BlocoNaoMinerado));
    bloco->numero = blocoAnterior == NULL ? 0 : blocoAnterior->numero + 1;
    bloco->nonce = 0;
    memset(bloco->data, 0, sizeof(bloco->data));
    blocoAnterior == NULL ? memset(bloco->hashAnterior, 0, sizeof(bloco->hashAnterior)) : stpcpy(bloco->hashAnterior, hashAnterior);
    if (bloco->numero != 0)
    {
        fillRandonUnminedBlock(bloco, hashAnterior, accountsBalance);
    }
    return bloco;
}

BlocoMinerado *createNewMinedBlock(BlocoNaoMinerado bloco, HASH hash)
{
    BlocoMinerado *newMinedBlock = malloc(sizeof(BlocoMinerado));
    newMinedBlock->bloco = bloco;
    strcpy(newMinedBlock->hash, hash);
    return newMinedBlock;
}

void fillRandonUnminedBlock(BlocoNaoMinerado *bloco, unsigned char *hashAnterior, int accountsBalance[255])
{
    MTRand randOrigin = seedRand(1234567);

    for (int i = 0; i < sizeof(bloco->data); i += 3)
    {
        int destinatario = randTransactionAdressNumber(&randOrigin), remetente = randTransactionAdressNumber(&randOrigin);
        int bitcoinAmount = randBitcoinAmount(&randOrigin);

        while (destinatario == remetente)
        {
            destinatario = randTransactionAdressNumber(&randOrigin);
            remetente = randTransactionAdressNumber(&randOrigin);
        }
        bloco->data[i] = destinatario;
        bloco->data[i + 1] = remetente;
        bloco->data[i + 2] = bitcoinAmount;
        accountsBalance[remetente] = accountsBalance[remetente] - bitcoinAmount;
        if (accountsBalance[remetente] < 0)
        {
            accountsBalance[remetente] = 0;
        }
        accountsBalance[destinatario] = accountsBalance[destinatario] + bitcoinAmount;
    }
    memcpy(bloco->hashAnterior, hashAnterior, sizeof(bloco->hashAnterior));
}

void mineBlocks(listOfBLocks **chain, listOfBLocks *tail, BlocoMinerado *head, int blocksToMine, int accountsBalance[255])
{
    for (int i = 0; i < blocksToMine - 1; i++)
    {
        BlocoNaoMinerado *blocoNovo = newUnminedBlock(tail, tail->block.hash, accountsBalance);
        BlocoMinerado *blocoMinerado = mineBlock(blocoNovo);
        if (*chain == NULL)
        {
            listOfBLocks *newBlock = (listOfBLocks *)malloc(sizeof(listOfBLocks));
            newBlock->block = *blocoMinerado;
            newBlock->next = NULL;
            head = newBlock;
            tail = newBlock;
            *chain = newBlock;
        }
        else
        {
            listOfBLocks *newBlock = (listOfBLocks *)malloc(sizeof(listOfBLocks));
            newBlock->block = *blocoMinerado;
            newBlock->next = NULL;
            tail->next = newBlock;
        }
    }
}

// funcao que imprime um bloco
// void printBlock(BlocoMinerado bloco)
// {
//     printf("Bloco: %d\n", bloco.bloco.numero);
//     printf("Nonce: %d\n", bloco.bloco.nonce);
//     printf("Hash: ");
//     printHash(bloco.hash);
//     printf("\n");
// }

// void printChain(listOfBLocks *chain)
// {
//     while (chain != NULL)
//     {
//         printBlock(chain->block);
//         chain = chain->next;
//     }
// }

// void storeChain(chainOfBlocks *currentlyChainHead)
// {
//     FILE *chainFile = fopen("chain.txt", "w");
//     fwrite(currentlyChainHead->next, sizeof(BlocoMinerado), 16, chainFile);
//     fclose(chainFile);
// }