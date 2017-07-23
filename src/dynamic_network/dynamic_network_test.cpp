#include <iostream>
#include <assert.h>
#include <vector>
#include <map>
#include <time.h>

#include"stdlib.h"

#include "dictionary.h"
#include "point.h"

using namespace std;
using namespace katen;

int dictionaryTest();
int pointTest();
int randomTest();
int multiplePointTest();
int printParameters(Point testingPoint);
int printStatus(Point testingPoint);


int main(int argc, char * argv[]){
  int result = 0;
  
  cout << "dynamic network test" << endl;

  
  dictionaryTest();

  //pointTest();
   multiplePointTest();

  //randomTest();

  return result;
}

int dictionaryTest(){
  int result = 0;

  Dictionary* testingInstance1 = Dictionary::getInstance();

  cout << "the address of the instance1 is: " << testingInstance1 << endl;

  Dictionary* testingInstance2 = Dictionary::getInstance();

  cout << "the address of the instance2 is: " << testingInstance2 << endl;

  
  assert(testingInstance1 == testingInstance2);

  string testingValues[10] = {"abd", "efs", "中文", "aaa", "www", "werwer", "ss", "tt", "ss", "ee"};

  for(int i=0; i<10; i++){
  
    long id = testingInstance2->addValue(testingValues[i]);

    cout << "the id of " << testingValues[i] << " is: " << id << endl;
  }
  return result;


}

int pointTest(){
  int result = 0;

  Point testingPoint = Point();

  double inputStatus[] = {1.0, 1.0, 1.0};
  double testingStatus[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

  int arraySize = sizeof(inputStatus)/sizeof(inputStatus[0]);

  
  
  testingPoint.connectTo(10, testingStatus);
  testingPoint.connectTo(20, testingStatus);
  testingPoint.connectTo(10, testingStatus);
  testingPoint.connectTo(30, testingStatus);
  testingPoint.connectTo(30, testingStatus);
  testingPoint.connectTo(30, testingStatus);
  

  vector< double* > parameters = testingPoint.getInputParameters();

  cout << "the size of the parameters: " << parameters.size() << endl;
  
  printParameters(testingPoint);

  printStatus(testingPoint);

  return result;

}

int multiplePointTest(){
  int result = 0;

  long inputSequence[] = {10, 20, 30, 10, 20, 30, 10, 20, 30};

  double currentStatus[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
  

  size_t inputNumber = sizeof(inputSequence)/sizeof(inputSequence[0]);

  map<long, Point*> allPoints;
  Point* p_prevPoint = NULL;

  for(size_t i=0; i<inputNumber-1; i++){
    map<long, Point*>::iterator it = allPoints.find(inputSequence[i]);
    Point* p_currentPoint;
    
    if(it == allPoints.end()){
      p_currentPoint = new Point();
      allPoints.insert(map<long, Point*>::value_type(inputSequence[i], p_currentPoint));
    }else{
      p_currentPoint = allPoints[inputSequence[i]];  
    }

    p_currentPoint->connectTo(inputSequence[i+1], currentStatus);

    printStatus((*p_currentPoint));

    double* newStatus = p_currentPoint->getOutputStatus();

    for(size_t i=0; i<Point::statusNumber; i++){
      currentStatus[i] = newStatus[i];
    }

    if(p_prevPoint != NULL){
      p_prevPoint->updateOutputParametersWithBP(p_currentPoint->getInputStatusGradient());
    }

    p_prevPoint = p_currentPoint;

  }


  return result;
}

int randomTest(){
  int result = 0;

    for(int i=0; i<1000; i++){
      double x;
      double x1;
      double x2;
      srand((unsigned)time(0)); //srand(3)
      x1 = rand();
      
      x2 = rand();
      x = x1/x2;
      cout<<x<<endl;
    }
  return result;  
}

int printParameters(Point testingPoint){
  int result = 0;

  cout << "print input parameters: " << endl;
  vector< double* > inputParameters = testingPoint.getInputParameters();

  for(int i=0; i<inputParameters.size(); i++){
    for(int j=0; j<testingPoint.statusNumber; j++){
      cout << inputParameters[i][j] << ", ";
    }
    cout << endl;
  }

  cout << "print output parameters: " << endl;
 vector< double* > outputParameters = testingPoint.getOutputParameters();

  for(int i=0; i<outputParameters.size(); i++){
    for(int j=0; j<testingPoint.statusNumber; j++){
      cout << outputParameters[i][j] << ", ";
    }
    cout << endl;
  }

  return result;
}

int printStatus(Point testingPoint){
  int result = 0;

  double* outputStatus = testingPoint.getOutputStatus();

  cout << "output status: ";
    for(int i=0; i<testingPoint.statusNumber; i++){
      cout << outputStatus[i] << ", ";
    }
  cout << endl;

  return result;
}