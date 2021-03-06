//
//  TestsForwardAlgorithm.c
//  hmmmmlib
//
//  Created by Thor Jakobsen on 30/08/2019.
//  Copyright © 2019 Thor Jakobsen. All rights reserved.
//

#include "TestsForwardAlgorithm.h"
#include "hmm.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>

bool testForwardAlgorithm() {
    HMM * hmmCon = HMMConventional(2, 2);
    HMM * hmmBLAS = HMMBLAS(2, 2);
    
    double transitionProbs[2][2] = {
        {0.5, 0.5},
        {0.3, 0.7}
    };
    
    double emissionProbs[2][2] = {
        {0.3, 0.7},
        {0.8, 0.2}
    };
    
    double initProbs[2] = {0.2, 0.8};
    
    for(unsigned int i = 0; i < hmmCon->hiddenStates; i++){
        hmmCon->initProbs[i] = initProbs[i];
        hmmBLAS->initProbs[i] = initProbs[i];
    }

    
    int i;
    int j;
    for(i = 0; i < hmmCon->hiddenStates; i++){
        for(j = 0; j < hmmCon->hiddenStates; j++){
            hmmBLAS->transitionProbs[i*hmmCon->hiddenStates+j] = transitionProbs[i][j];
            hmmCon->transitionProbs[i*hmmCon->hiddenStates+j] = transitionProbs[i][j];
        }
    }
    for(i = 0; i < hmmCon->hiddenStates; i++){
        for(j = 0; j < hmmCon->observations; j++){
            hmmBLAS->emissionProbs[i*hmmCon->observations+j] = emissionProbs[i][j];
            hmmCon->emissionProbs[i*hmmCon->observations+j] = emissionProbs[i][j];
        }
    }
    
    const unsigned int observation[10] = {0, 0, 0, 0, 0, 1, 1, 0, 0, 0};
    const unsigned int obsLenght = 10;
    
    double * alphaCon = calloc(hmmCon->hiddenStates*obsLenght, sizeof(double));
    double * alphaBLAS = calloc(hmmCon->hiddenStates*obsLenght, sizeof(double));
    
    double * scaleFactorAlpha = calloc(obsLenght, sizeof(double));
    double * scaleFactorBLAS = calloc(obsLenght, sizeof(double));
    
    F(hmmCon, observation, obsLenght, scaleFactorAlpha, alphaCon);
    F(hmmBLAS, observation, obsLenght, scaleFactorBLAS, alphaBLAS);
    
    double test[20] = {
        0.085714, 0.914286,
        0.148330, 0.851670,
        0.155707, 0.844293,
        0.156585, 0.843415,
        0.156690, 0.843310,
        0.634280, 0.365720,
        0.722736, 0.277264,
        0.230843, 0.769157,
        0.165653, 0.834347,
        0.157773, 0.842227
    };
    
    
    for(i = 0; i < obsLenght; i++){
        for(j = 0; j < hmmCon->hiddenStates; j++){
            assert(abs(alphaBLAS[i*hmmCon->hiddenStates+j]-test[i*hmmCon->hiddenStates+j] < 0.00001));
            assert(abs(alphaCon[i*hmmCon->hiddenStates+j]-test[i*hmmCon->hiddenStates+j] < 0.00001));
        }
    }
    
    assert(valdidateHMM(hmmCon) == true);
    assert(valdidateHMM(hmmBLAS) == true);

    HMMDeallocate(hmmCon);
    HMMDeallocate(hmmBLAS);
    
    
    HMM * hmm2 = HMMCsr(7, 4);
           
    double transitionProbs2[7][7] = {
       {0.0 , 0.0 , 0.9 , 0.1 , 0.0 , 0.0 , 0.0},
       {1.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0},
       {0.0 , 1.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0},
       {0.0 , 0.0 , 0.05 , 0.9 , 0.05 , 0.0 , 0.0},
       {0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 , 0.0},
       {0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0},
       {0.0 , 0.0 , 0.0 , 0.1 , 0.9 , 0.0 , 0.0}
    };

    double emissionProbs2[7][4] = {
       {0.3 , 0.25 , 0.25 , 0.2},
       {0.2 , 0.35 , 0.15 , 0.3},
       {0.4 , 0.15 , 0.2 , 0.25},
       {0.25 , 0.25 , 0.25 , 0.25},
       {0.2 , 0.4 , 0.3 , 0.1},
       {0.3 , 0.2 , 0.3 , 0.2},
       {0.15 , 0.3 , 0.2 , 0.35}
    };

    double initProbs2[7] = {0.0 , 0.0 , 0.0 , 1.0 , 0.0 , 0.0 , 0.0};

    for(i = 0; i < hmm2->hiddenStates; i++){
        hmm2->initProbs[i] = initProbs2[i];
    }
    for(i = 0; i < hmm2->hiddenStates; i++){
       for(j = 0; j < hmm2->hiddenStates; j++){
           hmm2->transitionProbs[i*hmm2->hiddenStates+j] = transitionProbs2[i][j];
       }
    }
    for(i = 0; i < hmm2->hiddenStates; i++){
       for(j = 0; j < hmm2->observations; j++){
           hmm2->emissionProbs[i*hmm2->observations+j] = emissionProbs2[i][j];
       }
    }

    const unsigned int observation2[10] = {0,1,2,3,3,2,1,3,2,1};
    const unsigned int obsLenght2 = 10;
    
    double * scaleFactor2 = calloc(obsLenght2, sizeof(double));
    double * alpha2 = calloc(obsLenght2*hmm2->hiddenStates, sizeof(double));
    F(hmm2, observation2, obsLenght2, scaleFactor2, alpha2);
    
    double test2alpha[70] = {0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 0.0297029702970297, 0.8910891089108911, 0.07920792079207922, 0.0, 0.0,
         0.0, 0.017751479289940822, 0.03550295857988165, 0.7988165680473371, 0.05325443786982248, 0.09467455621301775, 0.0,
         0.014105201292976783, 0.04231560387893035, 0.03967087863649721, 0.7140758154569498, 0.015868351454598886, 0.04231560387893036, 0.13164854540111665,
         0.0367677567200097, 0.05170465788751365, 0.05256640218563887, 0.7138434434025496, 0.06698625677426767, 0.013787908770003642, 0.06434357426001698,
         0.05198659387687777, 0.03171182226489543, 0.055326572081016934, 0.6561285776082829, 0.112934136194607, 0.08082182461391929, 0.011090473360400593,
         0.03141205283200857, 0.07672500391140769, 0.04730517836050952, 0.5911817003208785, 0.06781341533059485, 0.08949326274723163, 0.09606938649736914,
         0.06483316415628948, 0.05995980914443716, 0.06108337113044319, 0.575462087135659, 0.049019502784910594, 0.05730280956653559, 0.13233925608172487,
         0.06080739819354018, 0.03716810567944167, 0.07068361444879583, 0.5452330770139235, 0.17996260493700922, 0.059654928211884464, 0.046490271515404996,
         0.03669552875343646, 0.09769886257539809, 0.048567519065541305, 0.49506394220074496, 0.10915885400232408, 0.1421395645172638, 0.07067572888529124};

    
    for (j = 0; j < obsLenght2; j++){
        for(i = 0; i < hmm2->hiddenStates; i++) {
            assert(fabs(alpha2[j*hmm2->hiddenStates+i]-test2alpha[j*hmm2->hiddenStates+i]) < 0.00001);
        }
    }
    
    free(alpha2);
    free(scaleFactor2);
    assert(valdidateHMM(hmm2) == true);
    HMMDeallocate(hmm2);
    
    
    
    return true;
}
