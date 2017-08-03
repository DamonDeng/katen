#include "point_manager.h"

namespace katen{

  const string startPointString = "KATEN_DAMON_STARTPOINT_4455"; //it is a magic string identifying the first point.

  PointManager::PointManager(){

    long startKey = Dictionary::getInstance()->addValue(startPointString);
    Point* firstPoint = new Point(startKey);
    this->allPoints.insert(map<long, Point*>::value_type(startKey, firstPoint));
    this->history.push_back(vector<Point*>::value_type(firstPoint));

    for(size_t i=0; i<defaultStatusNumber; i++){
      double randomValue = math::RandomFactory::getNext();
      currentStatus.push_back(vector<double>::value_type(randomValue));
      predictStatus.push_back(vector<double>::value_type(randomValue));
      initStatus.push_back(vector<double>::value_type(randomValue));
      
    } 

  }

  int PointManager::insertString(string inputString){
    int result = 0;

    long currentKey = Dictionary::getInstance()->addValue(inputString);

    map<long, Point*>::iterator it = allPoints.find(currentKey);
    Point* p_currentPoint;
    
    if(it == allPoints.end()){
      //cout << "added point is not in all points, creating new Point." << endl; 
      p_currentPoint = new Point(currentKey);
      allPoints.insert(map<long, Point*>::value_type(currentKey, p_currentPoint));
    }else{
      //cout << "added point is in all points, using old Point." << endl; 
      p_currentPoint = allPoints[currentKey];  
    }

    Point* p_prevPoint = history.front(); // get the first element in the history, it is the prev point.
    p_prevPoint->connectTo(currentKey, this->currentStatus);


    //string reportInformation = p_prevPoint->getReportInformation();
    //cout << reportInformation;

    vector<double> newStatus = p_prevPoint->getOutputStatus();
    size_t currentStatusNumber = currentStatus.size();

    for(size_t i=0; i<newStatus.size(); i++){
      if(i < currentStatusNumber){
        currentStatus[i] = newStatus[i];
      }else{
        currentStatus.push_back(vector<double>::value_type(newStatus[i]));
      }  
    }

    //cout << "number of newStatus is: " << newStatus.size() << endl;
    //cout << "number of currentStatus of pointManager after getting OutputStatus is: " << this->currentStatus.size() << endl;
    

    if(history.size() < 2){
      //history size is 1, that means it is in the initial state.
      //do nothing.

    }else{
      
      list<Point*>::iterator it;
      it = history.begin();
      it++; // point to the second element
      Point* p_processingCurrentPoint = p_prevPoint;
      Point* p_processingPrevPoint;
      
      int iter_number = 0;

      while(it!=history.end()){
        //cout << "updating history: ";
        //cout << " " << iter_number << endl;
        iter_number++;

        p_processingPrevPoint = *it;

        //reportInformation = p_processingPrevPoint->getReportInformation();
        //cout << reportInformation;

        vector<double> inputStatusGradient = p_processingCurrentPoint->getInputStatusGradient();
        p_processingPrevPoint->updateStatusParametersWithBP(inputStatusGradient);

        p_processingCurrentPoint = p_processingPrevPoint;
        
        it++;

      }

      
    }

    history.push_front(p_currentPoint);
    if(history.size() > this->historyLength){
      history.pop_back();
    }
    return result;
    
  }

   
  int PointManager::resetPredictStatus(){
    int result = 0;
    for(size_t i=0; i<this->predictStatus.size() && i<this->initStatus.size(); i++){
      this->predictStatus[i] = this->initStatus[i];
    }
    return result;
  }

  vector<string> PointManager::predictString(string startString, int predictTime){
    cout << "start to predict string-------------------------" << endl;
    
    vector<string> result;
    if(!this->isPointInManager(startString)){
      return result;
    }
    long currentKey = Dictionary::getInstance()->addValue(startString);

    Point* p_currentPoint = this->allPoints[currentKey];
    cout << "start to predict first Point" << endl;
    long nextKey = p_currentPoint->predictNextPoint(this->predictStatus);
    cout << "get the first key of nextkey" << nextKey << endl;
    
    for(int i=0; i<predictTime; i++){
      //cout << "p_" << i << ": ";
      string nextString = Dictionary::getInstance()->getValue(nextKey);
      result.push_back(vector<string>::value_type(nextString));
      vector<double> newStatus = p_currentPoint->getOutputStatus();
      p_currentPoint = this->allPoints[nextKey];
      
      // string debugOutputString = Dictionary::getInstance()->getValue(nextKey);
      // cout << "current characters: " << debugOutputString << endl;
      // for (size_t tempi=0; tempi<newStatus.size(); tempi++){
      //   cout << " " << newStatus[tempi];
      // }
      // cout << endl;

      nextKey = p_currentPoint->predictNextPoint(newStatus);
      if(nextKey == 1){
        // break the loop if it return the first element which is the magic string.
        // As it means that current Point do not have next.
        break;
        
      }
    }

    cout << endl;
    
    return result;

  }

  bool PointManager::isPointInManager(long value){
    bool result = false;

    map<long, Point*>::iterator it = allPoints.find(value);
    Point* p_currentPoint;
    
    if(it != allPoints.end()){
      result = true; 
    }

    return result;

  }

  bool PointManager::isPointInManager(string valueString){
    long currentKey = Dictionary::getInstance()->addValue(valueString);

    bool result = this->isPointInManager(currentKey);

    return result;
  }

}


