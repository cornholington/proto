/*
Problem

During summer time, old cities in Europe are swarming with tourists who roam the
streets and visit points of interest.

Many old cities were built organically and not according to some architecture
plan, but, strangely, their growth exhibits a similar pattern: the cities
started from three points of interest, with each pair being connected by a
bidirectional street; then, gradually, new points of interest were added. Any
new point of interest was connected by two new bidirectional streets to two
different previous points of interest which were already directly connected by a
street.  A tourist visiting such a city would like to do a tour visiting as many
points of interest as possible. The tour can start at any point of interest and
must end at the same point of interest. The tour may visit each street at most
once and each point of interest at most once (with the exception of the first
point of interest which is visited exactly twice).

You are given the description of how the city grew. Find the largest number of
different points of interest a single tour can visit in this city.

Input

The first line of the input file contains the number of cases, T. T test cases
follow.

Each case begins with the integer N - the total number of points of interest in
the city. Points are denoted with numbers from 1 to N; numbers 1, 2, and 3
denote the three original points when the city started, while numbers 4, ..., N
denote the other points in the order they were added to the city.

The next N-3 lines each contain a pair of space-separated integers A, B,
indicating that the corresponding point of interest was connected by streets to
points A and B. First of these lines corresponds to point number 4, second to
point number 5, etc.

Output

For each test case, output one line containing "Case #x: y", where x is the case
number (starting from 1) and y is the largest number of points of interest a
tour can visit in this city.

Limits

1 ≤ T ≤ 50.

Small dataset

4 ≤ N ≤ 15.

Large dataset

4 ≤ N ≤ 1000.

Sample

---------------
Input   Output

2       Case #1: 4
5       Case #2: 6
1 2
2 1
6
1 2
1 4
4 5

*/

#include <stdlib.h>
#include <stdio.h>

typedef struct poi poi;

struct poi {
   boolean visited;   /* visited or not */
   poi*    neighbors; /* link list of neighbors */
   poi*    next;      /* for list */
};

static char* getline(FILE* char* buf, int* buflen)
{

}

int main(void)
{
   poi* all;

   char* line;

   w
}
