#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <iostream>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"
namespace sdds
{
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station
    {
        std::deque<CustomerOrder> m_orders;
        Workstation* m_pNextStation{};
    public:
        Workstation(const std::string str);
        //No copying and moving
        Workstation(const Workstation& other) = delete;
        Workstation& operator=(const Workstation& other) = delete;
        Workstation(Workstation&& other) = delete;
        Workstation& operator=(Workstation&& other) = delete;

        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        Workstation& operator+=(CustomerOrder&& newOrder);
        void setNextStation(Workstation* station = nullptr);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
    };

}

#endif // !SDDS_WORKSTATION_H



