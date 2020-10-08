/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    event.cpp
    Definition for the Event heritage, EventComparison compares 2 events,
    every other class-event is derived from the base class Event
*/

#include "event.h"
#include "company.h"
#include "simulation.h"


//Creates ReadyEvent if assembly of train is successful, else a new AssemblyEvent after 10min
void AssemblyEvent::processEvent()
{
    //Check so we don't put new events past the end time
    if(theSim->getTime()+20 > theSim->getEndTime())
    {
            return;
    }

    if(theCompany->assembly(trainNumber))
    {
        Event *e = new ReadyEvent(theSim, theCompany, theSim->getTime()+20, trainNumber);
        theSim->scheduleEvent(e);
    }
    else
    {
        Event *e = new AssemblyEvent(theSim, theCompany, theSim->getTime()+10, trainNumber);
        theSim->scheduleEvent(e);
    }
}

//ReadyEvent, creates a new RunningEvent in 10min
void ReadyEvent::processEvent()
{
    if(theSim->getTime()+10 > theSim->getEndTime())
    {
            return;
    }
    theCompany->changeToReady(trainNumber);
    Event *e = new RunningEvent(theSim, theCompany, theSim->getTime()+10, trainNumber);
    theSim->scheduleEvent(e);
    theCompany->printEvent(trainNumber, "is now ready, departing at " + HelpFunctions::IntToTime(theSim->getTime()+10));
}

//RunningEvent, creates a new ArrivedEvent timed based on when the train will arrive to the station
void RunningEvent::processEvent()
{
    int arrivalTime=theCompany->running(trainNumber);
    Event *e = new ArrivedEvent(theSim, theCompany, arrivalTime, trainNumber);
    theSim->scheduleEvent(e);
}

//ArrivedEvent, creates a FinishedEvent after 20min
void ArrivedEvent::processEvent()
{
    theCompany->arrived(trainNumber);
    Event *e = new FinishedEvent(theSim, theCompany, theSim->getTime()+20, trainNumber);
    theSim->scheduleEvent(e);
}

//Disassembles all the vehicles and returns them to the destination train station
void FinishedEvent::processEvent()
{
    theCompany->disassemble(trainNumber);
}
