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
std::string client_name = "22B0985_22B0958";
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
        if (i > text.size()){
            order curr = order(line);
            curr.age = text.size();
            fug *foundElement = nullptr;
            for (auto it = heapList.begin(); it != heapList.end(); it++)
            {
                if (curr.stocks == it->stocks)
                {
                    foundElement = &(*it);
                    break;
                }
            }
            if(!foundElement){
                heapList.push_back(fug(curr));
                text.push_back(order(line));
                continue;
            }

            if(curr.isBuy==1){
                foundElement->buy.push(curr);
            }else{
                foundElement->sell.push(curr);
            }
            foundElement->ifTrade(t);
            text.push_back(order(line));
        }
        
        
    }

    if (text.size() > 0 && text[text.size() - 1].clientName != client_name)
    {
        for(auto it = heapList.begin(); it!=heapList.end(); it++){
            fug i = *it;

            if(it->buy.size() != 0){
                order top = it->buy.top();
                
                while(top.lifeTime!=-1 && top.inTime + top.lifeTime < t){
                    it->buy.pop();
                    if(it->buy.size()==0) break;
                    top = it->buy.top();
                }
                string m = "";
                m = m + std::to_string(t) + " " + client_name + " SELL ";
                int count = 0;
                for(auto i :it->stocks) count++;
                for (auto i : it->stocks)
                    {
                        if(count == 1) m = m + i.first.name + " ";
                        else if(i.second != 0 )m = m + i.first.name + " " + std::to_string(i.second) + " ";
                    }
                int expire;
                if(top.lifeTime == -1) expire = -1;
                else expire = top.inTime + top.lifeTime - t;
                m = m + "$" + std::to_string(top.price) + " #" + std::to_string(top.quantity) + " " + std::to_string(expire);
                
                order now = order(m);
                now.age = text.size();
                if(it->buy.size()!=0){ 
                    if(it->median == 0 || it->median < top.price)
                    {
                        it->sell.push(now);
                        it->ifTrade(t);
                        text.push_back(now);
                        {                
                            std::lock_guard<std::mutex> lock(printMutex);     
                            std::cout << m << std::endl;
                        }
                    }
                }

            }
            if(it->sell.size() != 0){
                order top = it->sell.top();
                while(top.lifeTime!=-1 && top.inTime + top.lifeTime < t){
                    it->sell.pop();
                    if(it->sell.size()==0) break;
                    top = it->sell.top();
                }
                string m = "";
                m = m + std::to_string(t) + " " + client_name + " BUY ";
                for (auto i : it->stocks)
                    {
                      if(i.second != 0 )m = m + i.first.name;
                    }
                int expire;
                if(top.lifeTime == -1) expire = -1;
                else expire = top.inTime + top.lifeTime - t;
                m = m + " $" + std::to_string(top.price) + " #" + std::to_string(top.quantity) + " " + std::to_string(expire);
                
                order now = order(m);
                now.age = text.size();
                if(it->sell.size()!=0){ 
                    if(it->median == 0 || it->median > top.price){
                        it->buy.push(now);
                        it->ifTrade(t);
                        text.push_back(now);
                        {                
                            std::lock_guard<std::mutex> lock(printMutex);     
                            std::cout << m << std::endl;
                        }
                    }
                }
            }
        }
    }

    return 0;
}

int trader(std::string *message)
{
    return 1;
}
