/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    simulation.cpp
    Definitions for the Simulation Class. The Simulation Class manipulates
    the Events in priority_queue.
*/

#include "simulation.h"

//Destructor, deletes all objects in the event we have some left in our priority queue
Simulation::~Simulation()
{
    while(!eventQueue.empty())
    {
        Event *nextEvent = eventQueue.top();
        eventQueue.pop();
        delete nextEvent;
    }
}

// Execute events until event queue is empty
void Simulation::run()
{
    HelpFunctions::clrScreen();
    while(!eventQueue.empty())
    {
        nextEvent();
    }
}

// Schedule an Event
void Simulation::scheduleEvent (Event *newEvent) {
    eventQueue.push (newEvent);
}

// Processes one event at a time. Used in both run() and runNextInterval()
bool Simulation::nextEvent()
{
    if(eventQueue.empty())
    {
        return false;
    }
    Event *nextEvent = eventQueue.top();
    eventQueue.pop();
    currentTime = nextEvent->getTime();
    nextEvent->processEvent();
    delete nextEvent;
    return true;
}

// Process the queue until we meet currentTime+interval
bool Simulation::runNextInterval(int pmInterval)
{
    HelpFunctions::clrScreen();
    if(eventQueue.empty())
    {
        return false;
    }

    unsigned int tmpTime=currentTime+pmInterval;
    while(eventQueue.top()->getTime() < tmpTime)
    {
        if(nextEvent() == false)
        {
            return false;
        }
    }
    currentTime=tmpTime;
    return true;
}
