#include <cs50.h>
#include <stdio.h>

int calculateyears(int startpopulationtogrow, int populationtogrowend);

int main(void)
{
    int population;
    int endpopulation;
    int years;

    // TODO: Prompt for start size
    do
    {
        population = get_int("Start size: ");
    }
    while (population < 9);

    // TODO: Prompt for end size
    do
    {
        endpopulation = get_int("End size: ");
    }
    while (endpopulation < population);

    // TODO: Calculate number of years until we reach threshold
    years = calculateyears(population, endpopulation);

    // TODO: Print number of years
    //printf("population:%i\n",population);
    printf("Years: %i\n", years);
}

int calculateyears(int startpopulationtogrow, int populationtogrowend)
{
    int yearstogrowpopulation = 0;
    while (startpopulationtogrow < populationtogrowend)
    {
        startpopulationtogrow = startpopulationtogrow + (startpopulationtogrow / 3) - (startpopulationtogrow / 4);
        yearstogrowpopulation = yearstogrowpopulation + 1;
    }
    return yearstogrowpopulation;
}
