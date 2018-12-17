#include <iostream>
#include <queue>
#include <iomanip>
#include <fstream>
using namespace std;

struct EventList {
   // other stuff here
   void fill(istream& is);
   void simulate();
};

 struct Guests
 {
     /* data */
    string name;
    int age;
    Guests(string name, int age) {
        this->name = name;
        this->age = age;
    }
 };

struct GuestCompare {
    bool operator()(const Guests& s1, const Guests& s2) {
        return s1.age > s2.age;
    }
};



	//Empty Bank Queue












/**
 * The usual main function
 */
int main(int argc, char** argv)
{
   EventList eventList;

   // command-line parameter munging
   // also fills the event list with the input data
   char* progname = argv[0];            // simplify msgs a bit
   switch (argc) {
   case 1:
      eventList.fill(cin);
      break;
   case 2: {
      ifstream ifs(argv[1]);
      if (!ifs) {
         cerr << progname << ": couldn't open " << argv[1] << endl;
         return 1;
      }
      eventList.fill(ifs);
      break;
   }
   default:
      cerr << "Usage: " << progname << " [datafile]\n";
      return 2;
   }

   eventList.simulate();
}

void EventList::fill(istream& is)
{
   cout << "EventList::fill was called\n";
}

void EventList::simulate()
{
   cout << "EventList::simulate was called\n";
}

