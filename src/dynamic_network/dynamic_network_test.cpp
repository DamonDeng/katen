#include <iostream>
#include <assert.h>
#include <vector>
#include <time.h>

#include"stdlib.h"

#include "dictionary.h"
#include "point.h"

using namespace std;
using namespace katen;

int dictionaryTest();
int pointTest();
int randomTest();
int printParameters(Point testingPoint);

int main(int argc, char * argv[]){
  int result = 0;
  
  cout << "dynamic network test" << endl;

  
  dictionaryTest();

  pointTest();

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
  vector<double> testingStatus;

  int arraySize = sizeof(inputStatus)/sizeof(inputStatus[0]);

  for(int i=0; i<arraySize; i++){
    testingStatus.push_back(inputStatus[i]);
  }

  
  testingPoint.connectTo(10, testingStatus);
  testingPoint.connectTo(20, testingStatus);
  testingPoint.connectTo(10, testingStatus);
  testingPoint.connectTo(30, testingStatus);
  testingPoint.connectTo(30, testingStatus);
  testingPoint.connectTo(30, testingStatus);
  

  vector< double* > parameters = testingPoint.getInputParameters();

  cout << "the size of the parameters: " << parameters.size() << endl;
  
  printParameters(testingPoint);

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

  vector< double* > inputParameters = testingPoint.getInputParameters();

  for(int i=0; i<inputParameters.size(); i++){
    for(int j=0; j<testingPoint.statusNumber; j++){
      cout << inputParameters[i][j] << ", ";
    }
    cout << endl;
  }

  return result;
}