#ifndef DAMONDENG_KATEN_POINTMANAGER
#define DAMONDENG_KATEN_POINTMANAGER

#include "point.h"
#include "dictionary.h"
#include "dmath/util.h"
#include "dmath/random_factory.h"

#include <vector>
#include <list>

using namespace std;

namespace katen{

  class PointManager{
    public:
      PointManager();

      int insertString(string inputString);
      vector<string> predictString(string startString, int predictTime);
      string predictString(string inputString);
      int resetPredictStatus();
      static const int defaultStatusNumber=10;
      static const int historyLength=1000;

    private:

      map<long, Point*> allPoints;
      list<Point*> history;

      vector<double> currentStatus;
      vector<double> predictStatus;
      vector<double> initStatus;

      bool isPointInManager(long value);
      bool isPointInManager(string valueString);
      
  };
}


#endif // !DAMONDENG_KATEN_POINTMANAGER
