#include<string>

class mystring
{
public:
    std::string name;
    mystring(const std::string &stockName) : name(stockName){}
    mystring(){}
    // Copy constructor
    mystring(const mystring& other) : name(other.name) {}
    // Overload the ">" operator to compare based on name
    bool operator>(const mystring &other) const
    {
        return name.compare(other.name) > 0;
    }
    bool operator<(const mystring& other) const {
        return name.compare(other.name) < 0;
    }
    bool operator!=(const mystring& other) const {
        return name != other.name;
    }
    bool operator==(const mystring& other) const {
        return name == other.name;
    }
};