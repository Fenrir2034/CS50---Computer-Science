#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the person structure
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

// Function to generate a random allele ('A', 'B', or 'O')
char random_allele()
{
    char alleles[] = {'A', 'B', 'O'};
    return alleles[rand() % 3];
}

// Function to create a family with a specified number of generations
person *create_family(int generations)
{
    // Allocate memory for new person
    person *new_person = malloc(sizeof(person));

    // Check if there are more generations left to create
    if (generations > 1)
    {
        // Create two new parents for the current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // Set parent pointers for the current person
        new_person->parents[0] = parent0;
        new_person->parents[1] = parent1;

        // Randomly assign current person's alleles based on the alleles of their parents
        new_person->alleles[0] = parent0->alleles[rand() % 2];
        new_person->alleles[1] = parent1->alleles[rand() % 2];
    }
    else
    {
        // Set parent pointers to NULL (no more generations left to simulate)
        new_person->parents[0] = NULL;
        new_person->parents[1] = NULL;

        // Randomly assign alleles
        new_person->alleles[0] = random_allele();
        new_person->alleles[1] = random_allele();
    }

    // Return newly created person
    return new_person;
}

// Function to print the family tree of blood types
void print_family(person *p, int depth)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print the current person's blood type and generation
    printf("Child (Generation %d): blood type %c%c\n", depth, p->alleles[0], p->alleles[1]);

    // Print parents recursively
    for (int i = 0; i < 2; i++)
    {
        if (p->parents[i] != NULL)
        {
            printf("%*sParent (Generation %d): blood type %c%c\n", 4 * (depth + 1), "", depth + 1, p->parents[i]->alleles[0], p->parents[i]->alleles[1]);

            // Print grandparents recursively
            for (int j = 0; j < 2; j++)
            {
                if (p->parents[i]->parents[j] != NULL)
                {
                    printf("%*sGrandparent (Generation %d): blood type %c%c\n", 4 * (depth + 2), "", depth + 2, p->parents[i]->parents[j]->alleles[0], p->parents[i]->parents[j]->alleles[1]);
                }
            }
        }
    }
}

// Function to free memory recursively for a person and their ancestors
void free_family(person *p)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Free parents recursively
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Free the current person
    free(p);
}

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Specify the number of generations
    int GENERATIONS = 3;

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);

    return 0;
}


