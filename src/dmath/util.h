#ifndef DAMONDENG_KATEN_MATHUTIL
#define DAMONDENG_KATEN_MATHUTIL

#include <iostream>
#include <time.h>
#include <random>

using namespace std;

namespace katen{

namespace math{
  class Util{
    public:
      Util();
      static vector<double> softmax(vector<double> inputValue);
      static double crossEntropy(const double inputValue[], size_t valueNumber, double labelValue[]);
      static vector<double> softmaxCrossEntropyBP(vector<double> softmaxOutput, long rightPosition);
      static double dotProduct(const double inputValue[], size_t valueNumber, const double weight[]);
      static double dotProduct(vector<double> inputValue, const vector<double> weight);
      
      //static int dotProductBP(const double inputValue[], double gradient[]);
      //static double randomDouble(double min, double max);

    private:

      //static std::default_random_engine random(time(NULL));  
      //static std::uniform_real_distribution<double> dis(-1.0, 1.0);  
   

  };
}
}

#endif