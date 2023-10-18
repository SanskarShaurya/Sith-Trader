#include "receiver.h"
#include <vector>
#include <string>

class Stock
{
public:
    std::string name;
    int value;
    Stock(const std::string &stockName, int stockValue) : name(stockName), value(stockValue) {}

    // Overload the ">" operator to compare based on name
    bool operator>(const Stock &other) const
    {
        return std::strcmp(name.c_str(), other.name.c_str()) > 0;
    }
    bool operator<(const Stock& other) const {
        return std::strcmp(name.c_str(), other.name.c_str()) < 0;
    }
};

void add_stock(std::vector<Stock*>& v, Stock* s){
    v.push_back(s);
}

Stock* search_stock(std::vector<Stock*>& v, std::string s){
    for(auto a: v){
        if(a->name == s) return a;
    }
    return NULL;
}

int main() {

    Receiver rcv;
    std::string message = rcv.readIML();
    char delimiter = '#';
    std::vector<std::string> input;
    size_t start = 0, end = 0;
    while ((end = message.find(delimiter, start)) != std::string::npos) {
        input.push_back(message.substr(start, end - start));
        start = end + 2;
    }

    delimiter = ' ';
    std::vector<Stock*> stocks;
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
        Stock* curr = search_stock(stocks, order[0]);
        if (curr == NULL){
            Stock* newStock = new Stock (order[0],stoi(order[1]));
            stocks.push_back(newStock);
            std::cout << order[0] << " " << order[1] << " ";
            if (order[2]=="s") std::cout << "b\n";
            else std::cout << "s\n";
        }else{
            if(order[2]=="s"){
                if(stoi(order[1]) < curr->value){
                    std::cout << order[0] << " " << order[1] << " " << "b\n";
                    curr->value = stoi(order[1]);
                } else std::cout << "No trade\n";
            } else {
                if(stoi(order[1]) > curr->value){
                    std::cout << order[0] << " " << order[1] << " " << "s\n";
                    curr->value = stoi(order[1]);
                } else std::cout << "No trade\n";
            }
        }
    }


    return 0;
}
