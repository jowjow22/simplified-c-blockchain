#include "definitions/blocks.h"
#include "openssl/sha.h"

BlocoNaoMinerado *NewUnminedBlock(LastStoredBlockData *prevMinedBlock, unsigned char *accountsBalance, MTRand *randOrigin)
{
    BlocoNaoMinerado *block = (BlocoNaoMinerado *)malloc(sizeof(BlocoNaoMinerado));
    if (prevMinedBlock != NULL)
    {
        block->numero = prevMinedBlock->number + 1;
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

void fillRandonUnminedBlockData(BlocoNaoMinerado *block, unsigned char *accountsBalance, MTRand *randOrigin)
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
