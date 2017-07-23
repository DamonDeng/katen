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
      int position = positionInNextTargets(nextTarget);

      vector<double>::size_type j;

      for(j=0; j<inputParameters.size(); j++){
        inputParameters[j][position] = inputParameters[j][position] + generateInitParameter();
      }

    }else{
      //nextTarget is not in the nextTargets list, should update the nextTargets list
      //and append value to each set of parameters.
      cout << "is not in the next target list" << endl;
      this->nextTargets.push_back(nextTarget);

      vector<double>::size_type j;

      for(j=0; j<inputParameters.size(); j++){
        this->inputParameters[j].push_back(generateInitParameter());
      }
    }

    return result;
  }

//connect to a target with the status.
  //if the target is in the nextTargets list, the inputParameters should be updated with BP.
  //if the target is not in the nextTargets list, the nextTargets list should be update.
  //and the new value of inputParameters should be appended at the end of each set of parameters.

  //the structure of the inputParameters is a two dimentions vector with double value.
  // {{status1:{target1, target2, target3 ...}, {status2:{target1, target2, }}}
  int Target::connectToNewTarget(long nextTarget, vector<double> status){
    int result = 0;

    this->nextTargets.push_back(nextTarget);
    double* targetParameters = new double[this->statusNumber];
    
    for(size_t i=0; i<this->statusNumber; i++){
      double[i] = this->generateInitParameter();
    }

    this->inputParameters.push_back(vector< double* >::value_type(targetParameters));

    if(isInNextTargets(nextTarget)){
      //nextTarget is in the nextTargets list, should update the parameter with BP.
      cout << "is in the next target list" << endl;
      int position = positionInNextTargets(nextTarget);

      vector<double>::size_type j;

      for(j=0; j<inputParameters.size(); j++){
        inputParameters[j][position] = inputParameters[j][position] + generateInitParameter();
      }

    }else{
      //nextTarget is not in the nextTargets list, should update the nextTargets list
      //and append value to each set of parameters.
      cout << "is not in the next target list" << endl;
      this->nextTargets.push_back(nextTarget);

      vector<double>::size_type j;

      for(j=0; j<inputParameters.size(); j++){
        this->inputParameters[j].push_back(generateInitParameter());
      }
    }

    return result;
  }


  vector< vector<double> > Target::getInputParameters(){
    return this->inputParameters;
  }

  vector< vector<double> > Target::getOutputParameters(){
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