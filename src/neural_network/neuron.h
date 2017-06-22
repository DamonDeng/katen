#ifndef DAMONDENG_KATEN_NEURON
#define DAMONDENG_KATEN_NEURON

#include <map>

using namespace std;

namespace katen{

  class Neuron{
    public:
      Neuron();

      int connectFrom(Neuron inputNeuron);
      int connectTo(Neuron outputNeuron);

      int forward();
      int backward();

      map<long, Neuron> getAllNextNeuron();
      map<long, Neuron> getAllPrevNeuron();

      long getID();

    private:
      long id;
      map<long, Neuron> inputNeuronMap;
      map<long, Neuron> outputNeuronMap;

      long _genUID();
      


  };

}

#endif