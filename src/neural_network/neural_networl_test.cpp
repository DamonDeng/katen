#include <iostream>
#include "network.h"
#include "neuron.h"

using namespace std;
using namespace katen;

int main(int argc, char * argv[]){

    cout << "Main testing in neural network" << endl;

    Neuron firstNeuron = Neuron();
    Neuron *currentNeuron = &firstNeuron;

    cout << "the id of firstNeuron: " << firstNeuron.getID() << endl;
    cout << "the id of currentNeuron:" << currentNeuron->getID() << endl;

    for (int i=0;i<100;i++){
        Neuron testingNeuron = Neuron();
        currentNeuron->connectTo(testingNeuron);
        currentNeuron = &testingNeuron;
        //cout << "the id of the neuron is:" << testingNeuron.getID() << endl;

    }

    //currentNeuron = firstNeuron;

    map<long, Neuron> nextNeuron = firstNeuron.getAllNextNeuron();

    

    cout << "this size of the Map: " << nextNeuron.size() << endl;

     for(map<long, Neuron>::iterator it = nextNeuron.begin(); it != nextNeuron.end(); it++ ){
       
       it->second.forward();
     }

    


    return 0;

}