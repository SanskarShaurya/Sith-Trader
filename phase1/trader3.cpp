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
    RedBlackTree<myPair<int>> maxSum; 
    int net_profit = 0;
    bool skip = false;
    for(auto ms : input){
        Package P1(ms);
        bool flag = 0;
        // std::cout << P1.quantity << std::endl;
        for(auto it = packages.begin(); it != packages.end(); it++){
            auto i = *it;
            if(i == P1 && i.price == P1.price){
                if(P1.isBuy == i.isBuy){
                    it->quantity += P1.quantity;
                    for(auto i : P1.stocks){
                        if(i.second*P1.isBuy > 0){
                            maxSum.search(i.first).first += i.second*P1.isBuy*P1.quantity;
                        }else{
                            maxSum.search(i.first).second += i.second*P1.isBuy*P1.quantity;
                        }
                    }
                }else{
                    if(i.quantity > P1.quantity){
                        it->quantity -= P1.quantity;
                        for(auto j : P1.stocks){
                            if(j.second*i.isBuy > 0){
                                maxSum.search(j.first).first -= j.second*i.isBuy*P1.quantity;
                            }else{
                                maxSum.search(j.first).second -= j.second*i.isBuy*P1.quantity;
                            }
                        }
                        skip = true;
                    }else{
                        P1.quantity = P1.quantity - i.quantity;
                        for(auto j : i.stocks){
                            if(j.second*i.isBuy > 0){
                                maxSum.search(j.first).first -= j.second*i.isBuy*i.quantity;
                            }else{
                                maxSum.search(j.first).second -= j.second*i.isBuy*i.quantity;
                            }
                        }
                        packages.erase(it);
                        if(P1.quantity!=0) {
                            flag = 0;
                            break;
                        }else{
                            skip = true;
                        }
                        
                    }
                }
                flag = 1;
                break;
            }
        }

        if(skip){
            skip = false;
            continue;
        }

        if(!flag) {
            packages.push_back(P1);
            for(auto i : P1.stocks){
                if(i.second*P1.isBuy > 0){
                    maxSum.search(i.first).first += i.second*P1.isBuy*P1.quantity;
                }else{
                    maxSum.search(i.first).second += i.second*P1.isBuy*P1.quantity;
                }
            }
        
            // for(auto i: packages){
            //     std::cout << i.maxQuantity << std::endl;
            // }
            for(auto it = packages.begin(); it != packages.end(); it++){
                for(auto j : P1.stocks){
                    if(it->stocks.find(j.first)){
                        // std::cout << it->maxQuantity << std::endl;
                        if(it->stocks.search(j.first) > 0){
                            it->maxQuantity = min(it->maxQuantity, -1*(maxSum.search(j.first).second + 1)/it->stocks.search(j.first));
                        }else{
                            it->maxQuantity = min(it->maxQuantity, -1*(maxSum.search(j.first).first + 1)/it->stocks.search(j.first));
                        }
                    }   
                }
            }
        }
        std::cout << "No Trade" << std::endl;
        



        // Package bestPackage;
        // int maxProfit = 0;
        // int n = packages.size();
        // for (int i = 0; i < (1 << n); i++)
        // {
        //     Package P = P1;
        //     P.indexes.push_back(n);
        //     // std::cout<<n<<" ";

        //     for (int j = n - 1; j >= 0; j--)
        //     {
        //         if ((i & (1 << j)) != 0){
        //             P = P + packages[j];
        //             P.indexes.push_back(j);
        //             // std::cout<<j<<" ";
        //         }
        //     }
        //     // std::cout<<std::endl;
        //     int check = P.isArbitrage();
        //     // P.printPackage();
        //     // if(check) std::cout<<"Detected Arbitrage " << P.price<<std::endl;
        //     if(P.price > maxProfit && check){
        //         maxProfit = P.price;
        //         bestPackage = P;
        //     }
        //     // std::cout<<"----"<<std::endl;
        // }
        // // std::cout<<P1.stocks.nodeCount<<std::endl;
        // packages.push_back(P1); 
        // if(bestPackage.indexes.size() == 0)std::cout<<"No Trade"<<std::endl;
        // else{
        //     for(auto k : bestPackage.indexes){
        //         packages[k].printPackage();
        //         packages.erase(packages.begin() + k);
        //     }
        //     net_profit+=bestPackage.price;
        // }
        // std::cout<<"----------------"<<std::endl;
    }
    // std::cout << net_profit << std::endl;
    for(auto i : packages){
        i.printPackage();
    }
    for(auto i : maxSum){
        std::cout << i.first.name << " " << i.second.first << " " << i.second.second << std::endl;
    }
    return 0;
}