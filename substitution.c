#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int key_validation(char* k, int argc);
char* encrypt(char* text, char* k);


int main (int argc, char* argv[])
{
    // Check if key is valid
    int error = key_validation(argv[1], argc);

    // If key is not valid, exit program
    // Error 1
    if (error == 1)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    // Error 2
    else if (error == 2)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    // Error 3
    else if (error == 3)
    {
        printf("Key must only contain alphabetic characters\n");
        return 1;
    }

    // Error 4
    else if (error == 4)
    {
        printf("Key must not contain repeated characters\n");
        return 1;
    }

    // Substitution key
    char* key = argv[1];

    // Ask user for plaintext
    char* plainText = get_string("plaintext: ");

    // Encrypt plain text
    char* cipherText = encrypt(plainText, key);

    // Print incrypted text
    printf("ciphertext: %s\n", cipherText);

}


int key_validation(char* k, int argc)
{
    // If user doens't provide a key
    if (argc != 2)
        return 1;

    // Key length
    int len = strlen(k);

    // Key must be 26 characters long
    if (len != 26)
        return 2;

    // Key must only contain lettes of the alphabet
    for (int i = 0; i < len; i++)
    {
        // If given letter is not a character, return error 3
        if (isdigit(k[i]))
            return 3;
    }

    // Array contain all the letters of the alphabet
    char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}

    // Variable count, if count reachs 26, that means key is valid
    int count = 0;

    // Iterate over each character in the key
    for (int i = 0; i < 26; i++)
    {
        // Iterate over each element in alphabet array
        for (int j = 0; j < 26; j++)
        {
            // Compare if key[i] character iguals to alphabet[j] character, if yes
            if (toupper(k[i]) == alphabet[j])
            {
                // Reassign the element[j] of the alphabet array to a "?" or any chracter other than the letters of the alphabet
                alphabet[j] = '?';
                count++;
            }

            // If key doesn't have repeated characters, return 0, valid key
            if (count == 26)
                return 0;
        }
    }

    // Key has repeated characters, invalid key
    return 4;
}

char* encrypt(char* text, char* k)
{
    // Iterate over plain text
    for (int i = 0; text[i] != '\0'; i++)
    {
        // If uppercase encypher character and uppercase it
        if (isupper(text[i]))
            text[i] = toupper(k[text[i] - 'A']);

        // If lower case encypher character and lower case it
        else if (islower(text[i]))
            text[i] = tolower(k[text[i] - 'a']);
    }

    // Return enciphered text
    return text;
}