// Name: IRAKLIS TSANACHTSIDIS
// Seneca Student ID: 122226228
// Seneca email: itsanachtsidis@myseneca.ca
// Date of completion: 2023-11-29
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <fstream>
#include <string>
#include <algorithm>
#include "LineManager.h"
namespace sdds
{
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    {
        if (!file.empty())
        {
            std::ifstream newFile(file);
            if (!newFile)
            {
                throw std::string("Error: File cannot be opened");
            }

            std::string line{};
            while (std::getline(newFile, line))
            {
                std::string firstWorkStation{}, nextWorkStation{};
                firstWorkStation = line.substr(0, line.find_first_of("|"));
                nextWorkStation = line.erase(0,firstWorkStation.size() + 1);

                auto WStation = std::find_if(stations.begin(), stations.end(),[&](Workstation* ws) 
                    { return ws->getItemName() == firstWorkStation; });

                m_activeLine.push_back(*WStation);

                if (!nextWorkStation.empty())
                {
                    auto nextWs = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws1)
                        {
                            return ws1->getItemName() == nextWorkStation;
                        });
                    if (nextWs != stations.end())
                    {
                        m_activeLine.back()->setNextStation(*nextWs);
                    }
                }
               
            }

            auto firstSt = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws)
                {
                    return std::none_of(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws1)
                        {
                            return ws == ws1->getNextStation();
                    });
                });

            if (firstSt != m_activeLine.end())
            {
                m_firstStation = *firstSt;
            }

            m_cntCustomerOrder = g_pending.size();
        }
        else
        {
            throw std::string("Error: Invalid file given");
        }
    }

    void LineManager::reorderStations()
    {
        std::vector<Workstation*> reordered;
        reordered.push_back(m_firstStation);
        reordered.push_back(m_firstStation->getNextStation());
        for_each(m_activeLine.begin() + 2, m_activeLine.end(), [&](Workstation* work) {
            reordered.push_back(reordered.back()->getNextStation());
        });

        m_activeLine = std::move(reordered);
    }

    bool LineManager::run(std::ostream& os)
    {
        static size_t iterationNum{};
        ++iterationNum;

        os << "Line Manager Iteration: " << iterationNum << std::endl;
        if (!g_pending.empty())
        {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* work)
        {
                work->fill(os);
        });

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* work)
        {
                work->attemptToMoveOrder();
        });
       //All orders have been completed
        return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
    }

    void LineManager::display(std::ostream& os) const
    {
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* work)
            {
                work->display(os);
            });
    }
}