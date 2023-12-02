#ifndef CIPHER_H
#define CIPHER_H

#include <stdbool.h>

bool checkKey(char *secretKey);
char getSubstitution(char key, char symbol, bool mode);
void encrypt(const char *plainText, char *encryptedText, char *secretKey);
void decrypt(char *plainText, const char *encryptedText, char *secretKey);

#endif