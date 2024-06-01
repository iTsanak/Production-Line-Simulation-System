// Name: IRAKLIS TSANACHTSIDIS
// Seneca Student ID: 122226228
// Seneca email: itsanachtsidis@myseneca.ca
// Date of completion: 2023-11-29
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Workstation.h"

namespace sdds
{
    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;
    Workstation::Workstation(const std::string str) : Station(str) {}

    void Workstation::fill(std::ostream& os)
    {
        if (m_orders.empty() == false)
        {
            if (m_orders.size())
            {
                m_orders.front().fillItem(*this, os);
            }
        }
    }

    bool Workstation::attemptToMoveOrder() {
        bool result = false;

        if (!m_orders.empty()) {
            CustomerOrder& currentOrder = m_orders.front();

            if (currentOrder.isItemFilled(getItemName()) || getQuantity() == 0) {
                if (m_pNextStation) {
                    *m_pNextStation += std::move(currentOrder);                 
                }
                else {
                    if (currentOrder.isOrderFilled()) {
                        g_completed.push_back(std::move(currentOrder));
                    }
                    else {
                        g_incomplete.push_back(std::move(currentOrder));
                    }
                }
                result = true;
                m_orders.pop_front();
            }
        }

        return result;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
    {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }

    void Workstation::setNextStation(Workstation* station)
    {
        
            m_pNextStation = station;
        
    }

    Workstation* Workstation::getNextStation() const
    {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream& os) const
    {
        if (this->m_pNextStation)
        {
            os << this->getItemName() << " --> " << this->m_pNextStation->getItemName() << std::endl;
        }
        else
        {
            os << this->getItemName() << " --> End of Line" << std::endl;
        }
    }



    


}
