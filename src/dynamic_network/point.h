#ifndef DAMONDENG_KATEN_POINT
#define DAMONDENG_KATEN_POINT

#include <vector>
#include <sstream>

using namespace std;

namespace katen{

  class Point{
    public:
      Point(long ID);
      ~Point();
      Point(const Point& point);

      long getID();

      int connectTo(long nextPoint, vector<double> status);

      vector< vector<double> > getInputParameters();
      vector< vector<double> > getOutputParameters();

      vector<double> getOutputStatus();
      vector<double> getInputStatusGradient();

      int updateStatusParametersWithBP(vector<double> outputStatusGradient);

      long predictNextPoint(vector<double> status);

      string getReportInformation();

      static const double stepSize;

    
    
    private:
      long ID;
      
      vector<long> nextPoints;
      vector<double> inputStatus;
      vector<double> outputStatus;

      vector< vector<double> > inputParameters;
      vector< vector<double> > outputParameters;

      vector<double> inputStatusGradient;
      vector<double> hiddenLayerValue;

      int connectToNewPoint(long nextPoint, vector<double> status);
      int updateOldPoint(long nextPoint, vector<double> status);

      int updateOutputStatus();

      int positionInNextPoints(long nextPoint);
      bool isInNextPoints(long nextPoint);

      int addNextPoint(long nextPoint);

      double generateInitParameter();

  };

}


#endif