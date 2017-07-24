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
int stringSequenceTest();
int printParameters(Point testingPoint);
int printStatus(Point testingPoint);

vector<long> getInputSequence();
int printSequence(vector<long> sequence);
vector<string> split(const string &s, const string &seperator);


int main(int argc, char * argv[]){
  int result = 0;
  
  cout << "dynamic network test" << endl;

  
  //dictionaryTest();

  //pointTest();
  //multiplePointTest();
  stringSequenceTest();

  //randomTest2();

  //size_t resultNumber;
  //getInputSequence(resultNumber);

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


int stringSequenceTest(){
  int result = 0;

  vector<long> inputSequence = getInputSequence();
  
  for(size_t i=0; i<inputSequence.size(); i++){
    cout << " " << inputSequence[i];
  }
  cout << endl;

  double currentStatus[Point::statusNumber];
  double predictStatus[Point::statusNumber];

  for(size_t i=0; i<Point::statusNumber; i++){
    currentStatus[i] = math::RandomFactory::getNext();
    predictStatus[i] = currentStatus[i];
  }

  
  map<long, Point*> allPoints;
  Point* p_prevPoint = NULL;

  for(size_t i=0; i<inputSequence.size(); i++){
    map<long, Point*>::iterator it = allPoints.find(inputSequence[i]);
    Point* p_currentPoint;
    
    if(it == allPoints.end()){
      p_currentPoint = new Point(inputSequence[i]);
      allPoints.insert(map<long, Point*>::value_type(inputSequence[i], p_currentPoint));
    }
  }

  for(size_t i=0; i<inputSequence.size()-1; i++){
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

    vector<double> newStatus = p_currentPoint->getOutputStatus();

    for(size_t j=0; j<Point::statusNumber; j++){
      currentStatus[j] = newStatus[j];
    }

    if(p_prevPoint != NULL){
      vector<double> inputStatusGradient = p_currentPoint->getInputStatusGradient();
      cout << "getting input status gradient:";
      for(int k=0; k<Point::statusNumber; k++){
        cout << " " << inputStatusGradient[k];
      }
      cout << endl;
      double tempGradient[Point::statusNumber];
      for(size_t k=0; k<Point::statusNumber; k++){
        tempGradient[i] = inputStatusGradient[i];
      }
      p_prevPoint->updateOutputParametersWithBP(tempGradient);
    }

    p_prevPoint = p_currentPoint;

  }

  
  int predictTime = 100;

  Dictionary* dictionary = Dictionary::getInstance();
  long predictID = dictionary->getID("I");
  //predictID = 10;

  vector<long> predictSequence;
  
  map<long, Point*>::iterator it = allPoints.find(predictID);
  Point* currentPoint = it->second;

  cout << "Current Point ID:" << currentPoint->getID() << endl;

  cout << "Predicting the sequence with the init ID: " << predictID << endl;

  for(size_t i=0; i<predictTime; i++){
    //cout << "p:" << i << " ";
    long predictResult = currentPoint->predictNextPoint(predictStatus);
    //cout << "  " << predictResult;
    predictSequence.push_back(vector<long>::value_type( predictResult));

    vector<double> newStatus = currentPoint->getOutputStatus();
    predictID = predictResult;
    it = allPoints.find(predictID);
    if(it == allPoints.end()){
      cout << "Not in it!!!!!!!!!!!!!!!!";
      cout << " " << predictID;
    }else{
      currentPoint = it->second;
    }
     

    for(int j=0; j<Point::statusNumber; j++){
        predictStatus[j] = newStatus[j];
     }
    
  }

  cout << endl << "  end of prediction" << endl;

  printSequence(predictSequence);


  return result;
}



int multiplePointTest(){
  int result = 0;

  long inputSequence[] = {10, 20, 30, 30, 10, 40, 30, 20, 10, 30, 10, 20, 10, 20, 10, 20};
  size_t inputNumber = sizeof(inputSequence)/sizeof(inputSequence[0]);

  for(size_t i=0; i<inputNumber; i++){
    cout << " " << inputSequence[i];
  }
  cout << endl;

  double currentStatus[Point::statusNumber];
  
  for(size_t i=0; i<Point::statusNumber; i++){
    currentStatus[i] = math::RandomFactory::getNext();
  }

  
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

    vector<double> newStatus = p_currentPoint->getOutputStatus();

    for(size_t j=0; j<Point::statusNumber; j++){
      currentStatus[j] = newStatus[j];
    }

    if(p_prevPoint != NULL){
      vector<double> inputStatusGradient = p_currentPoint->getInputStatusGradient();
      cout << "getting input status gradient:";
      for(int k=0; k<Point::statusNumber; k++){
        cout << " " << inputStatusGradient[k];
      }
      cout << endl;
      double tempGradient[Point::statusNumber];
      for(size_t k=0; k<Point::statusNumber; k++){
        tempGradient[k] = inputStatusGradient[k];
      }
      p_prevPoint->updateOutputParametersWithBP(tempGradient);
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

    vector<double> newStatus = currentPoint->getOutputStatus();
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

  vector<double> outputStatus = testingPoint.getOutputStatus();

  cout << "output status: ";
    for(int i=0; i<testingPoint.statusNumber; i++){
      cout << outputStatus[i] << ", ";
    }
  cout << endl;

  return result;
}

vector<long> getInputSequence(){
  string inputString = "Something that make me can be used to train the sentence, hope that it works!";
  inputString = inputString + "I am a boy, hope that it is a new sample.";
  inputString = inputString + "Some new words, new sample set has more training sample.";
  inputString = inputString + "I have an idea, hope that it can provide more training sample.";
  inputString = inputString + "I have a pen, hope that it can provide more training sample.";
  inputString = inputString + "I can go to school, hope that it can provide more training sample.";
  inputString = inputString + "Some new words, hope that it can provide more training sample.";


  vector<string> splitResult = split(inputString, " ");

  vector<long> result;
  
  Dictionary* dictionary = Dictionary::getInstance();

  for(size_t i=0; i<splitResult.size(); i++){
    result.push_back(vector<long>::value_type(dictionary->addValue(splitResult[i])));
  }

  return result;
}


int printSequence(vector<long> sequence){
  Dictionary* dictionary = Dictionary::getInstance();

  cout << "printing sequence: " << endl;
  for(size_t i=0; i<sequence.size(); i++){
    string value = dictionary->getValue(sequence[i]);
    cout << " " << value;
  }
  cout << endl;
  return 0;
}




vector<string> split(const string &s, const string &seperator){
  vector<string> result;
  typedef string::size_type string_size;
  string_size i = 0;

  while(i != s.size()){
    //
    int flag = 0;
    while(i != s.size() && flag == 0){
      flag = 1;
      for(string_size x = 0; x < seperator.size(); ++x)
        if(s[i] == seperator[x]){
        ++i;
        flag = 0;
        break;
        }
    }
    
    //
    flag = 0;
    string_size j = i;
    while(j != s.size() && flag == 0){
      for(string_size x = 0; x < seperator.size(); ++x)
        if(s[j] == seperator[x]){
          flag = 1;
          break;
        }
      if(flag == 0) 
        ++j;
    }
    if(i != j){
      result.push_back(s.substr(i, j-i));
      i = j;
    }
  }
  return result;
}



