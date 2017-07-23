#ifndef DAMONDENG_KATEN_TARGET
#define DAMONDENG_KATEN_TARGET

#include <vector>

using namespace std;

namespace katen{

  class Point{
    public:
      Point();
      ~Point();

      int connectTo(long nextPoint, vector<double> status);

      vector< double* > getInputParameters();
      vector< double* > getOutputParameters();

      static const int statusNumber = 10;
      
    
    private:

      vector<long> nextPoints;
      vector<long> inputStatus;
      vector<long> outputStatus;

      vector< double* > inputParameters;
      vector< double* > outputParameters;

      

      int connectToNewPoint(long nextPoint, vector<double> status);
      int updateOldPoint(long nextPoint, vector<double> status);

      int positionInNextPoints(long nextPoint);
      bool isInNextPoints(long nextPoint);

      int addNextPoint(long nextPoint);

      double generateInitParameter();

  };

}


#endif