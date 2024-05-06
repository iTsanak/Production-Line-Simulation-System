// Date of completion: 2023-11-21
#include "CustomerOrder.h"

namespace sdds
{
     size_t CustomerOrder::m_widthField = 0;
    CustomerOrder::CustomerOrder(const std::string str)
    {
        Utilities util;
        bool more = true;
        size_t next_pos = 0;

        m_name = util.extractToken(str, next_pos, more);
        m_product = util.extractToken(str, next_pos, more);
        auto first_pos = next_pos;

        while (more)
        {
            util.extractToken(str, next_pos, more);
            m_cntItem++;
        }
        more = true;
        m_lstItem = new Item*[m_cntItem];

        for (size_t i = 0; i < m_cntItem; i++)
        {
            m_lstItem[i] = new Item(util.extractToken(str, first_pos, more));
        }


        if (m_widthField < util.getFieldWidth())
        {
           m_widthField = util.getFieldWidth();
        }

    }

    CustomerOrder::CustomerOrder(const CustomerOrder& other)
    {
        throw std::string("Error: Can't call copy constructor");
    }

    CustomerOrder::CustomerOrder( CustomerOrder&& other) noexcept
    {
        *this = std::move(other);
    }


    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept
    {
        if (this != &other)
        {
            for (size_t i = 0; i < m_cntItem; i++)
            {
                delete m_lstItem[i];
            }
            if (m_lstItem != nullptr)
            {
                delete[] m_lstItem;
            }

            m_name = other.m_name;
            m_product = other.m_product;
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;
            other.m_name = {};
            other.m_product = {};
            other.m_cntItem = 0;
            other.m_lstItem = nullptr;
        }
        return *this;
    }

    bool CustomerOrder::isOrderFilled() const
    {
        bool filled = true;
        for (size_t i = 0; i < m_cntItem && filled; i++)
        {
            if (m_lstItem[i]->m_isFilled == false )
            {
                filled = false;
            }
        }
        return  filled;
    }

    CustomerOrder::~CustomerOrder()
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }
        
    bool CustomerOrder::isItemFilled(const std::string& itemName) const
    {
        bool result = true;
        for (size_t i = 0; i < m_cntItem; i++)
        {
            
            if (m_lstItem[i]->m_itemName == itemName)
            {
                result = m_lstItem[i]->m_isFilled;
            }
        }
        return result;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os)
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (m_lstItem[i]->m_itemName == station.getItemName())
            {
                if (station.getQuantity() > 0 && m_lstItem[i]->m_isFilled == false)
                {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                        break; 
                }
                else if(station.getQuantity() == 0)
                {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
                
            }
        }
    }
    ////////////////////////////////////////////////REMEMBER HERE 2
    void CustomerOrder::display(std::ostream& os) const
    {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++)
        {
            os << "[" << std::setw(6) << std::right << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] " << std::setw(CustomerOrder::m_widthField - 2) 
                << std::left << std::setfill(' ') << m_lstItem[i]->m_itemName << " - ";
            os << (m_lstItem[i]->m_isFilled == true ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }




}
