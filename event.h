/*
    Morgan Vallin, mova1701, mova1701@student.miun.se
    2018-06-11, Projektarbete, Objektorienterad programmering i C++
    event.h
    Declaration for the Event heritage, EventComparison compares 2 events,
    every other class-event is derived from the base class Event
*/

#ifndef EVENT_H
#define EVENT_H

class Simulation;
class Company;

class Event {
public:
    // Constructor requires time of event
    Event (unsigned int t, unsigned int tNr) : time(t), trainNumber(tNr) { }

    virtual ~Event() { }

    // Process event by invoking this method
    virtual void processEvent()=0;

    // Get time for this event
    unsigned int getTime() const {return time;}
    unsigned int getTrainNumber() const {return trainNumber;}

protected:
    // Time for this event
    unsigned int time;
    unsigned int trainNumber;
};

// Used to compare to Events with respect to time
class EventComparison {
public:
    bool operator() (Event * left, Event * right) {
        return left->getTime() > right->getTime();
    }
};

//--- Derived Event-classes ----------------------------------------------------

class AssemblyEvent : public Event {
public:
    AssemblyEvent (Simulation *sim, Company *comp, int pmTime, int pmTrainNumber)
    : Event(pmTime, pmTrainNumber),theSim(sim),theCompany(comp) { }

    virtual void processEvent();

protected:
    Simulation *theSim;
    Company *theCompany;
};


class AssembledEvent : public Event {
public:
    AssembledEvent (Simulation *sim, Company *comp, int pmTime, int pmTrainNumber)
    : Event(pmTime, pmTrainNumber),theSim(sim),theCompany(comp) { }

    virtual void processEvent();

protected:
    Simulation *theSim;
    Company *theCompany;
};


class ReadyEvent : public Event {
public:
    ReadyEvent (Simulation *sim, Company *comp, int pmTime, int pmTrainNumber)
    : Event(pmTime, pmTrainNumber),theSim(sim),theCompany(comp) { }

    virtual void processEvent();

protected:
    Simulation *theSim;
    Company *theCompany;
};


class RunningEvent : public Event {
public:
    RunningEvent (Simulation *sim, Company *comp, int pmTime, int pmTrainNumber)
    : Event(pmTime, pmTrainNumber),theSim(sim),theCompany(comp) { }

    virtual void processEvent();

protected:
    Simulation *theSim;
    Company *theCompany;
};


class ArrivedEvent : public Event {
public:
    ArrivedEvent (Simulation *sim, Company *comp, int pmTime, int pmTrainNumber)
    : Event(pmTime, pmTrainNumber),theSim(sim),theCompany(comp) { }

    virtual void processEvent();

protected:
    Simulation *theSim;
    Company *theCompany;
};


class FinishedEvent : public Event {
public:
    FinishedEvent (Simulation *sim, Company *comp, int pmTime, int pmTrainNumber)
    : Event(pmTime, pmTrainNumber),theSim(sim),theCompany(comp) { }

    virtual void processEvent();

protected:
    Simulation *theSim;
    Company *theCompany;
};

#endif

