#include <iostream>

#include "util.h"

using namespace std;
using namespace katen;

int main(int argc, char * argv[]){

  cout << "testing of math util" << endl;

  double inputValue[] = {1.0, 2.0, -1.0, -1.0};
  double labelValue[] = {1.0, 0.0, 0.0};
  
  double weight[3][4] = {
          {1.0, 1.0, 1.0, 1.0},
          {1.0, 1.0, 1.0, 1.0},
          {1.0, 1.0, 1.0, 1.0}
          };
  
  double fullConnectResult[3];

  int totalIterTime = 10;

  for(int iterTime=0; iterTime<totalIterTime; iterTime++){
 for(int i=0; i<3; i++){
    fullConnectResult[i] = Util::dotProduct(inputValue, weight[i], 4);
  }



  double resultValue[] = {0.0, 0.0, 0.0};
  size_t valueNumber = sizeof(fullConnectResult)/sizeof(fullConnectResult[0]);

  cout << "valueNumber: " << valueNumber << endl;

  Util::softmax(fullConnectResult, valueNumber, resultValue);

  for(size_t i=0; i<valueNumber; i++){
    cout << "value of resultValue[" << i << "]: " << resultValue[i] << endl;

  }

  double crossEntropy = Util::crossEntropy(resultValue, valueNumber, labelValue);

  cout << "the crossEntropy is: " << crossEntropy << endl;

  double gradient[3];

  Util::softmaxCrossEntropyBP(resultValue, 3, gradient, 0);

  for(size_t i=0; i<3; i++){
    cout << "gradient of [" << i << "]: " << gradient[i] << endl;

  }

  for (int i=0; i<3; i++){
    for (int j=0; j<4; j++){
      weight[i][j] = weight[i][j] - gradient[i]*inputValue[j]; 
    }
  }

  for (int i=0; i<3; i++){
    cout << "weight[" << i << "]: ";
    for (int j=0; j<4; j++){
      cout << weight[i][j] << " ";
      }
    cout << endl;;
  }

  }
  
 
  
  return 0;

}

