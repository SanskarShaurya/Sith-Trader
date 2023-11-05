#include <vector>
#include <string>
#include "map.h"


class Package
{
public:
    RedBlackTree<int> stocks;
    int price;
    int isBuy;
    vector<int> indexes;
    Package() {};
    Package(std::string i, int index) {
        indexes.push_back(index);
        char delimiter = ' ';
        std::vector<std::string> order;
        size_t start = 0;
        size_t end = 0;
        while ((end = i.find(delimiter, start)) != std::string::npos)
        {
            order.push_back(i.substr(start, end - start));
            start = end + 1;
        }
        order.push_back(i.substr(start));
        for(int j = 0; j<order.size()-2; j+=2){
            stocks.insert(order[j],stoi(order[j+1]));
        }
        price = stoi(order[order.size()-2]);
        isBuy = (order[order.size()-1] == "b") ? 1 : -1;
    }
    
    Package(RedBlackTree<int> input, int isBuy, int price) : stocks(input), isBuy(isBuy), price(price) {};
    Package(const Package& other)
    : price(other.price), isBuy(other.isBuy) {
        RedBlackTree<int> temp (other.stocks);
        stocks = temp;
    }
    Package operator+(Package& rhs)
    {
        RedBlackTree<int> temp = this->stocks; 
        for(auto i : rhs.stocks){
            temp.search(i.first) = (this->stocks.search(i.first))*this->isBuy + (i.second)*(rhs.isBuy);
        }
        int res = this->price + rhs.price;
        return Package(temp,1,res);
    }
    
};

