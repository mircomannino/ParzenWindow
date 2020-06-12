# ParzenWindow
Implementation of "Parzen Window" non-parametric esimation for pdf.

## Compile and run the test (Parzen Window test)

```
g++ test_ParzenWindow.cc pdfEstimatorPW.cc utils.cc -o test_ParzenWindow

```
For this test I used a gaussian distribution in 1D and 2D. The following lines explain how to run the tests.
```
# Test 1D
./parzenWindow data1D/gaussian_training_set.txt 1.5 gaussian1D

# Test 2D
./parzenWindow data2D/gaussian_training_set.txt 1.5 gaussian2D
```
Where in each of the line above there are 3 input parameters:
* path to the input data.
* Value of H1 (the initial edge of the window).
* Name of the output file, containing the estimation of the pdf.

## IRIS Classifier test
I used the parzen window estimation to exploit the Bayes theorem in order to get a classification of the well known iris dataset.
There is a validation test in order to find out the best H1 to give in input to the parzen window estimator.
For the complilation execute this command:
```
g++ IRIS_Classifier.cc pdfEstimatorPW.cc utils.cc -o IRIS_Classifier
```
For run the test, execute this command:
```
./IRIS_Classifier
```
