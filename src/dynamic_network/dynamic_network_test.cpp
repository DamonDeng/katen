#include <iostream>
#include <assert.h>
#include <vector>
#include <map>
#include <time.h>
#include <random>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include"stdlib.h"

#include "dictionary.h"
#include "point.h"

#include "dmath/util.h"
#include "dmath/random_factory.h"
#include "point_manager.h"

using namespace std;
using namespace katen;

int fileTest();
int dictionaryTest();
int pointTest();
int randomTest();
int randomTest2();
int multiplePointTest();
int stringSequenceTest();
int printParameters(Point testingPoint);
int printStatus(Point testingPoint);
vector<string> splitToCharacters(const string &s);

int pointManagerTest();

vector<long> getInputSequence();
int printSequence(vector<long> sequence);
vector<string> split(const string &s, const string &seperator);


int main(int argc, char * argv[]){
  int result = 0;
  
  cout << "dynamic network test" << endl;

  
  //dictionaryTest();

  //pointTest();
  //multiplePointTest();
  //stringSequenceTest();

  //randomTest2();

  //size_t resultNumber;
  //getInputSequence(resultNumber);

  pointManagerTest();

  //fileTest();

  cout << "step size: " << Point::stepSize << endl;

  //splitToCharacters("testing!");

  return result;
}

int dictionaryTest(){
  int result = 0;

  Dictionary* testingInstance1 = Dictionary::getInstance();

  cout << "the address of the instance1 is: " << testingInstance1 << endl;

  Dictionary* testingInstance2 = Dictionary::getInstance();

  cout << "the address of the instance2 is: " << testingInstance2 << endl;

  
  assert(testingInstance1 == testingInstance2);

  string testingValues[10] = {"abd", "efs", "中文", "aaa", "www", "werwer", "ss", "tt", "ss", "ee"};

  for(int i=0; i<10; i++){
  
    long id = testingInstance2->addValue(testingValues[i]);

    cout << "the id of " << testingValues[i] << " is: " << id << endl;
  }
  return result;


}

int pointTest(){
  int result = 0;

  // Point testingPoint = Point(10);

  // double inputStatus[] = {1.0, 1.0, 1.0};
  // double testingStatus[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

  // int arraySize = sizeof(inputStatus)/sizeof(inputStatus[0]);

  
  
  // testingPoint.connectTo(10, testingStatus);
  // testingPoint.connectTo(20, testingStatus);
  // testingPoint.connectTo(10, testingStatus);
  // testingPoint.connectTo(30, testingStatus);
  // testingPoint.connectTo(30, testingStatus);
  // testingPoint.connectTo(30, testingStatus);
  

  // vector< double* > parameters = testingPoint.getInputParameters();

  // cout << "the size of the parameters: " << parameters.size() << endl;
  
  // printParameters(testingPoint);

  // printStatus(testingPoint);

  return result;

}


int stringSequenceTest(){
  int result = 0;

  // vector<long> inputSequence = getInputSequence();
  
  // for(size_t i=0; i<inputSequence.size(); i++){
  //   cout << " " << inputSequence[i];
  // }
  // cout << endl;

  // double currentStatus[Point::statusNumber];
  // double predictStatus[Point::statusNumber];

  // for(size_t i=0; i<Point::statusNumber; i++){
  //   currentStatus[i] = math::RandomFactory::getNext();
  //   predictStatus[i] = currentStatus[i];
  // }

  
  // map<long, Point*> allPoints;
  // Point* p_prevPoint = NULL;

  // for(size_t i=0; i<inputSequence.size(); i++){
  //   map<long, Point*>::iterator it = allPoints.find(inputSequence[i]);
  //   Point* p_currentPoint;
    
  //   if(it == allPoints.end()){
  //     p_currentPoint = new Point(inputSequence[i]);
  //     allPoints.insert(map<long, Point*>::value_type(inputSequence[i], p_currentPoint));
  //   }
  // }

  // for(size_t i=0; i<inputSequence.size()-1; i++){
  //   map<long, Point*>::iterator it = allPoints.find(inputSequence[i]);
  //   Point* p_currentPoint;
    
  //   if(it == allPoints.end()){
  //     p_currentPoint = new Point(inputSequence[i]);
  //     allPoints.insert(map<long, Point*>::value_type(inputSequence[i], p_currentPoint));
  //   }else{
  //     p_currentPoint = allPoints[inputSequence[i]];  
  //   }

  //   p_currentPoint->connectTo(inputSequence[i+1], currentStatus);

  //   printParameters((*p_currentPoint));
  //   printStatus((*p_currentPoint));

  //   vector<double> newStatus = p_currentPoint->getOutputStatus();

  //   for(size_t j=0; j<Point::statusNumber; j++){
  //     currentStatus[j] = newStatus[j];
  //   }

  //   if(p_prevPoint != NULL){
  //     vector<double> inputStatusGradient = p_currentPoint->getInputStatusGradient();
  //     cout << "getting input status gradient:";
  //     for(int k=0; k<Point::statusNumber; k++){
  //       cout << " " << inputStatusGradient[k];
  //     }
  //     cout << endl;
  //     double tempGradient[Point::statusNumber];
  //     for(size_t k=0; k<Point::statusNumber; k++){
  //       tempGradient[i] = inputStatusGradient[i];
  //     }
  //     p_prevPoint->updateOutputParametersWithBP(tempGradient);
  //   }

  //   p_prevPoint = p_currentPoint;

  // }

  
  // int predictTime = 100;

  // Dictionary* dictionary = Dictionary::getInstance();
  // long predictID = dictionary->getID("I");
  // //predictID = 10;

  // vector<long> predictSequence;
  
  // map<long, Point*>::iterator it = allPoints.find(predictID);
  // Point* currentPoint = it->second;

  // cout << "Current Point ID:" << currentPoint->getID() << endl;

  // cout << "Predicting the sequence with the init ID: " << predictID << endl;

  // for(size_t i=0; i<predictTime; i++){
  //   //cout << "p:" << i << " ";
  //   long predictResult = currentPoint->predictNextPoint(predictStatus);
  //   //cout << "  " << predictResult;
  //   predictSequence.push_back(vector<long>::value_type( predictResult));

  //   vector<double> newStatus = currentPoint->getOutputStatus();
  //   predictID = predictResult;
  //   it = allPoints.find(predictID);
  //   if(it == allPoints.end()){
  //     cout << "Not in it!!!!!!!!!!!!!!!!";
  //     cout << " " << predictID;
  //   }else{
  //     currentPoint = it->second;
  //   }
     

  //   for(int j=0; j<Point::statusNumber; j++){
  //       predictStatus[j] = newStatus[j];
  //    }
    
  // }

  // cout << endl << "  end of prediction" << endl;

  // printSequence(predictSequence);


  return result;
}



int multiplePointTest(){
  int result = 0;

  // long inputSequence[] = {10, 20, 30, 30, 10, 40, 30, 20, 10, 30, 10, 20, 10, 20, 10, 20};
  // size_t inputNumber = sizeof(inputSequence)/sizeof(inputSequence[0]);

  // for(size_t i=0; i<inputNumber; i++){
  //   cout << " " << inputSequence[i];
  // }
  // cout << endl;

  // vector<double> currentStatus;
  // const int statusNumber = 10;

  // for(size_t i=0; i<statusNumber; i++){
  //   currentStatus.push_back(vector<double>::value_type(math::RandomFactory::getNext()));
  // }

  
  // map<long, Point> allPoints;
  // Point* p_prevPoint = NULL;

  // for(size_t i=0; i<inputNumber-1; i++){
  //   map<long, Point*>::iterator it = allPoints.find(inputSequence[i]);
  //   Point* p_currentPoint;
    
  //   if(it == allPoints.end()){
  //     p_currentPoint = new Point(inputSequence[i]);
  //     allPoints.insert(map<long, Point*>::value_type(inputSequence[i], p_currentPoint));
  //   }else{
  //     p_currentPoint = allPoints[inputSequence[i]];  
  //   }

  //   p_currentPoint->connectTo(inputSequence[i+1], currentStatus);

  //   printParameters((*p_currentPoint));
  //   printStatus((*p_currentPoint));

  //   vector<double> newStatus = p_currentPoint->getOutputStatus();

  //   for(size_t j=0; j<Point::statusNumber; j++){
  //     currentStatus[j] = newStatus[j];
  //   }

  //   if(p_prevPoint != NULL){
  //     vector<double> inputStatusGradient = p_currentPoint->getInputStatusGradient();
  //     cout << "getting input status gradient:";
  //     for(int k=0; k<Point::statusNumber; k++){
  //       cout << " " << inputStatusGradient[k];
  //     }
  //     cout << endl;
  //     double tempGradient[Point::statusNumber];
  //     for(size_t k=0; k<Point::statusNumber; k++){
  //       tempGradient[k] = inputStatusGradient[k];
  //     }
  //     p_prevPoint->updateOutputParametersWithBP(tempGradient);
  //   }

  //   p_prevPoint = p_currentPoint;

  // }

  // double predictStatus[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

  // int predictTime = 20;

  // long predictID = 10;

  // map<long, Point*>::iterator it = allPoints.find(predictID);
  // Point* currentPoint = it->second;

  // cout << "Predicting the sequence with the init ID: " << predictID << endl;

  // for(int i=0; i<predictTime; i++){
    
  //   long predictResult = currentPoint->predictNextPoint(predictStatus);
  //   cout << "  " << predictResult;

  //   vector<double> newStatus = currentPoint->getOutputStatus();
  //   predictID = predictResult;
  //   it = allPoints.find(predictID);
  //   currentPoint = it->second;

  //   for(int j=0; j<Point::statusNumber; j++){
  //     predictStatus[j] = newStatus[j];
  //   }
    
  // }

  // cout << endl << "  end of prediction" << endl;

  


  return result;
}

int pointManagerTest(){
  int result = 0;
  cout << "Now we can start our test" << endl;

  //string inputString = "测试的中文字";
  //string inputString = "Better Speaking is all about how you can become a fluent";
  
  // string inputString = "On the 24th of February, 1815, the look-out at Notre-Dame de la Garde signalled the three-master, the Pharaon from Smyrna, Trieste, and Naples. ";
  // inputString += "As usual, a pilot put off immediately, and rounding the Chateau d'If, got on board the vessel between Cape Morgion and Rion island.";

  // inputString += "Immediately, and according to custom, the ramparts of Fort Saint-Jean were covered with spectators; it is always an event at Marseilles for a ship to come into port, especially when this ship, like the Pharaon, has been built, rigged, and laden at the old Phocee docks, and belongs to an owner of the city. ";
  // inputString += "The ship drew on and had safely passed the strait, which some volcanic shock has made between the Calasareigne and Jaros islands; had doubled Pomegue, and approached the harbor under topsails, jib, and spanker, but so slowly and sedately that the idlers, with that instinct which is the forerunner of evil, asked one another what misfortune could have happened on board. However, those experienced in navigation saw plainly that if any accident had occurred, it was not to the vessel herself, for she bore down with all the evidence of being skilfully handled, the anchor a-cockbill, the jib-boom guys already eased off, and standing by the side of the pilot, who was steering the Pharaon towards the narrow entrance of the inner port, was a young man, who, with activity and vigilant eye, watched every motion of the ship, and repeated each direction of the pilot. ";
  // inputString += "The vague disquietude which prevailed among the spectators had so much affected one of the crowd that he did not await the arrival of the vessel in harbor, but jumping into a small skiff, desired to be pulled alongside the Pharaon, which he reached as she rounded into La Reserve basin. ";
  
  // inputString += "\"When the young man on board saw this person approach, he left his station by the pilot, and, hat in hand, leaned over the ship\'s bulwarks. ";
  // inputString += "He was a fine, tall, slim young fellow of eighteen or twenty, with black eyes, and hair as dark as a raven's wing; and his whole appearance bespoke that calmness and resolution peculiar to men accustomed from their cradle to contend with danger. ";
  // inputString += "\"Ah, is it you, Dantes?\" cried the man in the skiff. \"What's the matter? and why have you such an air of sadness aboard?\" ";
  // inputString += "\"A great misfortune, M. Morrel,\" replied the young man, -- \"a great misfortune, for me especially! Off Civita Vecchia we lost our brave Captain Leclere.\" ";
  // inputString += "\"And the cargo?\" inquired the owner, eagerly. ";
  // inputString += "\"Is all safe, M. Morrel; and I think you will be satisfied on that head. But poor Captain Leclere -- \" ";
  // inputString += "\"What happened to him?\" asked the owner, with an air of considerable resignation. \"What happened to the worthy captain?\" ";
  // inputString += "\"He died.\" ";
  // inputString += "\"Fell into the sea?\" ";
  // inputString += "\"No, sir, he died of brain-fever in dreadful agony.\" Then turning to the crew, he said, \"Bear a hand there, to take in sail!\" ";
  // inputString += "All hands obeyed, and at once the eight or ten seamen who composed the crew, sprang to their respective stations at the spanker brails and outhaul, topsail sheets and halyards, the jib downhaul, and the topsail clewlines and buntlines. The young sailor gave a look to see that his orders were promptly and accurately obeyed, and then turned again to the owner. ";
  // inputString += "\"And how did this misfortune occur?\" inquired the latter, resuming the interrupted conversation. ";
  // inputString += "\"Alas, sir, in the most unexpected manner. After a long talk with the harbor-master, Captain Leclere left Naples greatly disturbed in mind. In twenty-four hours he was attacked by a fever, and died three days afterwards. We performed the usual burial service, and he is at his rest, sewn up in his hammock with a thirty-six pound shot at his head and his heels, off El Giglio island. We bring to his widow his sword and cross of honor. It was worth while, truly,\" added the young man with a melancholy smile, \"to make war against the English for ten years, and to die in his bed at last, like everybody else.\" ";
  // inputString += "\"Why, you see, Edmond,\" replied the owner, who appeared more comforted at every moment, \"we are all mortal, and the old must make way for the young. If not, why, there would be no promotion; and since you assure me that the cargo -- \" ";
  // inputString += "\"Is all safe and sound, M. Morrel, take my word for it; and I advise you not to take 25,000 francs for the profits of the voyage.\" ";
  // inputString += "Then, as they were just passing the Round Tower, the young man shouted: \"Stand by there to lower the topsails and jib; brail up the spanker!\" ";
  // inputString += "The order was executed as promptly as it would have been on board a man-of-war. ";
  // inputString += "\"Let go -- and clue up!\" At this last command all the sails were lowered, and the vessel moved almost imperceptibly onwards.";

  // inputString += "learners of English from around the world and also from someone who specialises in teaching speaking, trainer Richard Hallows. Better Speaking is presented by Callum Robertson. ";
  // inputString += "Callum and Richard hear a clip from Korean football manager Pak Han Suk, and discuss ways you can improve your fluency in English. ";
  // inputString += "Callum and Richard hear a clip from the former Secretary-General of the United Nations, Kofi Annan. They also discuss different ways you can practise and improve your English pronunciation. ";
  // inputString += ", confident speaker of English. In the programmes we hear from ";
  // inputString += "learners of English from around the world and also from someone who specialises in teaching speaking, trainer Richard Hallows. Better Speaking is presented by Callum Robertson. ";
  // inputString += "Callum and Richard hear a clip from Korean football manager Pak Han Suk, and discuss ways you can improve your fluency in English. ";
  // inputString += "Callum and Richard hear a clip from the former Secretary-General of the United Nations, Kofi Annan. They also discuss different ways you can practise and improve your English pronunciation. ";
  // inputString += ", confident speaker of English. In the programmes we hear from ";
  // inputString += "learners of English from around the world and also from someone who specialises in teaching speaking, trainer Richard Hallows. Better Speaking is presented by Callum Robertson. ";
  // inputString += "Callum and Richard hear a clip from Korean football manager Pak Han Suk, and discuss ways you can improve your fluency in English. ";
  // inputString += "Callum and Richard hear a clip from the former Secretary-General of the United Nations, Kofi Annan. They also discuss different ways you can practise and improve your English pronunciation. ";
  

  

  
  PointManager pointManager;

  int totalIterTime=1;
  int totalLineNumber=2000;

  for(int iterTime=0; iterTime<totalIterTime; iterTime++){
    cout << "iterating: " << iterTime << endl;

    std::ifstream fin("./sampledata/mount_of_cristor.txt", std::ios::in); 

    if(!fin){
      cout << "failed to open the file" << endl;
    }else{
      cout << "file opened!" << endl;
    }

    char line[10240]={0};

    int lineNumber=0;
    
    while(fin.getline(line, sizeof(line))){
      //cout << ".";
      string fileString(line);
      //cout << fileString;
      //cout << endl;
      vector<string> trainingString = splitToCharacters(fileString);
      for (int i=0; i<trainingString.size(); i++){
        //cout << "inserting: " << trainingString[i] << "----------------" << endl;
        pointManager.insertString(trainingString[i]);
      }

      lineNumber++;
      if(lineNumber > totalLineNumber){
        break;
      } 
    }

    cout << endl;
    fin.clear();
    fin.close();
    

  }

  
  cout << "successfully insert all the strings -------------------------" << endl;

  string startString = "S";
  vector <string> predictResult = pointManager.predictString(startString, 1000);

  cout << "predict result:" << endl;
  cout << startString << " "; 
  for(int i=0; i<predictResult.size(); i++){
    cout << predictResult[i] << " ";
  }
  cout << endl;

  return result;
}

int fileTest(){
  int result = 0;

  std::ifstream fin("./sampledata/mount_of_cristor.txt", std::ios::in); 

  if(!fin){
    cout << "failed to open the file" << endl;
  }else{
    cout << "file opened!" << endl;
  }

  char line[10240]={0};

  int i=0;
  while(fin.getline(line, sizeof(line))){
  
    string tempString(line);
    cout << tempString;
    cout << endl;
  
    i++;
    if(i>20){
      break;
    } 
  }

  return result;
}

int randomTest(){
  int result = 0;

    for(int i=0; i<1000; i++){
      double x;
      double x1;
      double x2;
      srand((unsigned)time(0)); //srand(3)
      x1 = rand();
      
      x2 = rand();
      x = x1/x2;
      cout<<x<<endl;
    }
  return result;  
}

int randomTest2(){
  std::default_random_engine random(time(NULL));  
    std::uniform_int_distribution<int> dis1(0, 100);  
   std::uniform_real_distribution<double> dis2(-1.0, 1.0);  
   
    for(int i = 0; i < 10; ++i)  
        cout<<dis1(random)<<' ';  
    cout<<endl;  
   
    for(int i = 0; i < 10; ++i)  
        cout<<dis2(random)<<' ';  
    cout<<endl;  
   
    return 0;  
}

int printParameters(Point testingPoint){
  int result = 0;

  cout << "print input parameters: " << endl;
  vector< vector<double> > inputParameters = testingPoint.getInputParameters();

  for(int i=0; i<inputParameters.size(); i++){
    for(int j=0; j<inputParameters[i].size(); j++){
      cout << inputParameters[i][j] << ", ";
    }
    cout << endl;
  }

  cout << "print output parameters: " << endl;
 vector< vector<double> > outputParameters = testingPoint.getOutputParameters();

  for(int i=0; i<outputParameters.size(); i++){
    for(int j=0; j<outputParameters[i].size(); j++){
      cout << outputParameters[i][j] << ", ";
    }
    cout << endl;
  }

  return result;
}

int printStatus(Point testingPoint){
  int result = 0;

  vector<double> outputStatus = testingPoint.getOutputStatus();

  cout << "output status: ";
    for(int i=0; i<outputStatus.size(); i++){
      cout << outputStatus[i] << ", ";
    }
  cout << endl;

  return result;
}

vector<long> getInputSequence(){
  string inputString = "Something that make me can be used to train the sentence, hope that it works!";
  inputString = inputString + "I am a boy, hope that it is a new sample.";
  inputString = inputString + "Some new words, new sample set has more training sample.";
  inputString = inputString + "I have an idea, hope that it can provide more training sample.";
  inputString = inputString + "I have a pen, hope that it can provide more training sample.";
  inputString = inputString + "I can go to school, hope that it can provide more training sample.";
  inputString = inputString + "Some new words, hope that it can provide more training sample.";


  vector<string> splitResult = split(inputString, " ");

  vector<long> result;
  
  Dictionary* dictionary = Dictionary::getInstance();

  for(size_t i=0; i<splitResult.size(); i++){
    result.push_back(vector<long>::value_type(dictionary->addValue(splitResult[i])));
  }

  return result;
}


int printSequence(vector<long> sequence){
  Dictionary* dictionary = Dictionary::getInstance();

  cout << "printing sequence: " << endl;
  for(size_t i=0; i<sequence.size(); i++){
    string value = dictionary->getValue(sequence[i]);
    cout << " " << value;
  }
  cout << endl;
  return 0;
}




vector<string> split(const string &s, const string &seperator){
  vector<string> result;
  typedef string::size_type string_size;
  string_size i = 0;

  while(i != s.size()){
    //
    int flag = 0;
    while(i != s.size() && flag == 0){
      flag = 1;
      for(string_size x = 0; x < seperator.size(); ++x)
        if(s[i] == seperator[x]){
        ++i;
        flag = 0;
        break;
        }
    }
    
    //
    flag = 0;
    string_size j = i;
    while(j != s.size() && flag == 0){
      for(string_size x = 0; x < seperator.size(); ++x)
        if(s[j] == seperator[x]){
          flag = 1;
          break;
        }
      if(flag == 0) 
        ++j;
    }
    if(i != j){
      result.push_back(s.substr(i, j-i));
      i = j;
    }
  }
  return result;
}


vector<string> splitToCharacters(const string &s){
  vector<string> result;
  typedef string::size_type string_size;
  string_size i = 0;

  while(i != s.size()){
    //
    result.push_back(vector<string>::value_type(s.substr(i, 1)));
    
    i++;
  }
  return result;
}


