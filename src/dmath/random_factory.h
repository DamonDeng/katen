#ifndef DAMONDENG_KATEN_MATH_RANDOMFACTORY
#define DAMONDENG_KATEN_MATH_RANDOMFACTORY

#include <mutex>
#include <random>
#include <time.h>


namespace katen{
namespace math{
  class RandomFactory{
     public:
      static RandomFactory* getInstance();
      static double getNext();
      
     

    private:
      
      static std::mutex mtx;
      static RandomFactory* instance;

      RandomFactory();
      RandomFactory(const RandomFactory&);
	    RandomFactory& operator=(const RandomFactory&);
      
      static std::default_random_engine random;   
      static std::uniform_real_distribution<double> dis;   
   
      

  };
}
}

#endif
