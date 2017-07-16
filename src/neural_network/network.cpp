#include "network.h"

using namespace std;

namespace katen{

  Network::Network(){

  }

  int Network::addNeuronIfNotExist(Neuron *p_newNeuron){
    cout << "adding Neuron" << endl;
    if (this->isInTheNetwork(p_newNeuron)){
      return 1;  
    }else{
      this->allNeuronMap.insert(map<long, Neuron*> :: value_type( p_newNeuron->getID(), p_newNeuron));
    }
    return 0;
  }

  int Network::addNeuron(Neuron *p_newNeuron){
    cout << "updating Neuron" << endl;
    this->allNeuronMap.insert(map<long, Neuron*>::value_type(p_newNeuron->getID(), p_newNeuron));
    return 0;
  }

  int Network::connectNeuron(Neuron *p_sourceNeuron, Neuron *p_targetNeuron){
    cout << "connect Neuron" << endl;
    this->addNeuronIfNotExist(p_sourceNeuron);
    this->addNeuronIfNotExist(p_targetNeuron);
    p_sourceNeuron->connectTo(*p_targetNeuron);
    p_targetNeuron->connectFrom(*p_sourceNeuron);
    return 0;
  }

  int Network::disconnectNeuron(Neuron *p_sourceNeuron, Neuron *p_targetNeuron){
    cout << "disconnect Neuron" << endl;
    return 0;
  }

  int Network::setInputNeuron(Neuron *p_targetNeuron){
    cout << "setting InputNeuron" << endl;
    this->addNeuronIfNotExist(p_targetNeuron);
    this->allInputNeuronMap.insert(map<long, Neuron*>::value_type(p_targetNeuron->getID(),p_targetNeuron));
    return 0;
  }

  int Network::setOutputNeuron(Neuron *p_targetNeuron){
    cout << "setting OutputNeuron" << endl;
    this->addNeuronIfNotExist(p_targetNeuron);
    this->allOutputNeuronMap.insert(map<long, Neuron*>::value_type(p_targetNeuron->getID(),p_targetNeuron));
    return 0;
  }

  map<long, Neuron*> Network::getAllInputNeurons(){
    return this->allInputNeuronMap;
  }

  map<long, Neuron*> Network::getAllOutputNeurons(){
    return this->allOutputNeuronMap;
  }

  bool Network::isInTheNetwork(Neuron *p_neuron){
    bool result = false;
    map<long,Neuron*>::iterator it;
    it = this->allNeuronMap.find(p_neuron->getID());
    if (it == this->allNeuronMap.end()){
      result = false;
    }else{
      result = true;
    }

    return result;
  }

}