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

      vector< double* > getInputParameters();
      vector< double* > getOutputParameters();

      static const int statusNumber = 10;
      
    
    private:

      vector<long> nextTargets;
      vector<long> inputStatus;
      vector<long> outputStatus;

      vector< double* > inputParameters;
      vector< double* > outputParameters;

      

      int connectToNewTarget(long nextTarget, vector<double> status);
      int updateOldTarget(long nextTarget, vector<double> status);

      int positionInNextTargets(long nextTarget);
      bool isInNextTargets(long nextTarget);

      int addNextTarget(long nextTarget);

      double generateInitParameter();

  };

}


#endif