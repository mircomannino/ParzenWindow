CC=g++

all: test_ParzenWindow test_IRIS_Classifier

test_ParzenWindow: test_ParzenWindow.o pdfEstimatorPW.o utils.o
	${CC} -o test_ParzenWindow test_ParzenWindow.o pdfEstimatorPW.o utils.o

test_IRIS_Classifier: test_IRIS_Classifier.o pdfEstimatorPW.o utils.o
	${CC} -o test_IRIS_Classifier test_IRIS_Classifier.o pdfEstimatorPW.o utils.o

utils.o: utils.cc utils.h
	${CC} -c utils.cc

pdfEstimatorPW.o: pdfEstimatorPW.cc pdfEstimatorPW.h
	${CC} -c pdfEstimatorPW.cc

clean:
	rm -rf *.o test_ParzenWindow test_IRIS_Classifier
