#include "cipher.h"
#include <ctype.h>
#include <stdio.h>

#define ALPHABET_NUM 95 /*126 - 32 + 1*/
#define ASCII_OFFSET 32
#define ASCII_UPPER 126
#define STRIP_ASCII(x) ((x) - ASCII_OFFSET)
#define ADD_ASCII(x) ((x) + ASCII_OFFSET)
#define ENCRYPT true
#define DECRYPT false

bool checkKey(char *secretKey) {
	bool check = true;
	while (*secretKey != '\0') {
		if (*secretKey <= ASCII_OFFSET && *secretKey >= ASCII_UPPER) {
			check = false;
			break;
		}
		secretKey++;
	}
	return check;
}
char getSubstitution(char key, char symbol, bool mode) {
	char result;
	if (mode == true) {
		//encrypt
		result = (STRIP_ASCII(key) + STRIP_ASCII(symbol)) % ALPHABET_NUM;
	} else {
		//decrypt
		result = (STRIP_ASCII(symbol) - STRIP_ASCII(key) + ALPHABET_NUM) % ALPHABET_NUM;
	}
	result = ADD_ASCII(result);
	return result;
}
void encrypt(const char *plainText, char *encryptedText, char *secretKey) {
	if (secretKey == NULL) {
		return;
	}
	for (char *secretKeyInit = secretKey;
		*plainText != '\0' && *plainText != '\n';
		plainText++, encryptedText++) {
		*encryptedText = getSubstitution(*secretKey, *plainText, ENCRYPT);
		secretKey++;
		if (*secretKey == '\0') {
			secretKey = secretKeyInit;
		}
	}
	*encryptedText = '\0';
}
void decrypt(char *plainText, const char *encryptedText, char *secretKey) {
	if (secretKey == NULL) {
		return;
	}
	for (char *secretKeyInit = secretKey;
		*encryptedText != '\0';
		plainText++, encryptedText++) {
		*plainText = getSubstitution(*secretKey, *encryptedText, DECRYPT);
		secretKey++;
		if (*secretKey == '\0') {
			secretKey = secretKeyInit;
		}
	}
	*plainText = '\0';
}