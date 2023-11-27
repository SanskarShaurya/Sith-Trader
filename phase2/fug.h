#include "heap1.h"
class fug
{
public:
    RedBlackTree<int> stocks;
    MinHeap buy;
    MinHeap sell;
    fug()
    {
        stocks = RedBlackTree<int>();
        buy = MinHeap();
        sell = MinHeap();
    }
    fug(order o)
    {
        stocks = o.stocks;
        if (o.isBuy == 1)
        {
            buy.push(o);
        }
        else
        {
            sell.push(o);
        }
    }

    void ifTrade(int currTime)
    {
        if (this->buy.size() == 0 || this->sell.size() == 0)
            return;
        order *buyOrder = &this->buy.top();
        order *sellOrder = &this->sell.top();
        if (buyOrder->lifeTime != -1 && buyOrder->lifeTime + buyOrder->inTime < currTime)
        {
            this->buy.pop();
            this->ifTrade(currTime);
            return;
        }
        if (sellOrder->lifeTime != -1 && sellOrder->lifeTime + sellOrder->inTime < currTime)
        {
            this->sell.pop();
            this->ifTrade(currTime);
            return;
        }
        if (buyOrder->price < sellOrder->price)
            return;
        int tradeQuantity = std::min(buyOrder->quantity, sellOrder->quantity);
        int tradePrice = buyOrder->age < sellOrder->age ? buyOrder->price : sellOrder->price;
        buyOrder->quantity -= tradeQuantity;
        sellOrder->quantity -= tradeQuantity;
        if (buyOrder->quantity == 0)
            this->buy.pop();
        if (sellOrder->quantity == 0)
            this->sell.pop();
        this->ifTrade(currTime);
        return;
    }
};