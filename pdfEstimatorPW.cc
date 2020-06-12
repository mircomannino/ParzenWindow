#include "pdfEstimatorPW.h"
using namespace std;

/************************ Class pdfEstimatorPW ********************************/
/* estimatedPdf */
float pdfEstimatorPW::estimate(vector<float> x0, vector<vector<float>> trainingSet) {
    int N = trainingSet.size();
    float Hn = float(this->H1) / sqrt(N);
    // Estimating p(x0)
    float p_x0 = 0.0;
    for(auto xi : trainingSet) {
        vector<float> kernelArg = vectorDivisionByScalar(vectorSubtraction(x0, xi), Hn);
        float kernelRes = gaussianKernel(kernelArg);
        float Vn = pow(Hn, xi.size());
        p_x0 += kernelRes / Vn;
    }
    p_x0 /= N;
    return p_x0;
}
/******************************************************************************/
