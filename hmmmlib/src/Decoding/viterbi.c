#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "viterbi.h"


unsigned int* viterbi(HMM *hmm, const unsigned int *Y, const unsigned int T) {
    // Y is the data, T is the length of the data
    
    
    // allocate matrix[data][states]
    double* table = calloc(T*hmm->hiddenStates, sizeof(double*)); // freed before return in viterbi()

    
    // Compute initial probabilities
    for (unsigned int i = 0; i < hmm->hiddenStates; ++i) {
        table[0*hmm->hiddenStates+i] = log(hmm->initProbs[i]) + log(hmm->emissionProbs[i*hmm->observations+Y[0]]);
    }

    
    // Fill the table
    for (unsigned int i = 1; i < T; ++i) { 
        for (unsigned int k = 0; k < hmm->hiddenStates; ++k) {
            double value = -INFINITY;
            for (unsigned int j = 0; j < hmm->hiddenStates; ++j) {
                if (table[(i-1)*hmm->hiddenStates+j] + log(hmm->transitionProbs[j*hmm->hiddenStates+k]) > value) {
                    value = table[(i-1)*hmm->hiddenStates+j] + log(hmm->transitionProbs[j*hmm->hiddenStates+k]);
                }
            }
            table[i*hmm->hiddenStates+k] = log(hmm->emissionProbs[k*hmm->observations+Y[i]]) + value;
        }
    }

    
    // debug print table
    /* 
    printf("\n");
    for (int row = 0; row < T; row++) {
        for (int col = 0; col < hmm->hiddenStates; col++) {
            printf("%9.3f  ", table[row*hmm->hiddenStates + col]);
        }
        printf("\n");
    }
    printf("\n");
     */
   
    // Backtrack
    unsigned int* decodedStates = calloc(T, sizeof(int)); // freed by caller?
    unsigned int* decodedStateProbs = calloc(T, sizeof(int)); // freed by caller?
    

    // Find max value in last row in table[]
    unsigned int backtrackMaxIndex = 0; // initialization value
    double backtrackMaximum = -INFINITY;
    for (unsigned int m = 0; m < hmm->hiddenStates; m++) {
        if (table[((T-1) * hmm->hiddenStates ) + m] > backtrackMaximum) {
            backtrackMaxIndex = m;
            backtrackMaximum = table[(T-1) * hmm->hiddenStates + m];
            //printf("max is %f\n", backtrackMaximum);
        }
    }
    decodedStates[T-1] = backtrackMaxIndex;
    decodedStateProbs[T-1] = backtrackMaximum; // Hvis jeg gerne vil returnere denne, skal jeg så bare lægge den i enden på decodedStates ved returneringen?
    
    
    // finish backtracking
    for (unsigned int i = T-1; i > 0; i--) {
        for (unsigned int j = 0; j < hmm->hiddenStates; j++) {
            if (table[(i-1)*hmm->hiddenStates + j] + log(hmm->transitionProbs[j*hmm->hiddenStates + decodedStates[i]]) + log(hmm->emissionProbs[decodedStates[i]*hmm->observations + Y[i]]) == table[i*hmm->hiddenStates + decodedStates[i]]) {
                decodedStates[i-1] = j;
                break;
            }
        }
    }


    free(table);
    free(decodedStateProbs);
    return decodedStates;

    
}
