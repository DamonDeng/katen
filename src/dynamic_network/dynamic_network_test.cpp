#include <iostream>
#include <assert.h>
#include <vector>
#include <time.h>

#include"stdlib.h"

#include "dictionary.h"
#include "target.h"

using namespace std;
using namespace katen;

int dictionaryTest();
int targetTest();
int randomTest();
int printParameters(Target testingTarget);

int main(int argc, char * argv[]){
  int result = 0;
  
  cout << "dynamic network test" << endl;

  
  dictionaryTest();

  targetTest();

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

int targetTest(){
  int result = 0;

  Target testingTarget = Target();

  double inputStatus[] = {1.0, 1.0, 1.0};
  vector<double> testingStatus;

  int arraySize = sizeof(inputStatus)/sizeof(inputStatus[0]);

  for(int i=0; i<arraySize; i++){
    testingStatus.push_back(inputStatus[i]);
  }

  
  testingTarget.connectTo(10, testingStatus);
  testingTarget.connectTo(20, testingStatus);
  testingTarget.connectTo(10, testingStatus);
  testingTarget.connectTo(30, testingStatus);
  testingTarget.connectTo(30, testingStatus);
  testingTarget.connectTo(30, testingStatus);
  

  vector< double* > parameters = testingTarget.getInputParameters();

  cout << "the size of the parameters: " << parameters.size() << endl;
  
  printParameters(testingTarget);

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

int printParameters(Target testingTarget){
  int result = 0;

  vector< double* > inputParameters = testingTarget.getInputParameters();

  for(int i=0; i<inputParameters.size(); i++){
    for(int j=0; j<testingTarget.statusNumber; j++){
      cout << inputParameters[i][j] << ", ";
    }
    cout << endl;
  }

  return result;
}