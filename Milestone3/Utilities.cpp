// Name: IRAKLIS TSANACHTSIDIS
// Seneca Student ID: 122226228
// Seneca email: itsanachtsidis@myseneca.ca
// Date of completion: 2023-11-29
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Utilities.h"


namespace sdds
{
    char Utilities::m_delimiter = '\0';

    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }
    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }
    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
    {
        size_t start = next_pos;
        std::string token;

        if (str[start] == m_delimiter)
        {
            more = false;
            throw std::exception();
            
        }    
        else {
            token = str.substr(start, str.length());
            token = token.substr(0, token.find_first_of(m_delimiter));
            next_pos += (token.length() + 1);
            more = next_pos >= str.length() ? false : true;
            if (token.length() > m_widthField) {
                m_widthField = token.length();
            }
        }       
        token.erase(0, token.find_first_not_of(' '));
        token.erase(token.find_last_not_of(' ') + 1);
        return token;
    }
    
 

    
    
}
