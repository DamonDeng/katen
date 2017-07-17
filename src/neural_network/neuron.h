#ifndef DAMONDENG_KATEN_NEURON
#define DAMONDENG_KATEN_NEURON

#include <map>
#include <vector>

using namespace std;

namespace katen{

  class Neuron{
    public:
      Neuron();

      int connectFrom(Neuron *p_inputNeuron);
      int connectTo(Neuron *p_outputNeuron);

      int forward();
      int backward();

      int computeLayerNumber(long prevLayerNumber);
      int resetComputeLayerNumber();

      map<long, Neuron*> getAllNextNeuron();
      map<long, Neuron*> getAllPrevNeuron();

      long getID();
      long getLayerNumber();

    private:
      long id;
      map<long, Neuron*> inputNeuronMap;
      map<long, Neuron*> outputNeuronMap;

      long _genUID();
      
      long maxLayerNumber;
      long confirmLayerNumber;

      vector<long> potentialLayerNumbers;


  };

}

#endif