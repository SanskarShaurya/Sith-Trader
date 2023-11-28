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
                text.push_back(order(line));
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
        for (auto it = heapList.begin(); it != heapList.end(); it++)
        {
            if (it->buy.size() != 0)
            {
                order curr = it->buy.top();
                curr.age = text.size();
                int currTime = curr.inTime;
                string m = "";
                m = m + std::to_string(time) + " " + client_name + " SELL ";
                for (auto i : it->stocks)
                    {
                      if(i.second != 0 )m = m + i.first.name;
                    }
                std::lock_guard<std::mutex> lock(printMutex);
                m = m + " $" + std::to_string(curr.price) + " #" + std::to_string(curr.quantity) + " -1";
                std::cout << m << std::endl;
                order x = order(m);
                x.age = text.size();
                it->sell.push(x);
                text.push_back(x);
                it->ifTrade(currTime);
            }
            if(it->sell.size()!=0){
                order curr = it->sell.top();
                curr.age = text.size();
                int currTime = curr.inTime;
                string m = "";
                m = m + std::to_string(t) + " " + client_name + " BUY ";
                for(auto i : it->stocks) {if(i.second!=0) m = m + i.first.name;}
                m = m + " $" + std::to_string(curr.price) + " #" + std::to_string(curr.quantity) + " -1";
                std::lock_guard<std::mutex> lock(printMutex);
                std::cout << m << std::endl;
                order x = order(m);
                x.age = text.size();
                it->buy.push(x);
                text.push_back(x);
                it->ifTrade(currTime);
            }
        }
    }

    return 0;
}

int trader(std::string *message)
{
    return 1;
}
