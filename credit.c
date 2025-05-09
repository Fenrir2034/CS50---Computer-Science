#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user for a credit card number
    long long card_number;
    do
    {
        card_number = get_long("Number: ");
    }
    while (card_number <= 0);

    // Calculate the checksum using Luhn's algorithm
    int sum = 0;
    int digit_count = 0;

    long long temp_number = card_number; // Save a copy for checking card type

    while (card_number > 0)
    {
        int digit = card_number % 10;

        if (digit_count % 2 == 1)
        {
            // Multiply every other digit by 2
            digit *= 2;

            // Add the digits of the product
            sum += digit % 10 + digit / 10;
        }
        else
        {
            // Add digits that weren't multiplied by 2
            sum += digit;
        }

        card_number /= 10;
        digit_count++;
    }

    // Check if the card number is valid
    if (sum % 10 == 0)
    {
        // Determine the card type based on the first digits
        if ((digit_count == 13 || digit_count == 16) && temp_number / 1000000000000 == 4)
        {
            printf("VISA\n");
        }
        else if (digit_count == 16 && (temp_number / 100000000000000 == 51 || temp_number / 100000000000000 == 52 ||
                                       temp_number / 100000000000000 == 53 || temp_number / 100000000000000 == 54 ||
                                       temp_number / 100000000000000 == 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((digit_count == 15) && (temp_number / 10000000000000 == 34 || temp_number / 10000000000000 == 37))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}
