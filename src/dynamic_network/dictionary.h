#ifndef DAMONDENG_KATEN_DICTIONARY 
#define DAMONDENG_KATEN_DICTIONARY

#include <map>
#include <string>
#include <mutex>

using namespace std;

namespace katen{
  
  
  class Dictionary{
    public:
      static Dictionary* getInstance();
      
      bool isInIt(string value);
      bool isInIt(int id);
      
      long addValue(string value);
      string getValue(long id);
      long getID(string value);
      int removeValue(string value);
      int removeValue(long id);


    private:
      
      static std::mutex mtx;
      static Dictionary* instance;

      Dictionary();
      Dictionary(const Dictionary&);
	    Dictionary& operator=(const Dictionary&);
      
      map<string, long> idMap;
      map<long, string> valueMap;

      long _genUID();
      
      
  };
}

#endif