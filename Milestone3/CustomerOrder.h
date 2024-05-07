// Name: IRAKLIS TSANACHTSIDIS
// Seneca Student ID: 122226228
// Seneca email: itsanachtsidis@myseneca.ca
// Date of completion: 2023-11-29
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <iostream>
#include "Utilities.h"
namespace sdds
{
    struct Item
    {
        std::string m_itemName;
        size_t m_serialNumber{ 0 };
        bool m_isFilled{ false };

        Item(const std::string& src) : m_itemName(src) {};
    };

    class CustomerOrder
    {
        std::string m_name{};
        std::string m_product{};
        size_t m_cntItem{};
        Item** m_lstItem{};
        
    public:
        static size_t m_widthField;
        CustomerOrder() = default;
        CustomerOrder(const std::string str);
        CustomerOrder(const CustomerOrder& other);
        CustomerOrder& operator=(const CustomerOrder& other) = delete;
        CustomerOrder(CustomerOrder&& other) noexcept;
        CustomerOrder& operator=(CustomerOrder&&) noexcept;
        ~CustomerOrder();

        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
    };
}
#endif // !SDDS_CUSTOMERORDER_H



