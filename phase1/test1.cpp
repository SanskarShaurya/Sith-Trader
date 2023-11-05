#include <iostream>
#include "Package.h"

int main(){
    int n = 30;
    // for (int i = 0; i < (1 << n); i++)
    // {
    //     for (int j = n - 1; j >= 0; j--)
    //     {
    //         if ((i & (1 << j)) != 0)
    //             std::cout << "1";
    //         else
    //             std::cout << "0";
    //     }
    //     std::cout << "\n";
    // }
    RedBlackTree<int> tree1;
    RedBlackTree<int> tree2;
    mystring c = mystring("c");
    mystring a = mystring("a");
    mystring b = mystring("b");
    mystring d = mystring("d");
    mystring g = mystring("c");
    mystring e = mystring("e");
    tree1.insert(b,2);
    tree1.insert(a,1);
    // tree1.insert(c,3);
    tree1.insert(d,4);
    tree1.insert(e,5);
    // tree2.insert(c,4);
    tree2.insert(g,5);
    Package first(tree1,1,50);
    Package second(tree2,-1,100);
    Package third = first + second;
    // first = first + second;
    for(auto it = third.stocks.begin(); it != third.stocks.end(); ++it){
        std::cout << (*it).first.name << " " << (*it).second << std::endl;
    }
    // for(auto it = first.stocks.begin(); it != first.stocks.end(); ++it){
    //     std::cout << (*it).first.name << " " << (*it).second << std::endl;
    // }
}