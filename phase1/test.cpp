#include "map.h"

int main(){
    string a = "abcd";
    string b = "efgh";
    mystring a1 = mystring(a);
    mystring b1 = mystring(b);
    b = "hijk";
    mystring c1 = mystring(b);
    Map m;
    m[a1] = 10;
    m[b1] = 20;
    m[c1] = 30;
    cout<<m[b1];
    cout<<m[c1];
    cout<<m.find(a1)->second;
    b = "uikjh";
    mystring d1 = mystring(b);
    cout<<"\n"<<m.find(d1);
}