#include <iostream>
#include "neuron.h"

using namespace std;

namespace katen{

    Neuron::Neuron(){
      this->id = _genUID();   
      maxLayerNumber = 0;
      confirmLayerNumber = 0; 
    }

    

    int Neuron::connectFrom(Neuron *p_inputNeuron){
      this->inputNeuronMap.insert(map<long, Neuron*>::value_type(p_inputNeuron->getID(), p_inputNeuron));
      return 0;
    }

    map<long, Neuron*> Neuron::getAllPrevNeuron(){
      return this->inputNeuronMap;
    }

    int Neuron::connectTo(Neuron *p_outputNeuron){
      this->outputNeuronMap.insert(map<long, Neuron*>::value_type(p_outputNeuron->getID(), p_outputNeuron));
      return 0;
    }

    map<long, Neuron*> Neuron::getAllNextNeuron(){
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

    int Neuron::computeLayerNumber(long prevLayerNumber){
      //return value: 0 normal, 1 has circle;
      int result = 0;

      cout << "computing layer number in: " << this->id << endl;
      long currentLayerNumber = prevLayerNumber + 1;

      if(this->confirmLayerNumber != 0){
        //there is circle in this structure, return 1;
        result = 1;
        return result;
      }

      if (currentLayerNumber > this->maxLayerNumber){
        this->maxLayerNumber = currentLayerNumber;
      }

      this->potentialLayerNumbers.push_back(currentLayerNumber);

      if(this->inputNeuronMap.size() == 0){
        confirmLayerNumber = this->maxLayerNumber;
      }else{
        if(this->potentialLayerNumbers.size() == this->inputNeuronMap.size()){
          confirmLayerNumber = this->maxLayerNumber;
        }
      }
      
      
      map<long, Neuron*>::iterator it;
      int tempResult = 0;

      cout << "the size of output Neuron of: " << this->id << " is: " << outputNeuronMap.size() << endl;

      for(it = outputNeuronMap.begin(); it != outputNeuronMap.end(); it++){
        tempResult = it->second->computeLayerNumber(currentLayerNumber);
        if(tempResult == 1){
          result = 1;
        }
      }

      //normal result, not circle in this structure.
      return result;
    }

    int Neuron::resetComputeLayerNumber(){
      this->confirmLayerNumber = 0;
      this->potentialLayerNumbers.clear();
      this->maxLayerNumber = 0;
      return 0;
    }



    long Neuron::getID(){
      return this->id;
    }

    long Neuron::_genUID(){
      static long istart=0;
      return istart++;
    }

    long Neuron::getLayerNumber(){
      return this->confirmLayerNumber;
    }

    
    


}

