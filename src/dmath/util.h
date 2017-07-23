#ifndef DAMONDENG_KATEN_MATHUTIL
#define DAMONDENG_KATEN_MATHUTIL

#include <iostream>

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

    private:

  };
}
}

#endif