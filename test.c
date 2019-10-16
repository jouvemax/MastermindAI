#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> // pow()
#include <assert.h>

typedef enum {YELLOW, BLUE, GREEN, RED, PINK, ORANGE} color;

typedef struct {
	size_t size;
	color* elements;
	
	} Combination;

// --------------------------------------------------
Combination create_combination(size_t size)
{
	Combination r;
	r.size = size;
	
	r.elements = calloc(size, sizeof(color)); // tester si le pointeur est nul
	
	return r;
}

// --------------------------------------------------

//fonction libérant la mémoire allouée pour une combination passée en argument

void destroy_combination(Combination c) 
{
	free(c.elements);
}

int next_combination(Combination c) 
{
	int retour = 0;
for (int i = 0; i < c.size ; ++i) {
	if (c.elements[i] != 5) {
		retour = 1; 
	}
}

	if (0 == retour) { return retour;}
	else {
		
		int increment = 1;
		
		for (int j = 0; j < c.size; ++j) {
			
			if (increment) {
				c.elements[j] = (c.elements[j] + 1) % 6;
				
					if (0 == c.elements[j]) {
						increment = 1;
						}
					else {
						increment =  0;}
				
				}
			}
				return retour;
			}
		
}

void print_combination(const Combination combination)
{
    for (size_t i = 0; i < combination.size; ++i) {
        if (i > 0) putchar(' ');
        switch(combination.elements[i]) {
        case YELLOW:
            putchar('Y');
            break;
        case BLUE:
            putchar('B');
            break;
        case GREEN:
            putchar('G');
            break;
        case RED:
            putchar('R');
            break;
        case PINK:
            putchar('P');
            break;
        case ORANGE:
            putchar('O');
            break;
        default:
            printf("\nERROR\n");
            printf("Unexpected color %d\n", combination.elements[i]);
        }
    }
    putchar('\n');
}

typedef struct {
	size_t positions;
	size_t colors;
} Answer;

int ask(Combination c, Answer a) 
{
	print_combination(c);
	int i = 0;
	int j = 0;
	
	
	printf("Please score attempt (positions, colors) : ");
	scanf("%d", &i);
	getc(stdin);
	scanf("%d", &j);
	
	
	
	if (i < 0 || j < 0) {
		printf("Unable to parse answer. Aborting.");
		return 1;
		}
	else {
			a.positions = i;
			a.colors = j;
			
		if (a.positions == c.size) {
			printf("Found solution: ");
			print_combination(c);
			return 1;
			}
		else {
			return 0;
			}
		
		}
		
}

void solve_brute_force(size_t size)
{
	Combination c = create_combination(size);
	Answer a = {0, 0};
	
	while (!ask(c, a)) {
		next_combination(c);
		}
}

size_t combination_to_index(const Combination combination)
{
size_t retour = 0;

for (int i = combination.size -1; i >= 0; --i) {
	retour += combination.elements[i] * pow(6, i);
	}
return retour;
}

Combination* combination_from_index(size_t index, Combination* combination)
{
int ind = index;
int pos = 0;
for (int i = 0; i < combination->size; ++i) {
	pos = ind%6;
	combination->elements[i] = pos;
	ind /= 6;
	}

return combination;

}

int main(void) {
	
	Combination c = create_combination(4);
	
	
do {
	int i = 0;
	 i = combination_to_index(c);
	 combination_from_index(i, &c);
	 printf("%d\n", i);
	 print_combination(*combination_from_index(i, &c));
}while (next_combination(c));
}



