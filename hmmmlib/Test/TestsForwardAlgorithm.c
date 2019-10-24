//
//  TestsForwardAlgorithm.c
//  hmmmmlib
//
//  Created by Thor Jakobsen on 30/08/2019.
//  Copyright © 2019 Thor Jakobsen. All rights reserved.
//

#include "TestsForwardAlgorithm.h"
#include "hmm.h"
#include "forward.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>

bool testForwardAlgorithm() {
    HMM * hmm = HMMCreate(2, 2);
    
    double transitionProbs[2][2] = {
        {0.5, 0.5},
        {0.3, 0.7}
    };
    
    double emissionProbs[2][2] = {
        {0.3, 0.7},
        {0.8, 0.2}
    };
    
    double initProbs[2] = {0.2, 0.8};
    
    hmm->initProbs = initProbs;
    int i;
    int j;
    for(i = 0; i < hmm->hiddenStates; i++){
        for(j = 0; j < hmm->hiddenStates; j++){
            hmm->transitionProbs[i*hmm->hiddenStates+j] = transitionProbs[i][j];
        }
    }
    for(i = 0; i < hmm->hiddenStates; i++){
        for(j = 0; j < hmm->observations; j++){
            hmm->emissionProbs[i*hmm->observations+j] = emissionProbs[i][j];
        }
    }
    
    const unsigned int observation[10] = {0, 0, 0, 0, 0, 1, 1, 0, 0, 0};
    const unsigned int obsLenght = 10;
    
    double * scaleFactor = calloc(obsLenght, sizeof(double));
    double * alpha = forward(hmm, observation, obsLenght, scaleFactor);
    
    double test[20] = {0.085714, 0.148330, 0.155707, 0.156585, 0.156690, 0.634280, 0.722736, 0.230843, 0.165653, 0.157773,
        0.914286, 0.851670, 0.844293, 0.843415, 0.843310, 0.365720, 0.277264, 0.769157, 0.834347, 0.842227};
    
    
    for(i = 0; i < hmm->hiddenStates; i++) {
        for (j = 0; j < obsLenght; j++){
            assert(fabs(alpha[i*obsLenght+j]-test[i*obsLenght+j]) < 0.00001);
        }
    }
    
    return true;
}