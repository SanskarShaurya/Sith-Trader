// This is your trader. Place your orders from here
#include <iostream>
#include <atomic>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>
#include <fstream>
#include "Order.h"

extern std::atomic<int> commonTimer;
extern std::mutex printMutex;  // Declare the mutex for printing
std::string client_name = "Harry";

static std::vector<order> text;

int reader(int time)
{
    std::ifstream file ("output.txt");
    std::string line;
    int t = commonTimer.load();
    int i = 0;
    while(std::getline(file, line)){
        if(line[0] == '!' && line[1] == '@') {
            return 1;
        }
        if(line == "TL" || line == "") continue;
        // if(text.size()!=0) if(text[text.size()-1].clientName==client_name) {continue;}
        i++;
        if(i>text.size()){
            text.push_back(order(line));
        }
    }
    if(text.size() >= 2 && text[text.size()-1].clientName!=client_name) {
        std::lock_guard<std::mutex> lock(printMutex);
        std::cout<<time<<" Harry BUY AMD $100 #32 3"<<std::endl;
        text.push_back(order(std::to_string(time) + " Harry BUY AMD $100 #32 3"));
    }
    
    
    return 0;
}

int trader(std::string *message)
{
    return 1;
}
 