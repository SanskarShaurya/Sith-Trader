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
    int net_profit = 0;
    for(auto ms : input){
        Package P1(ms);
        bool flag = 0;
        for(auto it = packages.begin(); it != packages.end(); it++){
            auto i = *it;
            if(i == P1){
                if(i.isBuy == P1.isBuy){
                    if(P1.price*P1.isBuy <= i.price*i.isBuy){
                        flag = 1;break;
                    }
                    else {packages.erase(it);break;}
                }else if(i.isBuy + P1.isBuy == 0){
                    if(i.price == P1.price){
                        flag=1;
                        packages.erase(it);
                        break;
                    }
                }
            }
        }
        if(flag){std::cout<<"No Trade"<<std::endl; continue;}
        Package bestPackage;
        int maxProfit = 0;
        int n = packages.size();
        for (int i = 0; i < (1 << n); i++)
        {
            Package P = P1;
            P.indexes.push_back(n);
            for (int j = n - 1; j >= 0; j--)
            {
                if ((i & (1 << j)) != 0){
                    P = P + packages[j];
                    P.indexes.push_back(j);
                }
            }
            int check = P.isArbitrage();
            if(P.price > maxProfit && check){
                maxProfit = P.price;
                bestPackage = P;
            }
        }
        packages.push_back(P1); 
        if(bestPackage.indexes.size() == 0)std::cout<<"No Trade"<<std::endl;
        else{
            for(auto k : bestPackage.indexes){
                packages[k].printPackage();
                packages.erase(packages.begin() + k);
            }
            net_profit+=bestPackage.price;
        }
    }
    std::cout << net_profit << std::endl;
    for(auto i : packages){
        i.printPackage();
        char b;
        b = (i.isBuy == 1) ? 's' : 'b';
        std::cout << b <<  std::endl;
    }
    return 0;
}