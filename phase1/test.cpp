#include "map.h"
#include "set.h"
int main(){
    Map<int> stocks;
    Map<RedBlackTree> stock_prices;
    mystring a("abcd");
    mystring b("cdef");
    stock_prices[a].insert(10);
    stock_prices[a].insert(20);
    stock_prices[a].insert(30);
    stock_prices[a].insert(40);
    stock_prices[a].printTree();
    stock_prices[a].deleteNode(30);
    stock_prices[a].printTree();
}
