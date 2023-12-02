/*
8.41 (Pqyoaf X Nylfomigrob: Cuzqvbpcxo vlk Adzdujcjjl)
Implementing the Vigenère Cipher
For this exercise, you should implement your Vigenère cipher code in the file
cipher.c . This source-code file should contain the following items:
• Function checkKey receives a secret-key string and returns true if that string
consists only of letters. Otherwise, this function returns false , in which case
the key cannot be used with the Vigenère cipher algorithm. This function is
called by the encrypt and decrypt functions described below.
• Function getSubstitution receives a secret-key character, a character from a
plaintext or ciphertext string and a bool indicating whether to encrypt ( true )
or decrypt ( false ) the character in the second argument. This function is
called by the encrypt and decrypt functions (described below) to perform the
Vigenère cipher encryption or decryption algorithm for one character. The
function contains the Vigenère square as a 26-by-26 two-dimensional static
const char array.
• Function encrypt receives a string containing the plaintext to encrypt, a char-
acter array in which to write the encrypted text, and the secret key. The func-
tion iterates through the plaintext characters. For each letter, encrypt calls
getSubstitution , passing the current secret-key character, the letter to encrypt
and true . Function getSubstitution then performs the Vigenère cipher
encryption algorithm for that letter and returns its ciphertext equivalent.
• Function decrypt receives a string containing the ciphertext to decrypt, a
character array in which to write the resulting plaintext, and the secret key
used to create the ciphertext. The function iterates through the ciphertext
characters. For each letter, decrypt calls getSubstitution , passing the current
secret key character, the letter to decrypt and false . Function getSubstitu-
tion then performs the Vigenère cipher decryption algorithm for that letter
and returns its plaintext equivalent.
Other Files You Should Create
In addition to cipher.c , you should create the following code files:
• cipher.h should contain the encrypt and decrypt function prototypes.
• cipher_test.c , which #include s "cipher.h" and uses your encrypt and
decrypt functions to encrypt and decrypt text.
cipher_test.c
In your application, perform the following tasks:
1. Prompt for and input a plaintext sentence to encrypt and a secret key con-
sisting only of letters, call encrypt to create the ciphertext, then display it. Use
our secret key XMWUJBVYHXZ — this will enable you to decrypt the gibberish at
the beginning of this exercise.
2. Use your decrypt function and the secret key you entered in Step 1 to decrypt
the ciphertext you just created. Display the resulting plaintext to ensure your
decrypt function worked correctly.
3. Prompt for and input either the ciphertext section title that precedes this ex-
ercise or the exercise ciphertext title. Then, use your decrypt function and the
secret-key text you entered in Step 1 to decrypt the ciphertext.
As always, you should ensure that the character arrays into which you write encrypted
or decrypted text are large enough to store the text and its terminating null character.
Once your Vigenère cipher encryption and decryption algorithms work, have
some fun sending and receiving encrypted messages with your friends. When you
pass your secret key to the person who’ll use it to decrypt your ciphertext messages,
focus on keeping your key secure.
Compiling Your Code
In Visual C++ and Xcode, simply add all three files to your project, then compile and
run the code. For GNU gcc , execute the following command from the folder con-
taining cipher.c , cipher.h and cipher_test.c files:
gcc -std=c18 -Wall cipher.c cipher_test.c -o cipher_test
This will create the command cipher_test , which you can run with ./cipher_test .
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "cipher.h"

#define SECRET_KEY "XMWUJBVYHXZ"
#define ENCRYPTED_MSG "Pqyoaf X Nylfomigrob Cuzqvbpcxo vlk Adzdujcjjl"
#define STRSIZE 50
#define ENCRYPT true
#define DECRYPT false

int main (int argc, char *argv[])
{
	char plainText[STRSIZE + 1] = "Welcome to encryption";
	char encryptedText[STRSIZE + 1] = "";
	char secretKey[STRSIZE + 1] = SECRET_KEY;
	
	//printf("'%s' %s a valid secret key\n",
	//	SECRET_KEY, (checkKey(secretkey)) ? "is" : "is not");
		
	//printf("'%c' -> '%c'\n", 'E', getSubstitution('M', 'E', ENCRYPT));
	//printf("'%c' -> '%c'\n", 'Q', getSubstitution('M', 'Q', DECRYPT));
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
	strcat(plainText, ENCRYPTED_MSG);
	*secretKey = '\0';
	strcat(secretKey, SECRET_KEY);
	
	decrypt(plainText, ENCRYPTED_MSG, secretKey);
	printf("The gibberish at the beginning of this exercise is '%s'\n", ENCRYPTED_MSG);
	printf("Decrypted plaintext is '%s'\n",	plainText);
	
	return 0;
}
