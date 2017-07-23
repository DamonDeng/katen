#include "util.h"
#include <cmath>

using namespace std;

namespace katen{

  namespace math{

  Util::Util(){

  }

  int Util::softmax(const double inputValue[], size_t valueNumber, double resultValue[]){
    int result = 0;

    double expValue[valueNumber];
    double sumValue=0;

    for(size_t i=0; i<valueNumber; i++){
      expValue[i] = exp(inputValue[i]);
      sumValue = sumValue + expValue[i];
    }

    for(size_t i=0; i<valueNumber; i++){
      resultValue[i] = expValue[i]/sumValue;
      
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

  int Util::softmaxCrossEntropyBP(const double softmaxOutput[], size_t valueNumber, double gradient[], long rightPosition){
    int result = 0;

    for(size_t i=0; i<valueNumber; i++){
      if(i == rightPosition){
        gradient[i] = softmaxOutput[i]-1;
      }else{
        gradient[i] = softmaxOutput[i];
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
       
  }

}