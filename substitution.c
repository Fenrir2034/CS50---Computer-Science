#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Function prototypes
bool validate_key(char *key);
void encrypt_message(char *plaintext, char *key);

int main(int argc, char *argv[])
{
    // Check for correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // Validate the key
    if (!validate_key(argv[1]))
    {
        printf("Invalid key\n");
        return 1;
    }

    // Get user input for plaintext
    char plaintext[100];
    printf("plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    // Encrypt the message
    printf("ciphertext: ");
    encrypt_message(plaintext, argv[1]);

    // Print a newline and exit successfully
    printf("\n");
    return 0;
}

// Function to validate the key
bool validate_key(char *key)
{
    // Check for the key length
    if (strlen(key) != 26)
    {
        return false;
    }

    // Check for non-alphabetic characters and duplicate letters
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        for (int j = i + 1; j < 26; j++)
        {
            if (key[i] == key[j] || tolower(key[i]) == tolower(key[j]))
            {
                return false;
            }
        }
    }

    return true;
}

// Function to encrypt the message
void encrypt_message(char *plaintext, char *key)
{
    // Implement substitution cipher logic here
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        if (isalpha(plaintext[i]))
        {
            char original_case = isupper(plaintext[i]) ? 'A' : 'a';
            int index = tolower(plaintext[i]) - 'a'; // Adjusted indexing to start from 'a'
            printf("%c", isupper(plaintext[i]) ? toupper(key[index]) : tolower(key[index]));
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
}
