#include <iostream>
#include "Package.h"

int main(){
    vector<int> v = {1,2,4};
    
    RedBlackTree<int> tree1;
    RedBlackTree<int> tree2;
    Package first = Package("A 1 B 1 15 s");
    Package second = Package("A 1 B 1 10 s");
    if(first == second) std::cout << "YES" << std::endl;
    else std::cout << "NO" << std::endl;
}