#include "fug.h"
#include <iostream>

class trial{
public:
    int median;
    int totalQuantity;
    int rightQuantity;
    int leftQuantity;
    MinHeap<quantities> right;
    MinHeap<quantities> left;

    trial()
    {
        median = 0;
        totalQuantity = 0;
        rightQuantity = 0;
        leftQuantity = 0;
        right = MinHeap<quantities>();
        left = MinHeap <quantities>();
    }

    int getMedian(int price, int quantity){
        totalQuantity += quantity;
        if(price>median){
            right.push(quantities(price, quantity,1));
            rightQuantity += quantity;
        }else{
            left.push(quantities(price, quantity,-1));
            leftQuantity += quantity;
        }
        
        if(totalQuantity%2==0){
            if(rightQuantity==leftQuantity) return (left.top().price + right.top().price)/2;
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
            return (left.top().price + right.top().price)/2;
        }else{
            if(rightQuantity+1==leftQuantity) return left.top().price;
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
            return left.top().price;
        }
    }
};

using namespace std;

int main () {
    trial t = trial();
    std::cout << t.getMedian(3, 2) << std::endl;
    std::cout << t.getMedian(7, 4) << std::endl;
    std::cout << t.getMedian(2, 6) << std::endl;
    // std::cout << t.getMedian(2,201) << std::endl;
}