#include <vector>
#include <string>
#include "Package.h"

class order{    
public:
    int inTime;
    int lifeTime = -1;
    string clientName;
    int isBuy;
    int price;
    int quantity;
    bool isInfinite = false;
    bool invalid = false;
    RedBlackTree<int> stocks;
    int age;

    bool operator<(const order& o2) const {
        if (this->price != o2.price)
        return this->price*isBuy > o2.price*o2.isBuy;
        if (this->inTime != o2.inTime)
        return this->inTime < o2.inTime;
        return this->clientName < o2.clientName;
    }

    bool operator>(const order& o2) const{
        return o2 < *this;
    }

    void printOrder(){
        std::cout << "Client Name: " << clientName << std::endl;
        std::cout << "Is Buy: " << isBuy << std::endl;
        std::cout << "Price: " << price << std::endl;
        std::cout << "Quantity: " << quantity << std::endl;
        for(auto i : stocks){
            if(i.second) std::cout << i.first.name << " " << i.second << std::endl;
        }
    }

    order(std::string line){
        char delimiter = ' ';
        std::vector<std::string> word;
        size_t start = 0;
        size_t end = 0;
        while ((end = line.find(delimiter, start)) != std::string::npos)
        {
            word.push_back(line.substr(start, end - start));
            start = end + 1;
        }
        word.push_back(line.substr(start));
        if(word.size() < 7 || word[word.size()-2][0]!='#') {invalid = true; return;}
        
        inTime = stoi(word[0]);
        clientName = word[1];
        isBuy = (word[2] == "BUY") ? 1 : -1;
        if(stoi(word[word.size()-1]) != -1) lifeTime = stoi(word[word.size()-1]);
        else isInfinite = true;
        quantity = stoi(word[word.size()-2].substr(1));
        price = stoi(word[word.size()-3].substr(1));
        if(word.size()==7){
            stocks.insert(word[3],1);
            stocks.nodeCount = 1;
        }else{
            for(int i = 3; i<word.size()-3; i+=2){
                stocks.insert(word[i],stoi(word[i+1]));
            }
            stocks.nodeCount = (word.size() - 6)/2;
        }

    }
};
