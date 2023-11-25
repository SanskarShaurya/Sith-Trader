#include<iostream>
#include "map.h"


using namespace std;

int main(){
    RedBlackTree<myPair<int>> x;
    x.search(mystring("l"));
    for(auto i : x){
        std::cout << i.first.name << " " << i.second.first << i.second.second <<  std::endl;
    }
}