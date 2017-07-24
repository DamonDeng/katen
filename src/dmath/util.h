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
      static int softmax(const double inputValue[], size_t valueNumber, double resultValue[]);
      static double crossEntropy(const double inputValue[], size_t valueNumber, double labelValue[]);
      static int softmaxCrossEntropyBP(const double softmaxOutput[], size_t valueNumber, double gradient[], long rightPosition);
      static double dotProduct(const double inputValue[], size_t valueNumber, const double weight[]);
      //static int dotProductBP(const double inputValue[], double gradient[]);
      static double randomDouble(double min, double max);

    private:

      //static std::default_random_engine random(time(NULL));  
      //static std::uniform_real_distribution<double> dis(-1.0, 1.0);  
   

  };
}
}

#endif