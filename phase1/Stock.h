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
    Stock(){
        hasBestBuying = 0;
        hasBestSelling = 0;
    }
    Stock(int stockStandard) : standard(stockStandard) {
        hasBestBuying = 0;
        hasBestSelling = 0;
    }
};
