#include <iostream>

#include "point.h"
#include "dmath/util.h"
#include "dmath/random_factory.h"

using namespace std;

namespace katen{

  const double Point::stepSize = 0.1;

  Point::Point(long ID){
    this->ID = ID;
   
  }

  Point::Point(const Point& point){
    cout << "copying a new Point" << endl;
    this->ID = point.ID;

    this->nextPoints.insert(this->nextPoints.end(), point.nextPoints.begin(), point.nextPoints.end());
    this->inputStatus.insert(this->inputStatus.end(), point.inputStatus.begin(), point.inputStatus.end());
    this->outputStatus.insert(this->outputStatus.end(), point.outputStatus.begin(), point.outputStatus.end());
    this->inputStatusGradient.insert(this->inputStatusGradient.end(), point.inputStatusGradient.begin(), point.inputStatusGradient.end());
    this->hiddenLayerValue.insert(this->hiddenLayerValue.end(), point.hiddenLayerValue.begin(), point.hiddenLayerValue.end());
    
    
    for(size_t i=0; i<point.inputParameters.size(); i++){
      vector<double> tempParameters;
      tempParameters.insert(tempParameters.begin(), point.inputParameters[i].begin(), point.inputParameters[i].end());
      this->inputParameters.push_back(vector< vector<double> >::value_type(tempParameters));
    }
    
    for(size_t i=0; i<point.outputParameters.size(); i++){
      vector<double> tempParameters;
      tempParameters.insert(tempParameters.begin(), point.outputParameters[i].begin(), point.outputParameters[i].end());
      this->outputParameters.push_back(vector< vector<double> >::value_type(tempParameters));
    }

    // if you add any other attributes, rember to copy those attributes.
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
  int Point::connectTo(long nextPoint, vector<double> status){
    int result = 0;

    //cout << "::::::Point " << this->ID << " Connecting to: " << nextPoint ;
    //cout << "-------------------------------------------" << endl;

    size_t currentStatusNumber = this->inputStatus.size();
    for(size_t i=0; i<status.size(); i++){
      if(i < currentStatusNumber){
        this->inputStatus[i] = status[i];
      }else{
        this->inputStatus.push_back(vector<double>::value_type(status[i]));
      }
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
  int Point::connectToNewPoint(long nextPoint, vector<double> status){
    int result = 0;

    this->nextPoints.push_back(nextPoint);
    
    vector<double>* p_pointInputParameters = new vector<double>;
    vector<double>* p_pointOutputParameters = new vector<double>;
    
    for(size_t i=0; i<status.size(); i++){
      p_pointInputParameters->push_back(vector<double>::value_type(this->generateInitParameter()));
      p_pointOutputParameters->push_back(vector<double>::value_type(this->generateInitParameter()));
    }

    this->inputParameters.push_back(vector< vector<double> >::value_type(*p_pointInputParameters));
    this->outputParameters.push_back(vector< vector<double> >::value_type(*p_pointOutputParameters));
    
    size_t hiddenLayerNumber = this->hiddenLayerValue.size();

    for(size_t i=0; i<this->nextPoints.size(); i++){
      if(i < hiddenLayerNumber){
        this->hiddenLayerValue[i] = 0;
      }else{
        this->hiddenLayerValue.push_back(vector<double>::value_type(0));
      }
      
    }
    
    return result;
  }

  //update oldarget with the status.
  //the value of all the inputParameters should be updated based on softmax and cross entropy.

  //the structure of the inputParameters is a vector of double array.
  // {point1:{status1, status2, ...}, point2:{status1, status2}}
  int Point::updateOldPoint(long nextPoint, vector<double> status){
    //it is possible that the size of status is different from the size of inputParameters.
    //to do, handle this issue.
    //at present, we just use the min size of status and inputParameters.
    int result = 0;

    int rightPosition = positionInNextPoints(nextPoint);

    //cout << "should update the parameters with the result of position: " << rightPosition << endl;
    size_t nextPointNumber = this->nextPoints.size();

    vector<double> softmaxInput;
    
    
    
    //compute the value of hiddenLayer of all the next points:
    //div it with the size of status, to avoid status explosion.
    for(size_t i=0; i<nextPointNumber; i++){
      double dotProductResult = math::Util::dotProduct(status, this->inputParameters[i]);
      //dotProductResult = dotProductResult/status.size();
      softmaxInput.push_back(vector<double>::value_type(dotProductResult));
      this->hiddenLayerValue[i] = dotProductResult;
    }

    // cout << "softmax input: " ;
    // for(size_t i=0; i<softmaxInput.size(); i++){
    //   cout << "  " << softmaxInput[i];
    // }
    // cout << endl;

    vector<double> softmaxOutput = math::Util::softmax(softmaxInput);

    // cout << "softmax output: " ;
    // for(size_t i=0; i<softmaxOutput.size(); i++){
    //   cout << "  " << softmaxOutput[i];
    // }
    // cout << endl;

    vector<double> gradient = math::Util::softmaxCrossEntropyBP(softmaxOutput, rightPosition);

    // cout << "gradient: " ;
    // for(size_t i=0; i<nextPointNumber; i++){
    //   cout << "  " << gradient[i];
    // }
    // cout << endl;

    //clear old gradient of inputStatus:
    //it is updated base on the number of inputStatus, not inputStatusGradient itself.
    //as the initial number of inputStatusGradient is 0.
    
    //this->inputStatusGradient.clear();
    //this->inputStatusGradient.swap(vector<double>());

    size_t numberOfGradients = inputStatusGradient.size();
    for(size_t i=0; i<this->inputStatus.size(); i++){
      if(i < numberOfGradients){
        this->inputStatusGradient[i] = 0;
      }else{
        this->inputStatusGradient.push_back(vector<double>::value_type(0));
      }
      
    }

    // cout << "updating parameter: " << endl;
    // cout << "next point number: " << nextPointNumber << endl;
    // cout << "size of inputParameters:" << this->inputParameters.size() << endl;
    // cout << "size of inputStatusGradient:" << this->inputStatusGradient.size() << endl;
    

    for(size_t i=0; i<nextPointNumber; i++){
      //cout << "size of inputParameters[" << i << "]: " << inputParameters[i].size() << endl;
      for(size_t j=0; j<this->inputParameters[i].size(); j++){

       
        //comput currentGradient for weight current connection from inputStatus to hidden layer:
        double currentGradient = Point::stepSize*gradient[i]*status[j];

        //update inputParameters for gradient decent:
        //cout << " " << this->inputParameters[i][j] << "(-" << currentGradient << ") "; 
        this->inputParameters[i][j] = this->inputParameters[i][j] - currentGradient;
        
        //cout << " [" << this->inputStatusGradient[j] << " (+" << currentGradient << ")]  ";
        //accumulate gradient for all the inputStatus, for BP to prev point:
        this->inputStatusGradient[j] = this->inputStatusGradient[j] + currentGradient;

      }
      //cout << endl;
    }

    //cout << "after updating inpuStatusGradient: " << this->inputStatusGradient[0] << endl;

    // for(int i=0; i<this->inputStatusGradient.size(); i++){
    //   cout << " " << this->inputStatusGradient[i];
    // }
    // cout << endl;

    return result;
  }

  int Point::updateOutputStatus(){
    int result = 0;

    size_t nextPointNumber = this->nextPoints.size();

    double hiddenLayer[nextPointNumber];
    
    
    for(size_t i=0; i<nextPointNumber; i++){
      //the hiddenLayerValue has been computed in updateOldNextPoint method, don't need to be computed again.
      //hiddenLayer[i] = math::Util::dotProduct(this->inputStatus, this->inputParameters[i]);
      
      hiddenLayer[i] = this->hiddenLayerValue[i];
    }

    double tempParameters[nextPointNumber];

    size_t outputStatusNumber = this->outputStatus.size();
    double maxDotProductResult = 0;
    double absDotProductResult = 0;
    
    for(size_t s=0; s<this->inputStatus.size(); s++){
      
      for(size_t i=0; i<nextPointNumber; i++){
        tempParameters[i] = this->outputParameters[i][s];
      }
      double dotProductResult = math::Util::dotProduct(hiddenLayer, nextPointNumber, tempParameters);
      //div dotProductReuslt with nextPointNumber to avoid output status explosion.
      //dotProductResult = dotProductResult/nextPointNumber;
      absDotProductResult = fabs(dotProductResult);
      if(maxDotProductResult < absDotProductResult){
        maxDotProductResult = absDotProductResult;
      }
      if(s < outputStatusNumber){
        this->outputStatus[s] = dotProductResult;
      }else{
        this->outputStatus.push_back(vector<double>::value_type(dotProductResult));
      }    
    }

    for(size_t s=0; s<this->inputStatus.size(); s++){
      this->outputStatus[s] = this->outputStatus[s]/maxDotProductResult;
    }

    return result;

  }

  int Point::updateStatusParametersWithBP(vector<double> outputStatusGradient){
    int result = 0;

    size_t nextPointNumber = this->nextPoints.size();
    // cout << "Updating output_parameters of: " << this->ID << endl;
    // cout << "nextPointNumber: " << nextPointNumber << endl;
    // cout << "outputStatus number:" << this->outputStatus.size() << endl;
    // cout << "outputGradient number: " << outputStatusGradient.size() << endl;

    for(size_t i=0; i<this->outputStatus.size(); i++){
      for(size_t j=0; j<nextPointNumber; j++){
        //cout << "h(" << this->hiddenLayerValue[j] << ")* g(" << outputStatusGradient[i] << ") ";
        double currentGradient = Point::stepSize*outputStatusGradient[i]*this->hiddenLayerValue[j];
        //cout << " " << this->outputParameters[j][i] << " (-" << currentGradient << ") ";
        this->outputParameters[j][i] = this->outputParameters[j][i] - currentGradient;
      }
    }
    //cout << endl;
    
    return result;

  }


  long Point::predictNextPoint(vector<double> status){
    //cout << "predicting point: " << this->ID << " " << endl;
    long result = 0;

    size_t nextPointNumber = this->nextPoints.size();

    if(nextPointNumber == 0){
      //cout << "this point do not have next point:" << endl;
      result = 1; // returning the first element, if current point donot have next one;
      return result;
    }

    //double softmaxInput[nextPointNumber];
    //double softmaxOutput[nextPointNumber];
    vector<double> softmaxInput;

     //cout << "before dotproduct" << endl;
    //compute the value of all the next points:
    size_t hiddenLayerNumber = this->hiddenLayerValue.size();
    for(size_t i=0; i<nextPointNumber; i++){
      double dotProductResult = math::Util::dotProduct(status, this->inputParameters[i]);
      softmaxInput.push_back(vector<double>::value_type(dotProductResult));
      if(i < hiddenLayerNumber){
        this->hiddenLayerValue[i] = dotProductResult;
   
      }else{
        this->hiddenLayerValue.push_back(vector<double>::value_type(dotProductResult));
   
      }
    }
    
    //cout << "before softmax" << endl;
    vector<double> softmaxOutput = math::Util::softmax(softmaxInput);
    //cout << "after softmax" << endl;
    
    double maxValue = 0;
    size_t maxPosition = 0;

    //cout << "before nextPointNumber loop" << endl;
    for(size_t i=0; i<nextPointNumber; i++){
      if(softmaxOutput[i] > maxValue){
        maxValue = softmaxOutput[i];
        maxPosition = i;
      }
    }
    //cout << "after nextPointNumber loop" << endl;
    //cout << "the maxPosition number: " << maxPosition << endl;
    //cout << "the size of nextPoints: " << this->nextPoints.size();
    result = this->nextPoints[maxPosition];
    //cout << "before updating output status" << endl;
    updateOutputStatus();

    return result;
  }

  vector<double> Point::getOutputStatus(){
    
    return this->outputStatus;
  }

  vector<double> Point::getInputStatusGradient(){
    //cout << "getting inputStatusGradient, the first element is: " << this->inputStatusGradient[0] << endl;
    
    return this->inputStatusGradient;
    
  }

  vector< vector<double> > Point::getInputParameters(){
    return this->inputParameters;
  }

  vector< vector<double> > Point::getOutputParameters(){
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

  string Point::getReportInformation(){
    ostringstream os_report;
    os_report << "Report information os Point" << this->ID << ":-------------------" << endl;

    os_report << "NextPoints:  ";
    for(size_t i=0; i<this->nextPoints.size(); i++){
      os_report << " " << this->nextPoints[i] << " ";
    }
    os_report << endl;

    os_report << "inputStatus:  ";
    for(size_t i=0; i<this->inputStatus.size(); i++){
      os_report << " " << this->inputStatus[i] << " ";
    }
    os_report << endl;

    os_report << "hiddenLayerValue:  ";
    for(size_t i=0; i<this->hiddenLayerValue.size(); i++){
      os_report << " " << this->hiddenLayerValue[i] << " ";
    }
    os_report << endl;

    os_report << "outputStatus:  ";
    for(size_t i=0; i<this->outputStatus.size(); i++){
      os_report << " " << this->outputStatus[i] << " ";
    }
    os_report << endl;

    os_report << "inputStatusGradient:  ";
    for(size_t i=0; i<this->inputStatusGradient.size(); i++){
      os_report << " " << this->inputStatusGradient[i] << " ";
    }
    os_report << endl;

    os_report << "inputParameters:  " << endl;
    
    for(size_t i=0; i<this->inputParameters.size(); i++){
      for(size_t j=0; j<this->inputParameters[i].size(); j++){
        os_report << " " << this->inputParameters[i][j] << " ";
      } 
      os_report << endl;
    }
    
    os_report << "outputParameters:  " << endl;
    
    for(size_t i=0; i<this->outputParameters.size(); i++){
      for(size_t j=0; j<this->outputParameters[i].size(); j++){
        os_report << " " << this->outputParameters[i][j] << " ";
      } 
      os_report << endl;
    }

    os_report << "-----------------------------" << endl;

    return os_report.str();

  }

}