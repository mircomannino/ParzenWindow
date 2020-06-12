#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <math.h>
using namespace std;

/* Kernel */
float gaussianKernel(vector<float> x);
float basicKernel(vector<float> x);

/* Manage vector */
vector<float> vectorSubtraction(vector<float> x1, vector<float> x2);
vector<float> vectorDivisionByScalar(vector<float> x, float scalar);
vector<vector<float>> generateX(float range, int size, float step);

/* Data */
vector<vector<float>> getData(string fileName);
void saveData(map<vector<float>, float> values, string fileName);




#endif
