#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <iomanip>
#include "Utilities.h" 

namespace sdds
{
    class Station
    {
        int m_id{};
        std::string m_name{};
        std::string m_description{};
        size_t m_nextSerialNumber{};
        size_t m_numStockItems{};
    public:
        static size_t m_widthField; 
        static size_t id_generator; 
        Station(const std::string& recordLine);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
    
}
#endif // !SDDS_STATION_H


