#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Create ColorPoint struct with data members a, r, g, b, of type long
struct ColorPoint {
	long a;
	long r;
	long g;
	long b;
};


struct ColorPoint** create2DArray(int n) {
	// Array to hold a pointer value for the beginning of each row
	struct ColorPoint **points = (struct ColorPoint **)malloc(n * sizeof(struct ColorPoint *));
	for (int i = 0; i < n; ++i) {
		// Array to hold a set of values for each row
		points[i] = (struct ColorPoint *)malloc(n * sizeof(struct ColorPoint));
		for (int j = 0; j < n; ++j) {
			// Init the ColorPoint struct
			points[i][j].a = rand();
			points[i][j].r = rand();
			points[i][j].g = rand();
			points[i][j].b = rand();
		}
	}
	return points;
}
// Function to deallocate or free data in 2Darray
void free2DArray(struct ColorPoint** points, int n) {
	for (int i = 0; i < n; ++i) {
		free(points[i]);//initiating free call
	}
	free(points);
}

// Function f sums the j values in row i 
void f(struct ColorPoint **points, int n, long *dest) {
	long sum = 0;
	// Traversing with i and j and preforming addition of our points array with our long a,r,g,b
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sum += points[i][j].a;
			sum += points[i][j].r;
			sum += points[i][j].g;
			sum += points[i][j].b;
		}
	}
	*dest = sum;
}
/*
Initial Cache = EMPTY
points[0][0].a = Address 0 // Tag = 0 (MISS)
points[0][0].r = Address 8 // Tag = 0 (HIT)
points[0][0].g = Address 16 // Tag = 0 (HIT)
points[0][0].b = Address 24 // Tag = 0 (HIT)
points[0][1].a = Address 32 // Tag = 0 (HIT)
points[0][1].r = Address 40 // Tag = 0 (HIT)
points[0][1].g = Address 48 // Tag = 0 (HIT)
points[0][1].b = Address 56 // Tag = 0 (HIT)

This pattern will not continue past our 56th address because after the 56th address (64 bits), we have [0][2]
being accessed and put into our 64 bit cache which makes the the system purge all values [0][0]
since the values of [0][2] are now being stored. Essentially the cache is making room for the
incoming data.
*/

// Function g sums the i values in rows j
void g(struct ColorPoint **points, int n, long *dest) {
	long sum = 0;
	// Traversing with i and j and preforming addition of our points array with our long a,r,g,b
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sum += points[j][i].a;
			sum += points[j][i].r;
			sum += points[j][i].g;
			sum += points[j][i].b;
		}
	}
	*dest = sum;
}
/*
	Initial Cache = EMPTY
	points[0][0].a = Address 0 // Tag = 0 (MISS)
	points[0][0].r = Address 8 // Tag = 0 (HIT)
	points[0][0].g = Address 16 // Tag = 0 (HIT)
	points[0][0].b = Address 24 // Tag = 0 (HIT)
	points[1][0].a = Address 128 (32*4) // Tag = 2 (MISS)
	points[1][0].r = Address 136 // Tag = 2 (HIT)
	points[1][0].g = Address 144 // Tag = 2 (HIT)
	points[1][0].b = Address 152 // Tag = 2 (HIT)

	This pattern should continue up until it reaches the 64B capacity. At that time it will purge the data
	and reload it in the same pattern with the new data (Similar to procedure f)
	*/

    /* Function f was faster because we are traversing in the order of [i][j] which is a
    contiguous block of memory which creates less cache misses which means its quicker.
    function g was pretty slow in comparison because g() traverses in the order of [j][i]
    which is not a contiguous block of memory (not stored next to each other) meaning that
    more caches misses will occur which then makes the computation slower. */
    
int main() {
	int n = 2048;
	// Double pointer
	struct ColorPoint **points = create2DArray(n);
	long dest;
	// Variables of type clock_t
	clock_t start, stop;

	// Start the clock and preform our function call to f() then stop the clock and print to screen
	start = clock();
	for (int i = 0; i < 100; i++) {
		f(points, n, &dest);
	}
	stop = clock();
	printf("The time to run function f is %f seconds. \n", (double)(stop - start)/CLOCKS_PER_SEC);

	// Start the clock and preform our function call to g() then stop the clock and print to screen
	start = clock();
	for (int i = 0; i < 100; i++) {
		g(points, n, &dest);
	}
	stop = clock();
	printf("The time to run function g is %f seconds. \n", (double)(stop - start)/CLOCKS_PER_SEC);
	// Freeing the points and n values in the 2Darray
	free2DArray(points, n);

	return 0;
}


