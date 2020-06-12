#include "utils.h"
using namespace std;

#define ONE_OVER_SQRT2PI 0.3989422804

/* Define the gaussian kernel (mu=1, sigma=1)*/
float gaussianKernel(vector<float> x) {
    /* Compute the value of the mulitvariate Gaussian with mean[0] and Sigma[1] */
    float result = 1.0;
    for(int i = 0; i < x.size(); i++) {
        float exponential = exp((-0.5)*x[i]*x[i]);
        float normFactor = ONE_OVER_SQRT2PI;
        result *= (exponential * normFactor);
    }
    return result;
}

/* Define the basic kernel */
float basicKernel(vector<float> x) {
    for(auto el : x) {
        if(el < 0) el *= -1;
        if(el > 0.5) return 0;
    }
    return 1;
}

/* Subtraction between vectors */
vector<float> vectorSubtraction(vector<float> x1, vector<float> x2) {
    // Check the dimensions
    if(x1.size() != x2.size()) return vector<float>();
    // Compute the subtraction
    int size = x1.size();
    vector<float> result;
    for(int i = 0; i < size; i++) {
        result.push_back(x1[i] - x2[i]);
    }
    return result;
}

/* Vector division by a scalar */
vector<float> vectorDivisionByScalar(vector<float> x, float scalar) {
    vector<float> result;
    for(auto el : x) {
        result.push_back(float(el) / scalar);
    }
    return result;
}

/* Generate the x data */
vector<vector<float>> generateX(float range, int size, float step) {
    vector<vector<float>> result;
    if(size == 1) {
        for(float i = -range; i < range; i+=step) {
            result.push_back(vector<float>{i});
        }
    } else {
        for(float i = -range; i < range; i+=step) {
            for(float j = -range; j < range; j+=step) {
                result.push_back(vector<float>{i, j});
            }
        }
    }
    return result;
}

/* Get the data from file */
vector<vector<float>>  getData(string fileName) {
    vector<vector<float>> result;
    ifstream fileStream(fileName);
    string line = "";
    while(getline(fileStream, line)) {
        stringstream lineStream(line);
        float x = 0.0;
        vector<float> row;
        while(lineStream >> x) {
            row.push_back(x);
        }
        result.push_back(row);
    }
    fileStream.close();
    return result;
}

/* Save data on file */
void saveData(map<vector<float>, float> values, string fileName) {
    ofstream fileStream(fileName);
    for(auto xy : values) {
        for(auto xVal : xy.first) {
            fileStream << xVal << " ";
        }
        fileStream << xy.second << endl;
    }
    fileStream.close();
}
