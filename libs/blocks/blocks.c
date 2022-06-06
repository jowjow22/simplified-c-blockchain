#include "definitions/blocks.h"
#include "openssl/sha.h"

BlocoNaoMinerado *NewUnminedBlock(BlocoMinerado *prevMinedBlock, MTRand *randOrigin)
{
    BlocoNaoMinerado *block = (BlocoNaoMinerado *)malloc(sizeof(BlocoNaoMinerado));
    if (prevMinedBlock != NULL)
    {
        block->numero = prevMinedBlock->bloco.numero + 1;
        block->nonce = 0;
        memcpy(block->hashAnterior, prevMinedBlock->hash, sizeof(block->hashAnterior));
        fillRandonUnminedBlockData(block, randOrigin);
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

void fillRandonUnminedBlockData(BlocoNaoMinerado *block, MTRand *randOrigin)
{
    for (int i = 0; i < randTransactionsAmount(randOrigin); i += 3)
    {
        unsigned char destinatario = randTransactionAdressNumber(randOrigin), remetente = randTransactionAdressNumber(randOrigin);
        unsigned char bitcoinAmount = randBitcoinAmount(randOrigin);

        while (destinatario == remetente)
        {
            destinatario = randTransactionAdressNumber(randOrigin);
            remetente = randTransactionAdressNumber(randOrigin);
        }
        block->data[i] = destinatario;
        block->data[i + 1] = remetente;
        block->data[i + 2] = bitcoinAmount;
    }
}
