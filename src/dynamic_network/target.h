#ifndef DAMONDENG_KATEN_TARGET
#define DAMONDENG_KATEN_TARGET

#include <vector>

using namespace std;

namespace katen{

  class Target{
    public:
      Target();
      ~Target();

      int connectTo(long nextTarget, vector<double> status);

      vector< vector<double> > getInputParameters();
      vector< vector<double> > getOutputParameters();
      
    
    private:

      vector<long> nextTargets;
      vector<long> inputStatus;
      vector<long> outputStatus;

      vector< double* > inputParameters;
      vector< double* > outputParameters;

      const int statusNumber = 10;

      int positionInNextTargets(long nextTarget);
      bool isInNextTargets(long nextTarget);

      int addNextTarget(long nextTarget);

      double generateInitParameter();

  };

}


#endif