#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to encrypt a single character
char encrypt_char(char c, int key);

int main(int argc, string argv[])
{
    // Check for correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert the key from string to an integer
    int key = atoi(argv[1]);

    // Get user input
    string plaintext = get_string("plaintext: ");

    // Encrypt and print the ciphertext
    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char encrypted_char = encrypt_char(plaintext[i], key);
        printf("%c", encrypted_char);
    }

    printf("\n");

    return 0;
}

char encrypt_char(char c, int key)
{
    if (isalpha(c))
    {
        char base = isupper(c) ? 'A' : 'a';
        return (c - base + key) % 26 + base;
    }
    else
    {
        return c;
    }
}
