// This is your trader. Place your orders from here
#include <iostream>
#include <atomic>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>
#include <fstream>
#include "fug.h"

extern std::atomic<int> commonTimer;
extern std::mutex printMutex; // Declare the mutex for printing
std::string client_name = "Harry";
static string last_client;
static std::vector<order> text;
static vector<fug> heapList;

int reader(int time)
{
    std::ifstream file("output.txt");
    std::string line;
    int t = commonTimer.load();
    int i = 0;
    while (std::getline(file, line))
    {
        if (line[0] == '!' && line[1] == '@')
        {
            return 1;
        }
        if (line == "TL" || line == "")
            continue;
        i++;
        if (i > text.size())
        {
            order curr = order(line);
            if (curr.invalid)
            {
                i--;
                continue;
            }
            curr.age = text.size();
            int currTime = curr.inTime;
            fug *foundElement = nullptr;
            for (auto it = heapList.begin(); it != heapList.end(); it++)
            {
                if (curr.stocks == it->stocks)
                {
                    foundElement = &(*it);
                    break;
                }
            }
            if (foundElement == nullptr)
            {
                heapList.push_back(fug(curr));
                continue;
            }
            if (curr.isBuy == 1)
            {
                foundElement->buy.push(curr);
            }
            else
            {
                foundElement->sell.push(curr);
            }
            foundElement->ifTrade(currTime);
            text.push_back(order(line));
        }
    }
    if (text.size() > 0 && text[text.size() - 1].clientName != client_name)
    {

        // std::cout << time << " Harry BUY AMD $100 #32 3" << std::endl;
        // text.push_back(order(std::to_string(time) + " Harry BUY AMD $100 #32 3"));
        for (auto fugs : heapList)
        {
            if (fugs.buy.size() != 0)
            {
                order curr = fugs.buy.top();
                string m = "";
                m = m + std::to_string(time) + " " + client_name + " SELL ";
                for (auto i : fugs.stocks)
                    {
                      if(i.second != 0 )m = m + i.first.name;
                    }
                m = m + " $" + std::to_string(curr.price) + " #" + std::to_string(curr.quantity) + " -1";
                std::lock_guard<std::mutex> lock(printMutex);
                std::cout << m << std::endl;
                fugs.sell.push(order(m));
                text.push_back(order(m));
            }
            else if(fugs.sell.size()!=0){
                order curr = fugs.sell.top();
                string m = "";
                m = m + std::to_string(time) + " " + client_name + " BUY ";
                for(auto i : fugs.stocks) if(i.second!=0) m = m + i.first.name ;
                m = m + " $" + std::to_string(curr.price) + " #" + std::to_string(curr.quantity) + " -1";
                std::cout << m << std::endl;
                fugs.buy.push(order(m));
                text.push_back(order(m));
            }
        }
    }

    return 0;
}

int trader(std::string *message)
{
    return 1;
}
