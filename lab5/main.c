/* Code to simulate rolling three six-sided dice (D6)
 * User first types in seed value
 * Use seed value as argument to srand()
 * Call roll_three to generate three integers, 1-6
 * Print result "%d %d %d "
 * If triple, print "Triple!\n"
 * If it is not a triple but it is a dobule, print "Double!\n"
 * Otherwise print "\n"
 */
#include <stdio.h>
#include "dice.h"
#include <stdlib.h>

int main()
{
	int seed;
	printf("Enter seed:\n");
	scanf("%d", &seed);
	srand(seed);

	int x, y, z;
	roll_three(&x, &y, &z);
	printf("%d %d %d", x, y, z);

	if ((x==y) && (y==z))
	{
		printf(" Triple!\n");
	}
	else if((x==y)||(y==z)||(x==z))
	{
		printf(" Double!\n");
	}
	else
	{
		printf("\n");
	}
	return 0;
}
