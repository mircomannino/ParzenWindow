#include <iostream>
#include <vector>
#include <map>
#include "pdfEstimatorPW.h"
#include "utils.h"
using namespace std;

class Classifier {
private:
    map<string, vector<vector<float>>> trainingSets;
public:
    /* Constructor */
    Classifier(vector<vector<string>> trainingSetsFile) {
        for(auto trainingSet : trainingSetsFile) {
            string name = trainingSet[0];
            string path = trainingSet[1];
            trainingSets[name] = getData(path);
        }
    }

    /* Make a rediction */
    string getPrediction(vector<float> x, float edgeSize) {
        float max = 0.0;
        string maxClass = "";
        /* Predict the pdf for each class and get the one with higher probab. */
        for(auto trainingSet : trainingSets) {
            pdfEstimatorPW pdfEstimator(edgeSize);
            float discriminant = pdfEstimator.estimate(x, trainingSet.second);
            // cout << trainingSet.first << ": " << discriminant << endl;
            if(discriminant > max) {
                max = discriminant;
                maxClass = trainingSet.first;
            }
        }
        return maxClass;
    }

    /* Make the validation to determine the value of H1 */
    float makeValidation(vector<vector<float>> validationSet, string correctAnswer) {
        int totalSamples = validationSet.size();
        float correctPercentage = 0.0;
        float H1 = 0.0;
        for( ; correctPercentage < 99.0; H1+=0.1) {
            int nCorrect = this->makeTest(validationSet, H1, correctAnswer);
            correctPercentage = (float(nCorrect) / float(totalSamples)) * 100;
        }
        return H1;
    }

    /* Make a test with a bunch of input */
    /* The test set is referring only to a single class */
    int makeTest(vector<vector<float>> testSet, float H1, string correctAnswer) {
        int nCorrect = 0;
        for(auto x0 : testSet) {
            string prediction = this->getPrediction(x0, H1);
            if(prediction == correctAnswer) {
                nCorrect++;
            }
        }
        return nCorrect;
    }

};

int main() {
    /* Define the path and name for the Classifier */
    vector<vector<string>> trainingSetsFile = {
        vector<string>{"SETOSA", "./dataIRIS/setosa.training"},
        vector<string>{"VERSICOLOR", "./dataIRIS/versicolor.training"},
        vector<string>{"VIRGINICA", "./dataIRIS/virginica.training"}
    };

    /* Create the Classifier */
    Classifier myClassifier(trainingSetsFile);

    /**************************** Validation **********************************/
    /* Used to find the best value of H1 for each class */
    // SETOSA
    vector<vector<float>> validationSet_setosa = getData("./dataIRIS/setosa.validation");
    float H1_setosa = myClassifier.makeValidation(validationSet_setosa, "SETOSA");
    // VERSICOLOR
    vector<vector<float>> validationSet_versicolor = getData("./dataIRIS/versicolor.validation");
    float H1_versicolor = myClassifier.makeValidation(validationSet_versicolor, "VERSICOLOR");
    // VIRGINICA
    vector<vector<float>> validationSet_virginica = getData("./dataIRIS/virginica.validation");
    float H1_virginica = myClassifier.makeValidation(validationSet_virginica, "VIRGINICA");


    /************************* Test SETOSA ************************************/
    vector<vector<float>> testSet_setosa = getData("./dataIRIS/setosa.test");
    int totalSetosa = testSet_setosa.size();
    int correctSetosa = myClassifier.makeTest(testSet_setosa, H1_setosa, "SETOSA");
    cout << "TEST SETOSA ";
    cout << "(H1 = " << H1_setosa << "):\t\t";
    cout << "Correct: " << correctSetosa << "/" << totalSetosa << endl;
    /**************************************************************************/

    /************************* Test VERSICOLOR ********************************/
    vector<vector<float>> testSet_versicolor = getData("./dataIRIS/versicolor.test");
    int totalVersicolor = testSet_versicolor.size();
    int correctVersicolor = myClassifier.makeTest(testSet_versicolor, H1_versicolor, "VERSICOLOR");
    cout << "TEST VERSICOLOR ";
    cout << "(H1 = " << H1_versicolor << "):\t";
    cout << "Correct: " << correctVersicolor << "/" << totalVersicolor << endl;
    /**************************************************************************/

    /************************** Test VIRGINICA ********************************/
    vector<vector<float>> testSet_virginica = getData("./dataIRIS/virginica.test");
    int totalVirginica = testSet_virginica.size();
    int correctVirginica = myClassifier.makeTest(testSet_virginica, H1_virginica, "VIRGINICA");
    cout << "TEST VIRGINICA ";
    cout << "(H1 = " << H1_virginica << "):\t";
    cout << "Correct: " << correctVirginica << "/" << totalVirginica << endl;
    /**************************************************************************/


    return 0;
}
