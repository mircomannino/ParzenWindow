#ifndef __PDF_ESTIMATOR_PW__
#define __PDF_ESTIMATOR_PW__

#include <vector>
#include <math.h>
#include "utils.h"
using namespace std;

class pdfEstimatorPW {
private:
    float H1 = 0.0;
public:
    pdfEstimatorPW(float H1_) : H1(H1_) {}
    float estimate(vector<float> x0, vector<vector<float>> trainingSet);
};

#endif
