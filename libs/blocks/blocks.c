#include "definitions/blocks.h"
#include "openssl/sha.h"

BlocoNaoMinerado *NewUnminedBlock(BlocoMinerado *prevMinedBlock, long int accountsBalance[], MTRand *randOrigin)
{
    BlocoNaoMinerado *block = (BlocoNaoMinerado *)malloc(sizeof(BlocoNaoMinerado));
    if (prevMinedBlock != NULL)
    {
        block->numero = prevMinedBlock->bloco.numero + 1;
        block->nonce = 0;
        memcpy(block->hashAnterior, prevMinedBlock->hash, sizeof(block->hashAnterior));
        memset(block->data, 0, sizeof(block->data));
        fillRandonUnminedBlockData(block, accountsBalance, randOrigin);
    }
    else
    {
        block->numero = 0;
        block->nonce = 0;
        memset(block->hashAnterior, 0, sizeof(block->hashAnterior));
        memset(block->data, 0, sizeof(block->data));
    }
    return block;
}

BlocoMinerado *NewMinedBlock()
{
    BlocoMinerado *bloco = (BlocoMinerado *)malloc(sizeof(BlocoMinerado));
    return bloco;
}

void printHash(HASH hash)
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

void printMinedBlock(BlocoMinerado *block)
{
    printf("Numero: %d\n", block->bloco.numero);
    printf("Nonce: %d\n", block->bloco.nonce);
    printf("Data: \n");
    for (int i = 0; i < 181; i += 3)
    {
        printf("%d %d %d\n", block->bloco.data[i], block->bloco.data[i + 1], block->bloco.data[i + 2]);
    }
    printf("Hash anterior: ");
    printHash(block->bloco.hashAnterior);
    printf("Hash: ");
    printHash(block->hash);
}

void fillRandonUnminedBlockData(BlocoNaoMinerado *block, long int accountsBalance[], MTRand *randOrigin)
{

    for (int i = 0; i < randTransactionsAmount(randOrigin); i += 3)
    {
        unsigned char destinatario = randTransactionAdressNumber(randOrigin), remetente = randTransactionAdressNumber(randOrigin);
        unsigned char bitcoinAmount = randBitcoinAmount(randOrigin);

        while ((destinatario == remetente) || (bitcoinAmount < 1))
        {
            destinatario = randTransactionAdressNumber(randOrigin);
            remetente = randTransactionAdressNumber(randOrigin);
            bitcoinAmount = randBitcoinAmount(randOrigin);
        }
        if (accountsBalance[remetente] < bitcoinAmount)
        {
            accountsBalance[remetente] = 0;
        }
        else
        {
            accountsBalance[remetente] -= bitcoinAmount;
        }
        accountsBalance[destinatario] += bitcoinAmount;
        block->data[i] = remetente;
        block->data[i + 1] = destinatario;
        block->data[i + 2] = bitcoinAmount;
    }
}
