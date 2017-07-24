#include "random_factory.h"

using namespace std;

namespace katen{
namespace math{

  std::mutex RandomFactory::mtx;
  RandomFactory* RandomFactory::instance;

  std::default_random_engine RandomFactory::random(time(NULL));  
  std::uniform_real_distribution<double> RandomFactory::dis(-1.0, 1.0);  
   

  RandomFactory* RandomFactory::getInstance(){
        if (instance == NULL){
          mtx.lock();
          if (instance == NULL){
              instance = new RandomFactory();
          }
          mtx.unlock();
        }
        return instance;
      }
  

  RandomFactory::RandomFactory(){
    //private empty constructor;
   
  }


  RandomFactory::RandomFactory(const RandomFactory& source){
    //private copy contructor;
  }



  RandomFactory& RandomFactory::operator=(const RandomFactory& source){
    //private copy constructor with =;
    //this function will not be called, we set it as private.
    //the following return code is here to advoid the return warning.
    return *this;
  }

  double RandomFactory::getNext(){
    return dis(random);
  }


}
}