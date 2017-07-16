#ifndef DAMONDENG_KATEN_EXECUTOR
#define DAMONDENG_KATEN_EXECUTOR

#include "network.h"
#include "neuron.h"

#include <iostream>

using namespace std;

namespace katen{
  class Executor{
    public:
      Executor();

      int bind(Network *targetNetwork);

    private:


  };

}


#endif