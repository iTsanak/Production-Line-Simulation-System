// Name: IRAKLIS TSANACHTSIDIS
// Seneca Student ID: 122226228
// Seneca email: itsanachtsidis@myseneca.ca
// Date of completion: 2023-11-29
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_UTILITIES
#define SDDS_UTILITIES
#include <iostream>
#include <string>
#include "Station.h"
namespace sdds
{
    class Utilities
    {  
    private:
        size_t m_widthField{ 1 };
        
    public:
        static char m_delimiter;
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
        static void setDelimiter(char newDelimiter) {
            m_delimiter = newDelimiter;
        }
        static char getDelimeter()
        {
            return m_delimiter;
        }
        

    };
  
}
#endif 

