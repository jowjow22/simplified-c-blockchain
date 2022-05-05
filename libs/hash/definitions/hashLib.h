#include "openssl/crypto.h"
#include "openssl/sha.h"

#ifndef __HASHLIB_H
#define __HASHLIB_H

#define HASH_SIZE SHA256_DIGEST_LENGTH

typedef unsigned char HASH[HASH_SIZE];

void calcHash(int val, HASH hash);

void printHash(unsigned char hash[]);

#endif