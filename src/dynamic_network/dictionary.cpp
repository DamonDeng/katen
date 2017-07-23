#include "dictionary.h"

#include <string>
#include <map>
#include <iostream>


namespace katen{

  std::mutex Dictionary::mtx;
  Dictionary* Dictionary::instance;

  Dictionary* Dictionary::getInstance(){
        if (instance == NULL){
          mtx.lock();
          if (instance == NULL){
              instance = new Dictionary();
          }
          mtx.unlock();
        }
        return instance;
      }
  

  Dictionary::Dictionary(){
    //private empty constructor;
  }


  Dictionary::Dictionary(const Dictionary& source){
    //private copy contructor;
  }



  Dictionary& Dictionary::operator=(const Dictionary& source){
    //private copy constructor with =;
    //this function will not be called, we set it as private.
    //the following return code is here to advoid the return warning.
    return *this;
  }

  bool Dictionary::isInIt(string value){
    bool result = false;
    
    map<string, long>::iterator it;
    it = this->idMap.find(value);
    
    if (it == this->idMap.end()){
      result = false;
    }else{
      result = true;
    }

    return result;
  }

  bool Dictionary::isInIt(int id){
    bool result = false;
    
    map<long, string>::iterator it;
    it = this->valueMap.find(id);
    
    if (it == this->valueMap.end()){
      result = false;
    }else{
      result = true;
    }

    return result;
  }

  long Dictionary::addValue(string value){
    long resultID = 0;
    if(!isInIt(value)){
      resultID = _genUID();
      this->idMap.insert(map<string, long>::value_type(value, resultID));
      this->valueMap.insert(map<long, string>::value_type(resultID, value));

    }else{
      //we are sure that the value is in the map
      resultID = this->idMap[value];
    }

    return resultID;
  }
  
  string Dictionary::getValue(long id){
    string resultValue = "";

    if(isInIt(id)){
      resultValue = this->valueMap[id];
    }

    return resultValue;

  }
  
  long Dictionary::getID(string value){
    long resultID = 0;

    if(isInIt(value)){
      resultID = this->idMap[value];
    }

    return resultID;
  }
  
  int Dictionary::removeValue(string value){
    int result = 0;
    if(isInIt(value)){
      long id = this->idMap[value];
      this->idMap.erase(value);
      this->valueMap.erase(id);
    }
    return result;
  }
  
  int Dictionary::removeValue(long id){
    int result = 0;
    if(isInIt(id)){
      string value = this->valueMap[id];
      this->idMap.erase(value);
      this->valueMap.erase(id);
    }
    return result;
  }
  


  long Dictionary::_genUID(){
    static long istart=1;
    return istart++;
  }


}