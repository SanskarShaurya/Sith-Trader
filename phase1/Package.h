#include <vector>
#include <string>
#include "map.h"


class Package
{
public:
    RedBlackTree<int> stocks;
    int price = 0;
    int isBuy;
    vector<int> indexes;
    Package() {};
    Package(std::string i) {
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
        isBuy = (order[order.size()-1] == "b") ? 1 : -1;
        price = stoi(order[order.size()-2]) ;
    }
    
    Package(RedBlackTree<int> input, int isBuy, int price, vector<int> indexes) : stocks(input), isBuy(isBuy), price(price) ,indexes(indexes) {};
    Package(const Package& other)
    : price(other.price), isBuy(other.isBuy) {
        RedBlackTree<int> temp (other.stocks);
        stocks = temp;
    }
    Package operator+(Package& rhs)
    {
        RedBlackTree<int> temp = this->stocks; 
        for(auto i: temp) temp.search(i.first) = i.second * this->isBuy;
        for(auto i : rhs.stocks){
            temp.search(i.first) = temp.search(i.first) + (i.second)*(rhs.isBuy);
        }
        int res = this->price*this->isBuy + rhs.price*rhs.isBuy;
        return Package(temp,1,res, this->indexes);
    }

    bool isArbitrage(){
        for(auto i : stocks){
            if(i.second != 0){
                return false;
            }
        }
        return true;
    }
    void printPackage(){
        for(auto i : stocks){
            std::cout << i.first.name << " " << i.second << " ";
        }
        std::cout << price << " ";
        char b;
        b = (isBuy == 1) ? 's' : 'b';
        std::cout << b << std::endl;
    }
};

