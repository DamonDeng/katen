#include <iostream>
#include "network.h"
#include "neuron.h"
#include "executor.h"

using namespace std;
using namespace katen;

int neuronTest();
int networkTest();
int executorTest();

int main(int argc, char * argv[]){
  int result = 0;
  
  result = neuronTest();
  if (result != 0){
    return result;
  }

  result = networkTest();
  if (result != 0){
    return result;
  }

  result = executorTest();
  if (result != 0){
    return result;
  }

  return 0;
}

int neuronTest(){
    cout << "Main testing in neural network" << endl;

    Neuron firstNeuron = Neuron();
    Neuron *p_currentNeuron = &firstNeuron;

    cout << "the id of firstNeuron: " << firstNeuron.getID() << endl;
    cout << "the id of currentNeuron:" << p_currentNeuron->getID() << endl;

    for (int i=0;i<100;i++){
        Neuron testingNeuron = Neuron();
        p_currentNeuron->connectTo(&testingNeuron);
        p_currentNeuron = &testingNeuron;
        //cout << "the id of the neuron is:" << testingNeuron.getID() << endl;

    }

    //currentNeuron = firstNeuron;

    map<long, Neuron*> nextNeuron = firstNeuron.getAllNextNeuron();
    
    cout << "this size of the Map: " << nextNeuron.size() << endl;

     for(map<long, Neuron*>::iterator it = nextNeuron.begin(); it != nextNeuron.end(); it++ ){
       
       it->second->forward();
     }

    return 0;
}

int networkTest(){

  Network firstNetwork = Network();

  Neuron firstTestingNeuron = Neuron();
  Neuron secondTestingNeuron = Neuron();
  Neuron thirdTestingNeuron = Neuron();

  firstNetwork.addNeuron(&firstTestingNeuron);

  bool result = firstNetwork.isInTheNetwork(&firstTestingNeuron);

  if (result == false){
    cout << "didn't find the neuron" << endl;
  }else{
    cout << "found the neuron" << endl;
  }

  firstNetwork.connectNeuron(&firstTestingNeuron, &secondTestingNeuron);

  firstNetwork.connectNeuron(&secondTestingNeuron, &thirdTestingNeuron);

  firstNetwork.connectNeuron(&firstTestingNeuron, &thirdTestingNeuron);
  

  firstNetwork.setInputNeuron(&firstTestingNeuron);

  int tempResult = firstNetwork.updateLayerStructure();

  if(tempResult == 1){
    cout << "has circle in the network structure" << endl;
  }else{
    cout << "no circle in the network structure" << endl;
  }

  map<long, Neuron*> allNeuronMap = firstNetwork.getAllNeuronMap();

  map<long, Neuron*>::iterator it;

  for(it = allNeuronMap.begin(); it != allNeuronMap.end(); it++){
    cout << "the layer number of: " << it->second->getID() << " is: " << it->second->getLayerNumber() << endl;
  }

  return 0;
}

int executorTest(){
  Executor testExecutor = Executor();
  Network testNetwork = Network();

  testExecutor.bind(&testNetwork);
  return 0;
}