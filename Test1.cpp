#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <cstdlib>
#include <vector>
using namespace std;

struct EventList {
   // other stuff here
   void fill(istream& is);
   void simulate();
};

struct Event
{
    char type;
    int time;
    int length;
    bool operator>(Event* x)
    {
        return (time<x->time);
    }
    bool operator<(Event* x)
    {
        return (time>x->time);
    }
    Event(int arrival, int serviceLength, char letter)
    {
        time = arrival;
        length = serviceLength;
        type = letter;
    }
    Event(int arrival, char letter)
    {
        time = arrival;
        type = letter;
    }
    Event(int arrival, int serviceLength)
    {
        time = arrival;
        length = serviceLength;
        type = 'A';
    }
    Event(int arrival)
    {
        time = arrival;
        type = 'A';
    }
    Event()
    {
        type = 'A';
    }
    };

    struct Compare : public std::binary_function<Event*, Event*, bool>
    {
    bool operator() (const Event* x, const Event* y)
    {
        return ((x->time)>(y->time));
    }
    };

void simulate(priority_queue<Event*, vector<Event*>, Compare> &eventList);
void processArrival(Event* newEvent, priority_queue<Event*, vector<Event*>, Compare> &eventList, queue<Event*> &bankQueue, bool &teller, int &currentTime, int &waitTime);
void processDeparture(Event* newEvent, priority_queue<Event*, vector<Event*>, Compare> &eventList, queue<Event*> &bankQueue, bool &teller, int &currentTime, int &waitTime);




int main(int argc, char** argv)
{
   EventList eventList1;

   // command-line parameter munging
   // also fills the event list with the input data
   char* progname = argv[0];            // simplify msgs a bit
   switch (argc) {
   case 1:
      eventList1.fill(cin);
      break;
   case 2: {
      ifstream ifs(argv[1]);
      if (!ifs) {
         cerr << progname << ": couldn't open " << argv[1] << endl;
         return 1;
      }
      eventList1.fill(ifs);
      break;
   }
   default:
      cerr << "Usage: " << progname << " [datafile]\n";
      return 2;
   }

   eventList1.simulate();


    int arrivalTime, serviceLength, counter = 0, previousTime;
   /* ifstream file;
    priority_queue<Event*, vector<Event*>, Compare> eventList;

    file.open("data-0.txt");

    if(!file)
    {
        cout << "Could not open the input file" << endl;
        exit(0);
    }
    */

    while (eventList1 >> arrivalTime)
    {
    counter++;

       if(!eventList1.empty())
       {
          if (arrivalTime<previousTime)
          {
          cout << "Customer #" << counter << " out of order (time= " << arrivalTime << " previous time= " << previousTime << ")" << endl;
          exit(0);
          }
        }

       eventList1 >> serviceLength;
       eventList.push(new Event(arrivalTime, serviceLength));
       previousTime = arrivalTime;
    }
simulate(eventList);
//file.close();

   return 0;}

void simulate(priority_queue<Event*, vector<Event*>, Compare> &eventList)
{
    int currentTime, tempTime, tempLength, counter = 0, waitTime,
        originalArrivalTimes[eventList.size()];
    float totalWaitTime = 0;
    char tempType;
    queue<Event*> bankQueue;
    bool teller= true;

    if(!eventList.empty())
    {
        currentTime = eventList.top()->time;
    }
    else{
        cout << "Event list is empty" << endl;
    }

    while(!eventList.empty())
    {
        tempTime = eventList.top()->time;
        tempLength = eventList.top()->length;
        tempType = eventList.top()->type;
        waitTime = 0;
        Event* newEvent = new Event(tempTime,tempLength, tempType);
        currentTime = eventList.top()->time;

        if(newEvent->type=='A')
        {
            processArrival(newEvent, eventList, bankQueue, teller, currentTime, waitTime);
            totalWaitTime += waitTime;
            originalArrivalTimes[counter] = newEvent->time;
            counter++;
        }
        else
        {
            processDeparture(newEvent, eventList, bankQueue, teller, currentTime, waitTime);
            totalWaitTime += waitTime;
        }
         //processes the arrivals first
        delete newEvent;
       }

            cout << "Total Number of People Processed: " << counter << endl;
            totalWaitTime /= counter;
            cout << "Average amount of time spent waiting: " << totalWaitTime << endl;
            return;
}

void processArrival(Event* arrivalEvent, priority_queue<Event*, vector<Event*>, Compare> &eventList, queue<Event*> &bankQueue, bool &teller, int &currentTime, int &waitTime)
{
    int departureTime = currentTime + (arrivalEvent->length);
    cout << "Processing an arrival at time " << currentTime << " and length " << arrivalEvent->length << endl;
    eventList.pop();

    if(bankQueue.empty() && teller)
    {
        eventList.push(new Event(departureTime, 'D'));
        teller = 0;
    }
    else
    {
        int temp = arrivalEvent->time, tempLength = arrivalEvent->length, tempType = arrivalEvent->type;
        bankQueue.push(new Event(temp, tempLength, tempType));
    }
}
void processDeparture(Event* departureEvent, priority_queue<Event*, vector<Event*>, Compare> &eventList, queue<Event*> &bankQueue, bool &teller, int &currentTime, int &waitTime)
{
    int departureTime;

    cout << "Processing a departure at time " << currentTime << endl;
    eventList.pop();

    if(!bankQueue.empty())
    {
        //Transaction
        Event* customer = bankQueue.front();
        bankQueue.pop();
        waitTime = currentTime - (customer->time);
        departureTime = currentTime + customer->length;
        eventList.push(new Event(departureTime, 'D'));
    }
    else
    {
        teller= true;
    }
}


