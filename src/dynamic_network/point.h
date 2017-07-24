#ifndef DAMONDENG_KATEN_TARGET
#define DAMONDENG_KATEN_TARGET

#include <vector>

using namespace std;

namespace katen{

  class Point{
    public:
      Point(long ID);
      ~Point();

      int connectTo(long nextPoint, double status[]);

      vector< double* > getInputParameters();
      vector< double* > getOutputParameters();

      double* getOutputStatus();
      double* getInputStatusGradient();

      int updateOutputParametersWithBP(double* outputStatusGradient);

      long predictNextPoint(double* status);

      static const int statusNumber = 10;
      
    
    private:
      long ID;
      
      vector<long> nextPoints;
      double inputStatus[statusNumber];
      double outputStatus[statusNumber];

      vector< double* > inputParameters;
      vector< double* > outputParameters;

      double* inputStatusGradient;
      vector<double> hiddenLayerValue;

      int connectToNewPoint(long nextPoint, double status[]);
      int updateOldPoint(long nextPoint, double status[]);

      int updateOutputStatus();

      int positionInNextPoints(long nextPoint);
      bool isInNextPoints(long nextPoint);

      int addNextPoint(long nextPoint);

      double generateInitParameter();

  };

}


#endif