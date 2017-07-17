#ifndef DAMONDENG_KATEN_NETWORK
#define DAMONDENG_KATEN_NETWORK

#include <iostream>
#include "neuron.h"

using namespace std;

namespace katen{
  class Network{
    public:
      Network();
      
      int addNeuron(Neuron *p_newNeuron);
      int addNeuronIfNotExist(Neuron *p_newNeuron);
      
      map<long, Neuron*> getAllNeuronMap();

      int connectNeuron(Neuron *p_sourceNeuron, Neuron *p_targetNeuron);
      int disconnectNeuron(Neuron *p_sourceNeuron, Neuron *p_targetNeuron);

      int setInputNeuron(Neuron *p_targetNeuron);
      int setOutputNeuron(Neuron *p_targetNeuron);

      map<long, Neuron*> getAllInputNeurons();
      map<long, Neuron*> getAllOutputNeurons();

      bool isInTheNetwork(Neuron *p_neuron);

      int updateLayerStructure();

    private:

      map<long, Neuron*> allNeuronMap;
      map<long, Neuron*> allInputNeuronMap;
      map<long, Neuron*> allOutputNeuronMap;

      bool isLayerStructureDirty;

      vector< vector<Neuron*> > layerStructure;
      

  };
}

#endif