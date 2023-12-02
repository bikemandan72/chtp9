/*
8.42 (Vigenère Cipher Modification—Supporting All ASCII Characters)
Your Vigenère cipher implementation from Exercise 8.41 encrypts and decrypts only the
letters A–Z. All other characters simply pass through as is. Modify your implementation
to support the complete ASCII character set shown in Appendix B.
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "cipher.h"

#define SECRET_KEY "XMWUJBVYHXZ"
#define MSG "Secure C Programming: Encryption and Decryption"
#define STRSIZE 50
#define ENCRYPT true
#define DECRYPT false

int main (int argc, char *argv[])
{
	char plainText[STRSIZE + 1] = "Welcome to encryption";
	char encryptedText[STRSIZE + 1] = "";
	char secretKey[STRSIZE + 1] = SECRET_KEY;
		
	//printf("' ' = %d\n", ' ');
	
	do {
		printf("Enter secret key "
			"(CAPITAL letters only %d characters long):\n", STRSIZE - 1);
		fgets(secretKey, STRSIZE - 1, stdin);
		strtok(secretKey, "\n");
	} while (!checkKey(secretKey));
	printf("Entered secret key is '%s'\n", secretKey);

	printf("Enter plaintext sentence to encrypt (only letters %d characters long):\n",
		STRSIZE - 1);
	fgets(plainText, STRSIZE - 1, stdin);
	strtok(plainText, "\n");
	printf("Entered plaintext sentence to encrypt is '%s'\n", plainText);

	encrypt(plainText, encryptedText, secretKey);
	printf("Ciphertext is '%s'\n", encryptedText);
	
	decrypt(plainText, encryptedText, secretKey);
	printf("Decrypted plaintext is '%s'\n", plainText);

	*plainText = '\0';
	strcat(plainText, MSG);
	*secretKey = '\0';
	strcat(secretKey, SECRET_KEY);
	
	encrypt(plainText, encryptedText, secretKey);
	printf("The gibberish at the beginning of exercise 8.41 would be '%s'\n",
		encryptedText);
	
	decrypt(plainText, encryptedText, secretKey);
	printf("Decrypted plaintext is '%s'\n",	plainText);
	
	return 0;
}
