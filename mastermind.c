#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> // pow()
#include <assert.h>


// ==== BitSet ==========================================================

// define here the BitSet type

typedef struct {
	size_t size;
	char* bytes;
	
	} BitSet;
	

/** --------------------------------------------------
 * @brief creates a BitSet structure of a given size, specified as the number of wanted bits.
 * @param size number of wanted bits
 * @return the newly created (dynamically allocated) BitSet structure
 */
BitSet create_bitset(size_t size)
{
    BitSet result = { 0, NULL };
    const size_t extra = size % 8 > 0 ? 1 : 0;
    result.bytes = calloc(size / 8 + extra, sizeof(char));
    if (result.bytes != NULL) {
        result.size = size;
    }
    return result;
}



/** --------------------------------------------------
 * @brief free the memory which was allocated for the BitSet *b.
 * @param b the pointer to the BitSet
 */
void destroy_bitset (BitSet* b) 
{
	if (b != NULL) {
	free(b->bytes);
	b->bytes = NULL;
	}
}
/** --------------------------------------------------
 * @brief gets the bit value at bit position `index`
 * @param bitset the BitSet structure to read from
 * @param index the bit position to read
 * @return 0 or 1 according to bit value
 */
int bitset_get(const BitSet bitset, size_t index)
{
    if (index >= bitset.size) return 0;
    return (bitset.bytes[index / 8] >> (index % 8)) & 0x1;
}

/** --------------------------------------------------
 * @brief sets the bit value at bit position `index`
 * @param bitset the BitSet structure to write to
 * @param index the bit position to overwrite
 * @param bit 0 or 1 value to be set
 */
void bitset_set(BitSet* bitset, size_t index, int bit)
{
    assert(bitset != NULL); // this is a tool function
    if (index > bitset->size) return;
    char* prev = bitset->bytes + (index / 8);
    char shifted = 0x1 << (index % 8);
    *prev = bit ? (*prev | shifted) : (*prev & (-1 ^ shifted));
}


// ==== Combination =====================================================

// define here the Combination type and all the required functions


typedef enum {YELLOW, BLUE, GREEN, RED, PINK, ORANGE} color;

typedef struct {
	size_t size;
	color* elements;
	
	} Combination;

// --------------------------------------------------

/** --------------------------------------------------
 * @brief creates a Combination structure of a given size.
 * @param size of the combination
 * @return the newly created (dynamically allocated) Combination structure
 */
Combination create_combination(size_t size)
{
	Combination r;
	r.elements = calloc(size, sizeof(color));
	if (r.elements != NULL) {
	r.size = size;
}
	return r;
}

// --------------------------------------------------


/** --------------------------------------------------
 * @brief free the memory which was allocated for the Combination *c.
 * @param c a pointer to the Combination
 */
void destroy_combination(Combination* c) 
{
	if (c != NULL) {
	free(c->elements);
	c->elements = NULL;
	}
}

/** --------------------------------------------------
 * @brief modifies the Combination *c to obtain the next one if possible.
 * @param c a pointer to the Combination
 * @return 1 if there is a next combination, 0 otherwise
 */
int next_combination(const Combination* c) 
{
	
	if (c == NULL) {return 0;}
	
	int retour = 0;
	
	for (size_t i = 0; i < c->size ; ++i) {
		if (c->elements[i] != 5) {
		retour = 1; 
		}
	}

	if (0 == retour) { return retour;}
	else {
		
		int increment = 1;
		
		for (size_t j = 0; j < c->size; ++j) {
			
			if (increment) {
				c->elements[j] = (c->elements[j] + 1) % 6;
				
					if (0 == c->elements[j]) {
						increment = 1;
						}
					else {
						increment =  0;}
				
				}
			}
				return retour;
			}
}



/** --------------------------------------------------
 * @brief gives the corresponding index for a given Combination.
 * @param combination a given Combination
 * @return the index
 */
size_t combination_to_index(const Combination combination)
{
	size_t retour = 0;

	for (int i = combination.size -1; i >= 0; --i) {
	retour += combination.elements[i] * pow(6, i);
	}
	return retour;
}

// --------------------------------------------------
/** --------------------------------------------------
 * @brief finds the Combination that corresponds to a given index.
 * @param index the given index
 * @param combination a pointer to the Combination that will be modified
 * @return the pointer to the modified Combination
 */
Combination* combination_from_index(size_t index, Combination* const combination)
{
	if (combination == NULL) {return NULL;}
	int ind = index;
	int pos = 0;
	for (size_t i = 0; i < combination->size; ++i) {
	pos = ind%6;
	combination->elements[i] = pos;
	ind /= 6;
	}

	return combination;

}


// --------------------------------------------------
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


// ==== Answer ==========================================================

// define here the Answer type and all the required functions

typedef struct {
	size_t positions;
	size_t colors;
} Answer;

/** --------------------------------------------------
 * @brief prints the proposed Combination and the user is asked for his answers
 * @param c the proposed Combination
 * @param a a pointer to the Answer that will be modified according to the user answer
 * @return 1 if the program has to stop or 0 if it has to continue
 */
int ask(const Combination c, Answer* a) 
{
	if (a == NULL) {return 1;}
	print_combination(c);
	int i = 0;
	int j = 0;
	
	
	printf("Please score attempt (positions, colors): ");
	fflush(stdout);
	int scan = scanf("%d %d", &i, &j);

	getc(stdin);
	
	
	
	if (i < 0 || j < 0 || scan != 2) {
		printf("Unable to parse answer. Aborting.");
		fflush(stdout);
		return 1;
		}
	else {

		a->positions = i;
		a->colors = j;
		
		if (a->positions == c.size) {
			printf("Found solution: ");
			fflush(stdout);
			print_combination(c);
			return 1;
			}
		else {
			return 0;
			}
		
		}
		
}

// ==== Solvers =========================================================

// define here the Solver_support type and all the required functions
typedef struct {
	BitSet b;
	Combination user;
	Combination help;
	
} Solver_support;

/** --------------------------------------------------
 * @brief creates a Solver_support structure for a game of a given size.
 * @param size size of the Solver_support
 * @return the newly created (dynamically allocated) Solver_support structure
 */
Solver_support create_Solver_support(size_t size) 
{
	Solver_support s;
	s.b = create_bitset(pow(6, size));
	s.user = create_combination(size);
	s.help = create_combination(size);	
	return s;
}

/** --------------------------------------------------
 * @brief free the memory which was allocated for the Solver_support *s.
 * @param s a pointer to the Solver_support
 */
void destroy_Solver_support(Solver_support* s) 
{
	if (s != NULL) {
	destroy_bitset(&(s->b));
	destroy_combination(&(s->user));
	destroy_combination(&(s->help));
	}
}

// --------------------------------------------------

void solve_brute_force(size_t size)
{
	Combination c = create_combination(size);
	Answer a = {0, 0};
	
	while (!ask(c, &a)) {
		next_combination(&c);
		}
	destroy_combination(&c);
}

// --------------------------------------------------
int score_attempt(const Combination* attempt, const Combination* result, Answer* ans)
{
    if (ans     == NULL) return 0;
    ans->colors    = 0;
    ans->positions = 0;
    if (result  == NULL) return 0;
    if (attempt == NULL) return 0;
    if (attempt->size != result->size) return 0;

    int* used = calloc(attempt->size, sizeof(int));
    if (used == NULL) return 0;

    // Scoring positions
    for (size_t i = 0; i < attempt->size; ++i) {
        if (attempt->elements[i] == result->elements[i]) {
            ++(ans->positions);
            used[i] = 1;
        }
    }

    // Scoring colors
    for (size_t i = 0; i < attempt->size; ++i) {
        if (attempt->elements[i] != result->elements[i]) {
            int found = 0;
            for (size_t j = 0; !found && (j < attempt->size); ++j) {
                if (i != j && !used[j] && (attempt->elements[i] == result->elements[j])) {
                    ++(ans->colors);
                    used[j] = 1;
                    found = 1;
                }
            }
        }
    }

    free(used);
    return 1;
}

/** --------------------------------------------------
 * @brief check if all the combinations are not already eliminated.
 * @param b a BitSet
 * @return 1 if a Combination isn't eliminated, 0 otherwise
 */
int checkBitset(const BitSet b) {
	int a = 0;
	for (size_t i = 0; i < b.size; ++i) {
		if(bitset_get(b, i) == 0) {
			a = 1;
			}
		}
	return a;
	}
// --------------------------------------------------
/** --------------------------------------------------
 * @brief ask the user to give his answer and eliminates the Combinations that are not possible.
 * @param count pointer to a size_t that represents the number of Combinations that are not eliminated yet
 * @param s pointer the a Solver_support
 * @return 1 if it can still elminate combinations, 0 otherwise
 */
int review_combinations(Solver_support* s, size_t* count)
{
	
	
    assert(s != NULL); // review_combination() is a tool function so this should never happen
    Answer a = {0, 0};
    
	if (!checkBitset(s->b)) {
		return 0;}
    
    if (ask(s->user, &a)) {
		return 0;
		}
	else {
		
		
		for (int i = 0; i < pow(6, s->user.size); ++i) {

			
			Answer b;
			score_attempt(combination_from_index(i, &(s->help)), &(s->user), &b);
		
			if (a.positions != b.positions || a.colors != b.colors) {
				
				
				if (count != NULL && bitset_get(s->b, i) == 0) 
				{
				*count -= 1; 
				}
				
				bitset_set(&(s->b), i, 1);
				
				}
				
			}
		
		}
		return 1;
		}
    
    


// --------------------------------------------------
void solve_with_bitset(size_t size)
{
	Solver_support s = create_Solver_support(size);



	while (review_combinations(&s, NULL)) {
	
	
	int i = combination_to_index(s.user);
	
	while (bitset_get(s.b, i) == 1) {
		
		i++;
	
		
	}
	combination_from_index(i, &(s.user));
	
	
	}
	destroy_Solver_support(&s);
}


// --------------------------------------------------
/** --------------------------------------------------
 * @brief compute the index of the next combination that will be proposed to the user.
 * @param size size of a Combination
 * @param cardR cardinality of the set R
 * @param s pointer to the Solver_support
 * @return the index of the next combination
 */
int next_proposition(size_t size, int cardR, Solver_support* s) {
	
	size_t max = 0;
	int index = 0;
		for (int j = 0; j < pow(6, size); ++j) 
			{
				int tab[size+1][size+1];
				for (int o = 0; o < size+1; ++o) {
					for (int p = 0; p < size+1; ++p) {
						tab[o][p] = 0;
						}}
				int maxHi = -1;
				for (int k = 0; k < pow(6, size); ++k) 
				{
					if (bitset_get(s->b, k) == 0) {
						Answer b;
						score_attempt(combination_from_index(j, &(s->help)), combination_from_index(k, &(s->user)), &b);
						tab[b.positions][b.colors] += 1;
						}
				}
				for (int n = 0; n < size+1; ++n) 
						{
					for (int m = 0; m < size+1; ++m) 
							{
							if (tab[n][m] > maxHi) maxHi = tab[n][m];
							}
						}
				
			if ((cardR - maxHi) == max) {
				if (bitset_get(s->b, index) == 1 && bitset_get(s->b, j) == 0)
					{
						max = cardR - maxHi;
						index = j;
					}
				
				
				 }	
				
			if ((cardR - maxHi) > max) {
				max = cardR - maxHi;
				index = j;
				}
			}
			
		return index;
	
	}
void solve_knuth(size_t size)
{
	Solver_support s = create_Solver_support(size);

	for (int i = size-1; i >= size - size/2; --i) {
	s.user.elements[i] = 1;
	}
	
	int cardR = pow(6, size);

	while (review_combinations(&s, (size_t*)(&cardR))) 
	{
	
	int index = next_proposition(size, cardR, &s);
		
	combination_from_index(index, &(s.user));
					
	}
	destroy_Solver_support(&s);
}



// ==== main() ==========================================================

int main(void)
{
    int size = 0;
    do {
        printf("What size (2, 3, 4, 5)? ");
        fflush(stdout);
        scanf("%d", &size);
    } while ((size != 2) && (size != 3) && (size != 4) && (size != 5));

    char strategy = '\0';
    do {
        printf("What strategy ([B]rute force, B[i]tfield, [K]nuth)? ");
        fflush(stdout);
        scanf(" %c", &strategy);
    } while ((strategy != 'B') && (strategy != 'i') && (strategy != 'K'));

    switch(strategy) {
    case 'B':
        solve_brute_force(size);
        break;

    case 'i':
        solve_with_bitset(size);
        break;

    case 'K':
        solve_knuth(size);
        break;
    }

    return 0;
}
