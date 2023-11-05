#include "receiver.h"
#include <vector>
#include <string>
#include "Stock.h"
#include "Package.h"


int main()
{
    Receiver rcv;
    std::string message = "";
    while (true)
    {
        message += rcv.readIML();
        if (message[message.size() - 1] == '$')
            break;
    }
    char delimiter = '#';
    std::vector<std::string> input;
    size_t start = 0, end = 0;
    while ((end = message.find(delimiter, start)) != std::string::npos)
    {
        input.push_back(message.substr(start, end - start));
        start = end + 2;
    }
    delimiter = ' ';
    vector<Package> packages;
    int min_profit = 0;
    Package best_Package;
    for(auto ms : input){
        int n = packages.size();
        for (int i = 0; i < (1 << n); i++)
        {
            Package P(ms, n-1);
            int provisional_profit = 0;
            for (int j = n - 1; j >= 0; j--)
            {
                if ((i & (1 << j)) != 0)
                    P = P + packages[j];
                    P.indexes.push_back(j);
                    provisional_profit += packages[j].price;
            }
            bool check = false;
            for(auto i : P.stocks){
                std::cout << i.first.name << " " << i.second << "\n";
            }
        }
        std::cout << "----------" << std::endl;
        packages.push_back(Package(ms, n-1));   
        // Package P(ms);
        // P = P + packages[0];
        // for(auto i : P.stocks){
        //     std::cout << i.first.name << " " << i.second << "\n";
        // }
    }
    return 0;
}