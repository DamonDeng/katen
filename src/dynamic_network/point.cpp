#include <iostream>

#include "point.h"
#include "dmath/util.h"
#include "dmath/random_factory.h"

using namespace std;

namespace katen{

  Point::Point(long ID){
    this->ID = ID;
   
  } 

  Point::~Point(){
    //Todo, remember to delete all the parameters.
  }

  long Point::getID(){
    return this->ID;
  }

  //connect to a point with the status.
  //if the point is in the nextPoints list, the inputParameters should be updated with BP.
  //if the point is not in the nextPoints list, the nextPoints list should be update.
  
  //the structure of the inputParameters is a vector of double array.
  // {point1:{status1, status2, ...}, point2:{status1, status2}}
  int Point::connectTo(long nextPoint, double status[]){
    int result = 0;

    cout << "::::::Point " << this->ID << " Connecting to: " << nextPoint ;
    cout << "-------------------------------------------" << endl;

    for(size_t i=0; i<this->statusNumber; i++){
      this->inputStatus[i] = status[i];
    }

    if(isInNextPoints(nextPoint)){
      //nextPoint is in the nextPoints list, should update the parameter with BP.
      //cout << "is in the next point list" << endl;
      

      this->updateOldPoint(nextPoint, status);

    }else{
      //nextPoint is not in the nextPoints list, should update the nextPoints list
      //and append value to each set of parameters.
      //cout << "is not in the next point list" << endl;
      
      this->connectToNewPoint(nextPoint, status);
      this->updateOldPoint(nextPoint, status);

    }

    updateOutputStatus();

    return result;
  }

  //connect to a newpoint with the status.
  //and the new value of inputParameter should be appended at the end of inputParameters.

  //the structure of the inputParameters is a vector of double array.
  // {point1:{status1, status2, ...}, point2:{status1, status2}}
  int Point::connectToNewPoint(long nextPoint, double status[]){
    int result = 0;

    this->nextPoints.push_back(nextPoint);
    
    double* pointInputParameters = new double[this->statusNumber];
    double* pointOutputParameters = new double[this->statusNumber];
    
    for(size_t i=0; i<this->statusNumber; i++){
      pointInputParameters[i] = this->generateInitParameter();
      pointOutputParameters[i] = this->generateInitParameter();
    }

    this->inputParameters.push_back(vector< double* >::value_type(pointInputParameters));
    this->outputParameters.push_back(vector< double* >::value_type(pointOutputParameters));
    this->hiddenLayerValue.push_back(vector<double>::value_type(0));

    return result;
  }

  //update oldarget with the status.
  //the value of all the inputParameters should be updated based on softmax and cross entropy.

  //the structure of the inputParameters is a vector of double array.
  // {point1:{status1, status2, ...}, point2:{status1, status2}}
  int Point::updateOldPoint(long nextPoint, double status[]){
    int result = 0;

    int rightPosition = positionInNextPoints(nextPoint);

    cout << "should update the parameters with the result of position: " << rightPosition << endl;
    size_t nextPointNumber = this->nextPoints.size();

    double softmaxInput[nextPointNumber];
    double softmaxOutput[nextPointNumber];

    double gradient[nextPointNumber];
    
    //compute the value of all the next points:
    for(size_t i=0; i<nextPointNumber; i++){
      softmaxInput[i] = math::Util::dotProduct(status, this->statusNumber, this->inputParameters[i]);
      this->hiddenLayerValue[i] = softmaxInput[i];
    }
    
    math::Util::softmax(softmaxInput, nextPointNumber, softmaxOutput);

    cout << "softmax: " ;
    for(size_t i=0; i<nextPointNumber; i++){
      cout << "  " << softmaxOutput[i];
    }
    cout << endl;

    math::Util::softmaxCrossEntropyBP(softmaxOutput, nextPointNumber, gradient, rightPosition);

    cout << "gradient: " ;
    for(size_t i=0; i<nextPointNumber; i++){
      cout << "  " << gradient[i];
    }
    cout << endl;

    //clear old gradient of inputStatus:
    this->inputStatusGradient.clear();
    for(size_t i=0; i<this->statusNumber; i++){
      this->inputStatusGradient.push_back(vector<double>::value_type(0));
      
    }

    cout << "updating parameter: " << endl;

    for(size_t i=0; i<nextPointNumber; i++){
      for(size_t j=0; j<this->statusNumber; j++){
        //comput currentGradient for weight current connection from inputStatus to hidden layer:
        double currentGradient = gradient[i]*status[j];

        //update inputParameters for gradient decent:
        //cout << " " << this->inputParameters[i][j] << "(-" << currentGradient << ") "; 
        this->inputParameters[i][j] = this->inputParameters[i][j] - currentGradient;
        
        cout << " [" << this->inputStatusGradient[j] << " (+" << currentGradient << ")]  ";
        //accumulate gradient for all the inputStatus, for BP to prev point:
        this->inputStatusGradient[j] = this->inputStatusGradient[j] + currentGradient;

      }
      cout << endl;
    }

    cout << "after updating inpuStatusGradient: " << this->inputStatusGradient[0] << endl;

    for(int i=0; i<Point::statusNumber; i++){
      cout << " " << this->inputStatusGradient[i];
    }
    cout << endl;

    return result;
  }

  int Point::updateOutputStatus(){
    int result = 0;

    size_t nextPointNumber = this->nextPoints.size();

    double hiddenLayer[nextPointNumber];
    
    
    for(size_t i=0; i<nextPointNumber; i++){
      hiddenLayer[i] = math::Util::dotProduct(this->inputStatus, this->statusNumber, this->inputParameters[i]);
    }

    double tempParameters[nextPointNumber];

    for(size_t s=0; s<this->statusNumber; s++){

     for(size_t i=0; i<nextPointNumber; i++){
        tempParameters[i] = this->outputParameters[i][s];
        this->outputStatus[s] = math::Util::dotProduct(hiddenLayer, nextPointNumber, tempParameters);
      } 
    }

    return result;

  }

  int Point::updateOutputParametersWithBP(double* outputStatusGradient){
    int result = 0;

    size_t nextPointNumber = this->nextPoints.size();
    cout << "Updaeting output_parameters of: " << this->ID << endl;
    for(size_t i=0; i<this->statusNumber; i++){
      for(size_t j=0; j<nextPointNumber; j++){
        //cout << "h(" << this->hiddenLayerValue[j] << ")* g(" << outputStatusGradient[i] << ") ";
        double currentGradient = outputStatusGradient[i]*this->hiddenLayerValue[j];
        //cout << " " << this->outputParameters[j][i] << " (-" << currentGradient << ") ";
        this->outputParameters[j][i] = this->outputParameters[j][i] - currentGradient;
      }
    }
    cout << endl;
    
    return result;

  }

  long Point::predictNextPoint(double* status){
    long result = 0;

    size_t nextPointNumber = this->nextPoints.size();

    double softmaxInput[nextPointNumber];
    double softmaxOutput[nextPointNumber];

    
    //compute the value of all the next points:
    for(size_t i=0; i<nextPointNumber; i++){
      softmaxInput[i] = math::Util::dotProduct(status, this->statusNumber, this->inputParameters[i]);
      this->hiddenLayerValue[i] = softmaxInput[i];
    }
    
    math::Util::softmax(softmaxInput, nextPointNumber, softmaxOutput);

    double maxValue = 0;
    size_t maxPosition = 0;

    for(size_t i=0; i<nextPointNumber; i++){
      if(softmaxOutput[i] > maxValue){
        maxValue = softmaxOutput[i];
        maxPosition = i;
      }
    }
    
    result = this->nextPoints[maxPosition];

    updateOutputStatus();

    return result;
  }

  vector<double> Point::getOutputStatus(){
    vector<double> result;
    for(size_t i=0; i<Point::statusNumber; i++){
      result.push_back(vector<double>::value_type(this->outputStatus[i]));
    }
    return result;
  }

  vector<double> Point::getInputStatusGradient(){
    //cout << "getting inputStatusGradient, the first element is: " << this->inputStatusGradient[0] << endl;
    vector<double> result;
    for(size_t i=0; i<Point::statusNumber; i++){
      result.push_back(vector<double>::value_type(this->inputStatusGradient[i]));
    }
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
    return math::RandomFactory::getNext();
  }

}