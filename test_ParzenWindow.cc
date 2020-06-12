#include <iostream>
#include <vector>
#include <math.h>
#include <map>
#include "utils.h"
#include "pdfEstimatorPW.h"
using namespace std;

int main(int argc, char* argv[]) {
    /* Get the parameter */
    if(argc < 4) {
        cout << "Help:\n";
        cout << "first parameter: path of the input (ex. ./Data1D/gaussian_training_set.txt)\n";
        cout << "second parameter: value of H1 (ex. 1.0)\n";
        cout << "third parameter: name of the output (ex. gaussian1D)\n";
        return 0;
    }
    string inputFilePath(argv[1]);
    float H1 = atof(argv[2]);
    string outputName(argv[3]);

    /* Read the real pdf to estimate */
    vector<vector<float>> trainingSet = getData(inputFilePath);
    int N = trainingSet.size();

    /* Set the x values 2D*/
    float range = 5.0;
    float step = 0.1;
    vector<vector<float>> myX = generateX(range, trainingSet[0].size(), step);

    /* estimate the pdf */
    pdfEstimatorPW myEstimator(H1);
    map<vector<float>, float> estimatedPdf;
    for(auto x0 : myX) {
        float p_x0 = myEstimator.estimate(x0, trainingSet);
        estimatedPdf[x0] = p_x0;
    }

    /* save the data in a file */
    string N_str = to_string(N);
    string H1_str = to_string(H1);
    string outputPath = "./" + outputName + "__N_" + N_str + "__H_" + H1_str + ".txt"; // Change data2D
    saveData(estimatedPdf, outputPath);

    return 0;
}
