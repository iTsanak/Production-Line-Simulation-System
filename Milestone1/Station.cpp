// Date of completion: 2023-11-7
#include <sstream>
#include "Station.h"


namespace sdds
{
    size_t Station::m_widthField = 0;
    size_t Station::id_generator = 0;

    Station::Station(const std::string& recordLine)  
    {
        Utilities util;
        bool more = true;
        size_t next_pos = 0;

        m_name = util.extractToken(recordLine, next_pos, more);
        m_nextSerialNumber = stoi(util.extractToken(recordLine, next_pos, more));
        m_numStockItems = stoi(util.extractToken(recordLine, next_pos, more));
       

        if (Station::m_widthField < util.getFieldWidth()) {
            Station::m_widthField = util.getFieldWidth();
        }
        m_description = util.extractToken(recordLine, next_pos, more);
        m_id = ++id_generator;
    }

    const std::string& Station::getItemName() const
    {
        return m_name;
    }

    size_t Station::getNextSerialNumber()
    {
        return m_nextSerialNumber++;
    }

    size_t Station::getQuantity() const
    {
        return m_numStockItems;
    }

    void Station::updateQuantity()
    {
        if (m_numStockItems > 0)
        {
            m_numStockItems--;
        }
    }

    void Station::display(std::ostream& os, bool full) const
    {
        if (full == false)
        {
            os << std::setw(3) << std::setfill('0') << m_id << std::setfill(' ') <<  " | " << std::setw(m_widthField) << std::left  << m_name << "| " << std::setw(6) << std::right << std::setfill('0') << m_nextSerialNumber << " | " << std::endl;

        }
        else
        {
            os << std::setw(3) << std::right << std::setfill('0') << m_id << " | " << std::setw(m_widthField) << std::left << std::setfill(' ') << m_name << "| " << std::setw(6) << std::right << std::setfill('0') << m_nextSerialNumber << " | " << std::setw(4) << std::right << std::setfill(' ') << m_numStockItems << " | "  <<  m_description << std::endl;
        }
    }

}
