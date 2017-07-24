#include <iostream>
#include <assert.h>
#include <vector>
#include <map>
#include <time.h>
#include <random>

#include"stdlib.h"

#include "dictionary.h"
#include "point.h"

#include "dmath/util.h"
#include "dmath/random_factory.h"

using namespace std;
using namespace katen;

int dictionaryTest();
int pointTest();
int randomTest();
int randomTest2();
int multiplePointTest();
int printParameters(Point testingPoint);
int printStatus(Point testingPoint);


int main(int argc, char * argv[]){
  int result = 0;
  
  cout << "dynamic network test" << endl;

  
  //dictionaryTest();

  //pointTest();
  multiplePointTest();

  //randomTest2();

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

  Point testingPoint = Point(10);

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

  long inputSequence[] = {10, 20, 30, 30, 10, 40, 30, 20, 10, 30, 10, 20, 10, 20, 10, 20};


  double currentStatus[Point::statusNumber];
  
  for(size_t i=0; i<Point::statusNumber; i++){
    currentStatus[i] = math::RandomFactory::getNext();
  }

  size_t inputNumber = sizeof(inputSequence)/sizeof(inputSequence[0]);

  map<long, Point*> allPoints;
  Point* p_prevPoint = NULL;

  for(size_t i=0; i<inputNumber-1; i++){
    map<long, Point*>::iterator it = allPoints.find(inputSequence[i]);
    Point* p_currentPoint;
    
    if(it == allPoints.end()){
      p_currentPoint = new Point(inputSequence[i]);
      allPoints.insert(map<long, Point*>::value_type(inputSequence[i], p_currentPoint));
    }else{
      p_currentPoint = allPoints[inputSequence[i]];  
    }

    p_currentPoint->connectTo(inputSequence[i+1], currentStatus);

    printParameters((*p_currentPoint));
    printStatus((*p_currentPoint));

    double* newStatus = p_currentPoint->getOutputStatus();

    for(size_t i=0; i<Point::statusNumber; i++){
      currentStatus[i] = newStatus[i];
    }

    if(p_prevPoint != NULL){
      double* inputStatusGradient = p_currentPoint->getInputStatusGradient();
      cout << "getting input status gradient:";
      for(int k=0; k<Point::statusNumber; k++){
        cout << " " << inputStatusGradient[k];
      }
      cout << endl;
      p_prevPoint->updateOutputParametersWithBP(inputStatusGradient);
    }

    p_prevPoint = p_currentPoint;

  }

  double predictStatus[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

  int predictTime = 20;

  long predictID = 10;

  map<long, Point*>::iterator it = allPoints.find(predictID);
  Point* currentPoint = it->second;

  cout << "Predicting the sequence with the init ID: " << predictID << endl;

  for(int i=0; i<predictTime; i++){
    
    long predictResult = currentPoint->predictNextPoint(predictStatus);
    cout << "  " << predictResult;

    double* newStatus = currentPoint->getOutputStatus();
    predictID = predictResult;
    it = allPoints.find(predictID);
    currentPoint = it->second;

    for(int j=0; j<Point::statusNumber; j++){
      predictStatus[j] = newStatus[j];
    }
    
  }

  cout << endl << "  end of prediction" << endl;

  


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

int randomTest2(){
  std::default_random_engine random(time(NULL));  
    std::uniform_int_distribution<int> dis1(0, 100);  
   std::uniform_real_distribution<double> dis2(-1.0, 1.0);  
   
    for(int i = 0; i < 10; ++i)  
        cout<<dis1(random)<<' ';  
    cout<<endl;  
   
    for(int i = 0; i < 10; ++i)  
        cout<<dis2(random)<<' ';  
    cout<<endl;  
   
    return 0;  
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