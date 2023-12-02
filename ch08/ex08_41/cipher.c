#include "cipher.h"
#include <ctype.h>
#include <stdio.h>

#define ALPHABET_NUM 26
#define ASCII_OFFSET 65
#define STRIP_ASCII(x) ((x) - ASCII_OFFSET)
#define ADD_ASCII(x) ((x) + ASCII_OFFSET)
#define ENCRYPT true
#define DECRYPT false

bool checkKey(char *secretKey) {
	bool check = true;
	while (*secretKey != '\0') {
		if (!isalpha(*secretKey)) {
			check = false;
			break;
		}
		*secretKey = toupper(*secretKey);
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
		/*
		if (key > symbol) {
			result = ALPHABET_NUM - STRIP_ASCII(key) + STRIP_ASCII(symbol);
		} else {
			result = STRIP_ASCII(symbol) - STRIP_ASCII(key);
		}
		*/
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
		if (isspace(*plainText)) {
			*encryptedText = *plainText;
			continue;
		}
		*encryptedText = getSubstitution(*secretKey, toupper(*plainText), ENCRYPT);
		if (islower(*plainText)) {
			*encryptedText = tolower(*encryptedText);
		}
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
		if (isspace(*encryptedText)) {
			*plainText = *encryptedText;
			continue;
		}
		*plainText = getSubstitution(*secretKey, toupper(*encryptedText), DECRYPT);
		if (islower(*encryptedText)) {
			*plainText = tolower(*plainText);
		}
		secretKey++;
		if (*secretKey == '\0') {
			secretKey = secretKeyInit;
		}
	}
	*plainText = '\0';
}