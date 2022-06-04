#include "definitions/blocks.h"
#include "openssl/sha.h"

BlocoNaoMinerado *HeadUnminedBlock(){
    BlocoNaoMinerado *bloco = malloc(sizeof(BlocoNaoMinerado));
    bloco->numero = 0;
    bloco->nonce = 0;
    memset(bloco->data, 0, sizeof(bloco->data));
    memset(bloco->hashAnterior, 0, sizeof(bloco->hashAnterior));
    return bloco;
}

BlocoNaoMinerado *NewUnminedBlock(){
    BlocoNaoMinerado *bloco =
 malloc(sizeof(BlocoNaoMinerado));
    bloco->numero = 0;
    bloco->nonce = 0;
    memset(bloco->data, 0, sizeof(bloco->data));
    memset(bloco->hashAnterior, 0, sizeof(bloco->hashAnterior));
    return bloco;
}

BlocoMinerado *NewMinedBlock(){
    BlocoMinerado *bloco = malloc(sizeof(BlocoMinerado));
    return bloco;
}

void fillRandonUnminedBlock(BlocoNaoMinerado *bloco, BlocoNaoMinerado *blocoAnterior, unsigned char *hashAnterior){
    bloco->numero = blocoAnterior->numero + 1;
    MTRand randOrigin = seedRand(1234567);

    for (int i = 0; i < sizeof(bloco->data); i+=3){
    int destinatario = randTransactionAdressNumber(&randOrigin), remetente = randTransactionAdressNumber(&randOrigin);
    int bitcoinAmount = randBitcoinAmount(&randOrigin);

    while(destinatario == remetente){
        destinatario = randTransactionAdressNumber(&randOrigin);
        remetente = randTransactionAdressNumber(&randOrigin);
    }
        bloco->data[i] = destinatario;
        bloco->data[i+1] = remetente;
        bloco->data[i+2] = bitcoinAmount;
}
    memcpy(bloco->hashAnterior, hashAnterior, sizeof(bloco->hashAnterior));
}

