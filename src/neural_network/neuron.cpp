#include <iostream>
#include "neuron.h"

using namespace std;

namespace katen{

    Neuron::Neuron(){
      this->id = _genUID();    
    }

    // map<long, Neuron> Neuron::inputNeuronMap; 
    // map<long, Neuron> Neuron::outputNeuronMap; 

    int Neuron::connectFrom(Neuron inputNeuron){
      this->inputNeuronMap.insert(map<long, Neuron> :: value_type(inputNeuron.getID(), inputNeuron));
      return 0;
    }

    map<long, Neuron> Neuron::getAllPrevNeuron(){
      return this->inputNeuronMap;
    }

    int Neuron::connectTo(Neuron outputNeuron){
      this->outputNeuronMap.insert(map<long, Neuron> :: value_type(outputNeuron.getID(), outputNeuron));

      return 0;
    }

    map<long, Neuron> Neuron::getAllNextNeuron(){
      return this->outputNeuronMap;
    }

    int Neuron::forward(){
      cout << "forward in: " << this->id << endl;
      return 0;
    }

    int Neuron::backward(){
      cout << "backward in: " << this->id << endl;
      return 0;
    }

    long Neuron::getID(){
      return this->id;
    }

    long Neuron::_genUID(){
      static long istart=0;
      return istart++;
    }

    
    


}

