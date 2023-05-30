#include <math.h>

#define BIT(x) ( pow(2 , x) )
#define SETBIT(x,p) ( x | (1 << p) )
#define CLEARBIT(x,p) ( x & ~(1 << p) )
#define GETBIT(x,p) ( (x >> p) % 2 )
#define TOGGLEBIT(x,p) ( x ^ (1 << p) )
/* Loop related Macros */
// Example: RANGE (i, 10, 20)
// it will be 10,11,12,13,14,15,16,17,18,19,20
// Example: RANGE (i, 5, -5)
// it will be 5,4,3,2,1,0,-1,-2,-3,-4,-5
#define RANGE(i,y,x) ( i = y ; i != (x+((x-y)/abs(x-y))) ; i += ((x-y)/(abs(x-y))) )

// FOREACH (item, array)
// A C implementation of foreach loop, it will go through each element of an array , and will perform operations on each element as returned into pointer item variable.
#define FOREACH(i,A) for( size_t ct = 0 ; ct < sizeof(A)/sizeof(A[0]) ; ct++ )\
{\
  A[ct] = i;\
}

