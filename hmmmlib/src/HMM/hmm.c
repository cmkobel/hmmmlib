
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "hmm.h"
#include "forward.h"
#include "backward.h"
#include "forward_blas.h"
#include "backward_blas.h"
#include "forward_csr.h"
#include "backward_csr.h"

HMM * HMMConventional(const unsigned int hiddenStates, const unsigned int observations) {
    HMM * newHMM = calloc(1, sizeof(HMM));

    newHMM->forward = forward;
    newHMM->backward = backward;

    newHMM->hiddenStates = hiddenStates;
    newHMM->observations = observations;

    newHMM->initProbs = calloc(newHMM->hiddenStates ,sizeof(double));
    newHMM->transitionProbs = calloc(newHMM->hiddenStates*newHMM->hiddenStates, sizeof(double));
    newHMM->emissionProbs = calloc(newHMM->hiddenStates*newHMM->observations, sizeof(double));

    return newHMM;
}

HMM * HMMBLAS(const unsigned int hiddenStates, const unsigned int observations) {

    HMM * newHMM = calloc(1, sizeof(HMM));

    newHMM->forward = forward_blas;
    newHMM->backward = backward_blas;

    newHMM->hiddenStates = hiddenStates;
    newHMM->observations = observations;

    newHMM->initProbs = calloc(newHMM->hiddenStates ,sizeof(double));
    newHMM->transitionProbs = calloc(newHMM->hiddenStates*newHMM->hiddenStates, sizeof(double));
    newHMM->emissionProbs = calloc(newHMM->hiddenStates*newHMM->observations, sizeof(double));

    return newHMM;
}

HMM * HMMCsr(const unsigned int hiddenStates, const unsigned int observations) {

    HMM * newHMM = calloc(1, sizeof(HMM));

    newHMM->forward = forward_csr;
    newHMM->backward = backward_csr;

    newHMM->hiddenStates = hiddenStates;
    newHMM->observations = observations;

    newHMM->initProbs = calloc(newHMM->hiddenStates ,sizeof(double));
    newHMM->transitionProbs = calloc(newHMM->hiddenStates*newHMM->hiddenStates, sizeof(double));
    newHMM->emissionProbs = calloc(newHMM->hiddenStates*newHMM->observations, sizeof(double));

    return newHMM;
}

//should be static
bool valdidateHMM(const HMM *hmm){

    double sum;

    double epsilon = 0.00001;

    // Init probs.
    sum = 0.0;
    for (unsigned i = 0; i < hmm->hiddenStates; i++) {
        sum += hmm->initProbs[i];
    }
    if(fabs(sum - 1.0) > epsilon) {
        printf("Error: the sum of initProbs is %f\n", sum);
        return false;
    }


    // Transition matrix
    for (unsigned i = 0; i < hmm->hiddenStates; i++) {
        sum = 0.0;
        for (unsigned j = 0; j < hmm->hiddenStates; j++) sum += hmm->transitionProbs[i*hmm->hiddenStates+j];
        if (fabs(sum-1.0) > epsilon) {
            printf("Error: the sum of row %d in transitionProbs is %f", i, sum);
            return false;
        }
    }

    // Emission matrix
    for (unsigned i = 0; i < hmm->hiddenStates; i++) {
        sum = 0.0;
        for (unsigned j = 0; j < hmm->observations; j++) sum += hmm->emissionProbs[i*hmm->observations+j];
        if (fabs(sum-1.0) > epsilon) {
            printf("Error: the sum of row %d in emissionProbs is %f", i, sum);
            return false;
        } 
    }

    return true;
}

void F(HMM *hmm, const unsigned int *Y, const unsigned int T, double * scalingFactor, double * alpha) {

    hmm->forward(hmm, Y, T, scalingFactor, alpha); // Writes to scalingFactor

}

void B(HMM *hmm, const unsigned int *Y, const unsigned int T, double * scalingFactor, double * beta) {

    hmm->backward(hmm, Y, T, scalingFactor, beta); // Reads from scalingFactor

}

//should be static
void printHMM(const HMM *hmm){

    unsigned int i;
    unsigned int j;

    //Printing init probs
    printf("Init probs\n");
    for(i=0; i < hmm->hiddenStates; i++){
        printf("%f, ", hmm->initProbs[i]);
    }

    printf("\n\n\n");

    //Print the transitionpos
    printf("Transition probs\n");
    for(i = 0; i < hmm->hiddenStates; i++) {
        for (j = 0; j < hmm->hiddenStates; j++){
            printf("%f, ", hmm->transitionProbs[i*hmm->hiddenStates+j]);
        }
        printf("\n");
    }

    printf("\n\n\n");

    //Print the emissionprobs
    printf("Emission probs\n");
    for(i = 0; i < hmm->hiddenStates; i++) {
        for (j = 0; j < hmm->observations; j++){
            printf("%f, ", hmm->emissionProbs[i*hmm->observations+j]);
        }
        printf("\n");
    }

    printf("\n\n\n");
}

void HMMDeallocate(HMM * hmm){

    //printf("Trying to deallocate ...");
    free(hmm->initProbs);
    free(hmm->emissionProbs);
    free(hmm->transitionProbs);
    //free(hmm);
    //printf(" success.\n");

}




