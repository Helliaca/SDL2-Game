#ifndef RANDOM_H
#define RANDOM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

inline void init() {
	srand(time(NULL));
}

//Return random float
inline float getRandDecimal() {
  return (float)rand()/RAND_MAX;
}

//Return random integer in given range
inline int getRandInteger(int min, int max) {
	return min + rand() % (max - min);
}


#endif // RANDOM_H
