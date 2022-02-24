// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    int generationpersonexists = 0;
    int currentgeneration = generations;
    int randomparentallele = 0;
    // TODO: Allocate memory for new person
    person *generationperson = malloc(sizeof(person));
    if (generationperson == NULL)
    {
        return NULL;
    }
    generationpersonexists = 1;

    // Generation with parent data
    if (generations > 1)
    {
        // TODO: Recursively create blood type histories for parents
        currentgeneration = currentgeneration - 1;
        for (int i = 0; i < 2; i = i + 1)
        {
            generationperson->parents[i] = create_family(currentgeneration);
        }
        generations = currentgeneration;
        // TODO: Randomly assign child alleles based on parents
        for (int a = 0; a < 2; a = a + 1)
        {
            randomparentallele = rand() % 2;
            generationperson->alleles[a] = generationperson->parents[a]->alleles[randomparentallele];
        }
    }

    // Generation without parent data
    else
    {
        // TODO: Set parent pointers to NULL
        for (int ap = 0; ap < 2; ap = ap + 1)
        {
            generationperson->parents[ap] = NULL;
        }
        // TODO: Randomly assign alleles
        for (int aa = 0; aa < 2; aa = aa + 1)
        {
            generationperson->alleles[aa] = random_allele();
        }
    }

    // TODO: Return newly created person
    if (generationpersonexists == 1)
    {
        return generationperson;
    }
    return NULL;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    person *originalperson = p;
    person *parentsofperson[] = {NULL, NULL};
    person *currentparent = NULL;
    int parentsfreecomplete = 0;

    // TODO: Handle base case
    if (p == NULL)
    {
        return;
    }

    // TODO: Free parents
    if (p->parents[0] != NULL && p->parents[1] != NULL)
    {
        for (int i = 0; i < 2; i = i + 1)
        {
            parentsofperson[i] = p->parents[i];
        }
        currentparent = parentsofperson[0];
        free_family(parentsofperson[0]);
        currentparent = parentsofperson[1];
        free_family(parentsofperson[1]);
    }
    else
    {
        free(currentparent);
    }
    // TODO: Free child
    free(originalperson);
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
