#include <iostream>
#include "neuron.h"

using namespace std;

namespace katen{

    Neuron::Neuron(){
      this->id = _genUID();    
    }

    

    int Neuron::connectFrom(Neuron inputNeuron){
      this->inputNeuronMap.insert(map<long, Neuron>::value_type(inputNeuron.getID(), inputNeuron));
      return 0;
    }

    map<long, Neuron> Neuron::getAllPrevNeuron(){
      return this->inputNeuronMap;
    }

    int Neuron::connectTo(Neuron outputNeuron){
      this->outputNeuronMap.insert(map<long, Neuron>::value_type(outputNeuron.getID(), outputNeuron));

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

    int Neuron::deepForward(){
      cout << "deep forward in: " << this->id << endl;
      
      this->forward();
      map<long, Neuron>::iterator it;
      for(it = outputNeuronMap.begin(); it != outputNeuronMap.end(); it++){
        it->second.deepForward();
      }

      return 0;
    }

    int Neuron::deepBackward(){
      cout << "deep backward in: " << this->id << endl;
      
      this->backward();
      map<long, Neuron>::iterator it;
      for(it = inputNeuronMap.begin(); it != inputNeuronMap.end(); it++){
        it->second.deepForward();
      }

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

