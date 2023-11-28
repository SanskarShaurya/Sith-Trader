#include "heap1.h"
#include "quantities.h"


class fug
{
public:
    RedBlackTree<int> stocks;
    MinHeap<order> buy;
    MinHeap<order> sell;
    int median = 0;
    int totalQuantity = 0;
    int rightQuantity = 0;
    int leftQuantity = 0;
    MinHeap<quantities> right;
    MinHeap<quantities> left;

    fug()
    {
        stocks = RedBlackTree<int>();
        buy = MinHeap<order>();
        sell = MinHeap<order>();
        right = MinHeap<quantities>();
        left = MinHeap <quantities>();
        median = 0;
        totalQuantity = 0;
        rightQuantity = 0;
        leftQuantity = 0;
    }

    fug(const fug& other)
    : median(other.median), totalQuantity(other.totalQuantity), right(other.right), left(other.left),rightQuantity(other.rightQuantity), leftQuantity(other.leftQuantity){
        RedBlackTree<int> temp (other.stocks);
        this->stocks = temp;
    }

    fug(order o)
    {
        buy = MinHeap<order>();
        sell = MinHeap<order>();
        right = MinHeap<quantities>();
        left = MinHeap <quantities>();
        median = 0;
        totalQuantity = 0;
        rightQuantity = 0;
        leftQuantity = 0;
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

    void getMedian(int price, int quantity){
        totalQuantity += quantity;
        if(totalQuantity==0) return;
        if(price>median){
            right.push(quantities(price, quantity,1));
            rightQuantity += quantity;
        }else{
            left.push(quantities(price, quantity,-1));
            leftQuantity += quantity;
        }
        if(totalQuantity%2==0){
            if(rightQuantity==leftQuantity) {median = (left.top().price + right.top().price)/2;return;}
            MinHeap<quantities>* x = (leftQuantity>rightQuantity) ? &left : &right;
            MinHeap<quantities>* y = (leftQuantity>rightQuantity) ? &right : &left;

            int k = (leftQuantity>rightQuantity) ? leftQuantity - totalQuantity/2 : rightQuantity - totalQuantity/2;
            int temp = k;
            while(k>0){
                if(k <= x->top().quantity){
                    x->top().quantity -= k;
                    y->push(quantities(x->top().price, k, -1*x->top().minmax));
                    if(x->top().quantity == 0) x->pop();
                    break;
                }
                k -= x->top().quantity;
                y->push(quantities(x->top().price, x->top().quantity, -1*x->top().minmax));
                x->pop();
            }
            k = temp;
            if(x == &left) {leftQuantity -= k; rightQuantity += k;}
            if(x == &right) {rightQuantity -= k;leftQuantity += k;}
            median = (left.top().price + right.top().price)/2;
            // return (left.top().price + right.top().price)/2;
        }else{

            if(rightQuantity+1==leftQuantity) {median = left.top().price;return;}
            MinHeap<quantities>* x = (leftQuantity>rightQuantity+1) ? &left : &right;
            MinHeap<quantities>* y = (leftQuantity>rightQuantity+1) ? &right : &left;

            int k = (leftQuantity>rightQuantity+1) ? leftQuantity - totalQuantity/2 - 1 : rightQuantity - totalQuantity/2;
            int temp = k;

            while(k>0){

                if(k <= x->top().quantity){
                    x->top().quantity -= k;
                    y->push(quantities(x->top().price, k, -1*x->top().minmax));
                    if(x->top().quantity == 0) x->pop();
                    break;
                }
                k -= x->top().quantity;
                y->push(quantities(x->top().price, x->top().quantity, -1*x->top().minmax));
                x->pop();
            }
            k = temp;
            if(x == &left) {leftQuantity -= k; rightQuantity += k;}
            if(x == &right) {rightQuantity -= k;leftQuantity += k;}
            median = left.top().price;
            // return left.top().price;
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
        getMedian(tradePrice, tradeQuantity);
        if (buyOrder->quantity == 0)
            this->buy.pop();
        if (sellOrder->quantity == 0)
            this->sell.pop();
        this->ifTrade(currTime);
        return;
    }
};