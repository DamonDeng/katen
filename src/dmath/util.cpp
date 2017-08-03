#include "util.h"
#include <cmath>
#include <time.h>
#include <random>

using namespace std;

namespace katen{

  namespace math{

  Util::Util(){

  }

  vector<double> Util::softmax(vector<double> inputValue){
    vector<double> result;

    double maxValue = 1;
    double absValue = 0;

    for(size_t i=0; i<inputValue.size(); i++){
      absValue = fabs(inputValue[i]);  
      if(maxValue < absValue){
        maxValue = absValue;
      }
    }

    
  

    vector<double> expValue;
    double sumValue=0;

    for(size_t i=0; i<inputValue.size(); i++){
      double tempExpValue = exp(inputValue[i] / maxValue);
      if(tempExpValue!=tempExpValue){
        cout << "found NAN: input value is: " << inputValue[i] << endl;
      }
      expValue.push_back(vector<double>::value_type(tempExpValue));
      sumValue = sumValue + tempExpValue;
    }

    //cout << " tempDivValue:" << endl;
    for(size_t i=0; i<inputValue.size(); i++){
      double tempDivValue = expValue[i]/sumValue;
      
      if(tempDivValue!=tempDivValue){
        cout << "found NAN while diving: exp value is: " << expValue[i] << " sumValue is:" << sumValue << endl;
      }
      //cout << " " << tempDivValue;
      result.push_back(vector<double>::value_type(tempDivValue));
      
    }
    
    

    return result;
  }

  double Util::crossEntropy(const double inputValue[], size_t valueNumber, double labelValue[]){
    double result = 0;
    for(size_t i=0; i<valueNumber; i++){
      result = result + labelValue[i] * log(inputValue[i]) + (1 - labelValue[i]) * log(1 - inputValue[i]);
    }

    result = - result/valueNumber;

    return result;
  }

  vector<double> Util::softmaxCrossEntropyBP(const vector<double> softmaxOutput, long rightPosition){
    vector<double> result;

    for(size_t i=0; i<softmaxOutput.size(); i++){
      if(i == rightPosition){
        result.push_back(vector<double>::value_type(softmaxOutput[i]-1));
      }else{
        result.push_back(vector<double>::value_type(softmaxOutput[i]));
      }
    }

    return result;
  }

  double Util::dotProduct(const double inputValue[], size_t valueNumber, const double weight[]){
    double result = 0;
    for(size_t i=0; i<valueNumber; i++){
      result = result + inputValue[i]*weight[i];
    }
    return result;
  }

  double Util::dotProduct(const vector<double> inputValue, const vector<double> weight){
    double result = 0;
    for(size_t i=0; i<inputValue.size() && i<weight.size(); i++){
      result = result + inputValue[i]*weight[i];
    }
    return result;
  }
  
  // double Util::randomDouble(double min, double max){
   
  //   double result = dis(random);
  //   return result;
    
  // }


  }

 
}