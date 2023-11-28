#include "market.h"
#include <fstream>
#include <sstream>
#include <iostream>

int totalMoney = 0;
int trades = 0;
int shares = 0;
RedBlackTree<myTriple<int>> clients;

struct nofug{
    RedBlackTree<int> stocks;
    MinHeap<order> buy;
    MinHeap<order> sell;
    nofug(){
        stocks = RedBlackTree<int>();
        buy = MinHeap<order>();
        sell = MinHeap<order>();
    }
    nofug(order o){
        stocks = o.stocks;
        if(o.isBuy==1){
            buy.push(o);
        }else {
            sell.push(o);
        }
    }
};

void ifTrade(nofug& mynofuggu, int currTime){
    if (mynofuggu.buy.size() == 0 || mynofuggu.sell.size() == 0) return;
    order* buyOrder = &mynofuggu.buy.top();
    order* sellOrder = &mynofuggu.sell.top();
    if (buyOrder->lifeTime != -1 && buyOrder->lifeTime + buyOrder->inTime < currTime) {
        mynofuggu.buy.pop();
        ifTrade(mynofuggu, currTime);
        return;
    }
    if(sellOrder->lifeTime != -1 && sellOrder->lifeTime + sellOrder->inTime < currTime){
        mynofuggu.sell.pop();
        ifTrade(mynofuggu, currTime);
        return;
    }
    if (buyOrder->price < sellOrder->price) return;
    int tradeQuantity = std::min(buyOrder->quantity, sellOrder->quantity);
    int tradePrice = buyOrder->age < sellOrder->age ? buyOrder->price : sellOrder->price;
    buyOrder->quantity -= tradeQuantity; 
    sellOrder->quantity -= tradeQuantity;
    std::cout<<buyOrder->clientName<<" purchased "<<tradeQuantity<<" share of ";
    int count = 0;
    for(auto i :buyOrder->stocks){
        if(i.second) count++;
    }
    for(auto i : buyOrder->stocks){
        if(count == 1 && i.second == 1) {
            std::cout << i.first.name << " ";
            break;
        }
        if(i.second) std::cout << i.first.name << " " << i.second<<" ";
    }
    totalMoney += tradeQuantity*tradePrice;
    trades++;
    shares += tradeQuantity;
    clients.search(buyOrder->clientName).first += tradeQuantity;
    clients.search(sellOrder->clientName).second += tradeQuantity;
    clients.search(buyOrder->clientName).third -= tradeQuantity*tradePrice;
    clients.search(sellOrder->clientName).third += tradeQuantity*tradePrice;

    std::cout<<"from "<<sellOrder->clientName<<" for "<<tradePrice<<"$/share"<<std::endl;
    if(buyOrder->quantity == 0) mynofuggu.buy.pop();
    if(sellOrder->quantity == 0) mynofuggu.sell.pop();
    ifTrade(mynofuggu, currTime);
    return;
}


market::market(int argc, char** argv)
{

}

void market::start()
{
    // std::cout << "Ok" << std::endl;
    std::string file_path = "output.txt";
    std::ifstream file(file_path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    // Close the file
    file.close();

    // Read the string line by line
    std::string line;
    vector<nofug> heapList;
    int currTime = 0;
    int age = 0;
    while (std::getline(buffer, line)) {
        age = age + 1;
        if(line == "@!") break;
        if(line == "TL" || line == "!@") continue;
        order curr = order(line);
        if(curr.invalid) continue;

        if(curr.inTime > currTime) currTime = curr.inTime;
        curr.age = age;
        nofug* foundElement = nullptr;
        for(auto it = heapList.begin(); it != heapList.end(); it++){
            if(curr.stocks == it->stocks){
                foundElement = &(*it);
                break;
            }
        }
        clients.search(curr.clientName);
        if(foundElement==nullptr){
            heapList.push_back(nofug(curr));
            continue;
        }
        if(curr.isBuy==1){
            foundElement->buy.push(curr);
        }else{
            foundElement->sell.push(curr);
        }
        ifTrade(*foundElement, currTime);
    }
    std::cout << std::endl;
    std::cout << "---End of Day---" << std::endl;
    std::cout << "Total Amount of Money Transferred: $" << totalMoney << std::endl;
    std::cout << "Number of Completed Trades: " << trades << std::endl;
    std::cout << "Number of Shares Traded: " << shares << std::endl;
    for(auto i : clients){
        std::cout << i.first.name << " bought " << i.second.first << " and sold " << i.second.second << " for a net transfer of $" << i.second.third << std::endl;
    }

}
