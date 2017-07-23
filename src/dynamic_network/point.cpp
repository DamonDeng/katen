#include <iostream>

#include "point.h"

using namespace std;

namespace katen{

  Point::Point(){

  } 

  Point::~Point(){
    //Todo, remember to delete all the parameters.
  }

  //connect to a point with the status.
  //if the point is in the nextPoints list, the inputParameters should be updated with BP.
  //if the point is not in the nextPoints list, the nextPoints list should be update.
  
  //the structure of the inputParameters is a vector of double array.
  // {point1:{status1, status2, ...}, point2:{status1, status2}}
  int Point::connectTo(long nextPoint, vector<double> status){
    int result = 0;

    if(isInNextPoints(nextPoint)){
      //nextPoint is in the nextPoints list, should update the parameter with BP.
      cout << "is in the next point list" << endl;
      

      this->updateOldPoint(nextPoint, status);

    }else{
      //nextPoint is not in the nextPoints list, should update the nextPoints list
      //and append value to each set of parameters.
      cout << "is not in the next point list" << endl;
      
      this->connectToNewPoint(nextPoint, status);

    }

    return result;
  }

  //connect to a newpoint with the status.
  //and the new value of inputParameter should be appended at the end of inputParameters.

  //the structure of the inputParameters is a vector of double array.
  // {point1:{status1, status2, ...}, point2:{status1, status2}}
  int Point::connectToNewPoint(long nextPoint, vector<double> status){
    int result = 0;

    this->nextPoints.push_back(nextPoint);
    double* pointParameters = new double[this->statusNumber];
    
    for(size_t i=0; i<this->statusNumber; i++){
      pointParameters[i] = this->generateInitParameter();
    }

    this->inputParameters.push_back(vector< double* >::value_type(pointParameters));

    return result;
  }

  //update oldarget with the status.
  //the value of all the inputParameters should be updated based on softmax and cross entropy.

  //the structure of the inputParameters is a vector of double array.
  // {point1:{status1, status2, ...}, point2:{status1, status2}}
  int Point::updateOldPoint(long nextPoint, vector<double> status){
    int result = 0;

    int position = positionInNextPoints(nextPoint);

    cout << "should update the parameters with the result of position: " << position << endl;

    return result;
  }

  vector< double* > Point::getInputParameters(){
    return this->inputParameters;
  }

  vector< double* > Point::getOutputParameters(){
    return this->outputParameters;
  }


  int Point::addNextPoint(long nextPoint){
    int result = 0;

    this->nextPoints.push_back(nextPoint);

    return result;
  }

  int Point::positionInNextPoints(long nextPoint){
    int resultPosition = -1;
    for(int i=0; i<this->nextPoints.size(); i++){
      if(this->nextPoints[i] == nextPoint){
        resultPosition = i;
      }
    }
    return resultPosition;
  }

  bool Point::isInNextPoints(long nextPoint){
    bool result = false;
    int position = positionInNextPoints(nextPoint);

    if(position != -1){
      result = true;
    }

    return result;

  }

  double Point::generateInitParameter(){
    return 0.01;
  }

}