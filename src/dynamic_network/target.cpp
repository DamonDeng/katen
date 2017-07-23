#include <iostream>

#include "target.h"

using namespace std;

namespace katen{

  Target::Target(){

  } 

  Target::~Target(){
    //Todo, remember to delete all the parameters.
  }

  //connect to a target with the status.
  //if the target is in the nextTargets list, the inputParameters should be updated with BP.
  //if the target is not in the nextTargets list, the nextTargets list should be update.
  //and the new value of inputParameters should be appended at the end of each set of parameters.

  //the structure of the inputParameters is a two dimentions vector with double value.
  // {{status1:{target1, target2, target3 ...}, {status2:{target1, target2, }}}
  int Target::connectTo(long nextTarget, vector<double> status){
    int result = 0;

    if(isInNextTargets(nextTarget)){
      //nextTarget is in the nextTargets list, should update the parameter with BP.
      cout << "is in the next target list" << endl;
      

      this->updateOldTarget(nextTarget, status);

    }else{
      //nextTarget is not in the nextTargets list, should update the nextTargets list
      //and append value to each set of parameters.
      cout << "is not in the next target list" << endl;
      
      this->connectToNewTarget(nextTarget, status);

    }

    return result;
  }

  //connect to a newtarget with the status.
  //and the new value of inputParameter should be appended at the end of inputParameters.

  //the structure of the inputParameters is a vector of double array.
  // {target1:{status1, status2, ...}, target2:{status1, status2}}
  int Target::connectToNewTarget(long nextTarget, vector<double> status){
    int result = 0;

    this->nextTargets.push_back(nextTarget);
    double* targetParameters = new double[this->statusNumber];
    
    for(size_t i=0; i<this->statusNumber; i++){
      targetParameters[i] = this->generateInitParameter();
    }

    this->inputParameters.push_back(vector< double* >::value_type(targetParameters));

    return result;
  }

  //update oldarget with the status.
  //the value of all the inputParameters should be updated based on softmax and cross entropy.

  //the structure of the inputParameters is a vector of double array.
  // {target1:{status1, status2, ...}, target2:{status1, status2}}
  int Target::updateOldTarget(long nextTarget, vector<double> status){
    int result = 0;

    int position = positionInNextTargets(nextTarget);

    cout << "should update the parameters with the result of position: " << position << endl;

    return result;
  }

  vector< double* > Target::getInputParameters(){
    return this->inputParameters;
  }

  vector< double* > Target::getOutputParameters(){
    return this->outputParameters;
  }


  int Target::addNextTarget(long nextTarget){
    int result = 0;

    this->nextTargets.push_back(nextTarget);

    return result;
  }

  int Target::positionInNextTargets(long nextTarget){
    int resultPosition = -1;
    for(int i=0; i<this->nextTargets.size(); i++){
      if(this->nextTargets[i] == nextTarget){
        resultPosition = i;
      }
    }
    return resultPosition;
  }

  bool Target::isInNextTargets(long nextTarget){
    bool result = false;
    int position = positionInNextTargets(nextTarget);

    if(position != -1){
      result = true;
    }

    return result;

  }

  double Target::generateInitParameter(){
    return 0.01;
  }

}