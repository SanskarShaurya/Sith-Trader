#include "receiver.h"
#include "map.h"
#include <vector>
#include <string>
#include "Stock.h"
// class Stock
// {
// public:
//     std::string name;
//     int value;
//     Stock(const std::string &stockName, int stockValue) : name(stockName), value(stockValue) {}

//     // Overload the ">" operator to compare based on name
//     bool operator>(const Stock &other) const
//     {
//         return std::strcmp(name.c_str(), other.name.c_str()) > 0;
//     }
//     bool operator<(const Stock& other) const {
//         return std::strcmp(name.c_str(), other.name.c_str()) < 0;
//     }
// };

// void add_stock(std::vector<Stock*>& v, Stock* s){
//     v.push_back(s);
// }

// Stock* search_stock(std::vector<Stock*>& v, std::string s){
//     for(auto a: v){
//         if(a->name == s) return a;
//     }
//     return NULL;
// }

int main() {

    Receiver rcv;
    std::string message = "";
    while(true){
        message += rcv.readIML();
        if(message[message.size() - 1] == '$') break;
    }
    char delimiter = '#';
    std::vector<std::string> input;
    size_t start = 0, end = 0;
    while ((end = message.find(delimiter, start)) != std::string::npos) {
        input.push_back(message.substr(start, end - start));
        start = end + 2;
    }
    delimiter = ' ';
    // std::vector<Stock*> stocks;
    Map<Stock> stocks;
    int check;
    for (auto i : input){
        std::vector<std::string> order;
        order.resize(3);
        start = 0;
        end = 0;
        int k = 0;
        while ((end = i.find(delimiter, start)) != std::string::npos) {
            order[k] = i.substr(start, end - start);
            k++;
            start = end + 1;
        }
        order[k] = i.substr(start);

        mystring curr = mystring(order[0]);
        if (stocks.find(curr) == 0){
            stocks[curr].standard = stoi(order[1]);
            std::cout << order[0] << " " << order[1] << " ";
            if (order[2]=="s") std::cout << "b\r\n";
            else std::cout << "s\r\n";
        }else{
            if(order[2]=="s"){
                if(stocks[curr].hasBestSelling){
                    if(stoi(order[1]) == stocks[curr].bestSelling) {
                        std::cout << "No Trade" << "\r\n";
                        stocks[curr].hasBestSelling = 0;
                    }
                }else{
                    if(stocks[curr].standard > stoi(order[1])){
                        std::cout << order[0] << " " << order[1] << " " << "b\r\n";
                    }else{
                        std::cout << "No Trade" << "\r\n";
                        if(stocks[curr].hasBestBuying){
                            if(stocks[curr].bestBuying < stoi(order[1])){
                                stocks[curr].bestBuying = stoi(order[1]);
                            }
                        }else{
                            stocks[curr].bestBuying = stoi(order[1]);
                            stocks[curr].hasBestBuying = 1;
                        }
                    } 
                }
            }else{
                if(stocks[curr].hasBestBuying){
                    if(stoi(order[1]) == stocks[curr].bestBuying) {
                        std::cout << "No Trade" << "\r\n";
                        stocks[curr].hasBestBuying = 0;
                    }
                }else{
                    if(stocks[curr].standard < stoi(order[1])){
                        std::cout << order[0] << " " << order[1] << " " << "b\r\n";
                    }else{
                        std::cout << "No Trade" << "\r\n";
                        if(stocks[curr].hasBestSelling){
                            if(stocks[curr].bestSelling < stoi(order[1])){
                                stocks[curr].bestSelling = stoi(order[1]);
                            }
                        }else{
                            stocks[curr].bestSelling = stoi(order[1]);
                            stocks[curr].hasBestSelling = 1;
                        }
                    } 
                }
            }
        }
    }
    return 0;
}