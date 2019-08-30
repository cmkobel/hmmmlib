#include <stdio.h>
#import "hmm.h"

/*
 
 Returns the likeliyhood for observing a sequence Y of length T
 given a HMM hmm
 
 */
double forward(HMM *hmm, const int *Y, const int T);
