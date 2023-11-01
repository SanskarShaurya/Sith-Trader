#include <cstring>
#include <vector>
#include <string>

class Stock
{
public:
    int standard;
    int bestSelling;
    int bestBuying;
    bool hasBestSelling = 0;
    bool hasBestBuying = 0;
    void printState(){
        std::cout << "standard: " << standard << "\r\n";
        if(hasBestBuying) std::cout<< "bestBuying: " << bestBuying << "\r\n";
        if(hasBestSelling) std::cout<< "bestSelling: " << bestSelling << "\r\n";    
    }
    Stock(){
        hasBestBuying = 0;
        hasBestSelling = 0;
    }
    Stock(int stockStandard) : standard(stockStandard) {
        hasBestBuying = 0;
        hasBestSelling = 0;
    }
};
