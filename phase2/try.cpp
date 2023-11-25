#include "heap1.h"
#include <iostream>

using namespace std;

int main () {
    MinHeap heap1;
    MinHeap heap2;
    order first = order("2 C SELL AMZN $100 #18 10");
    heap1.push(first);
    order second = order("1 A BUY AMZN $100 #30 5");
    heap2.push(second);
    std::cout<<heap1.top().price<<heap2.top().price<<std::endl;
    order third = order("3 B SELL AMZN $100 #5 0");
    heap1.push(third);
    std::cout<<heap1.top().clientName<<heap2.top().clientName<<std::endl;


}