#include <vector>
#include <string>
#include "map.h"

class Package
{
public:
    RedBlackTree<int> stocks;
    int price = 0;
    int isBuy;
    int quantity;
    int q2;
    int maxQuantity;
    vector<int> indexes;
    Package(){};
    Package(std::string i)
    {
        char delimiter = ' ';
        std::vector<std::string> order;
        size_t start = 0;
        size_t end = 0;
        while ((end = i.find(delimiter, start)) != std::string::npos)
        {
            order.push_back(i.substr(start, end - start));
            start = end + 1;
        }
        order.push_back(i.substr(start));
        for (int j = 0; j < order.size() - 3; j += 2)
        {
            stocks.insert(order[j], stoi(order[j + 1]));
        }
        stocks.nodeCount = (order.size() - 2) / 2;
        isBuy = (order[order.size() - 1] == "b") ? 1 : -1;
        if (order.size() % 2 == 0)
        {
            price = stoi(order[order.size() - 2]);
            quantity = 1;
        }
        else
        {
            quantity = stoi(order[order.size() - 2]);
            price = stoi(order[order.size() - 3]);
        }
        maxQuantity = quantity;
        q2 = quantity;
    }

    Package(RedBlackTree<int> input, int isBuy, int price, vector<int> indexes, int quantity) : stocks(input), isBuy(isBuy), price(price), indexes(indexes), quantity(quantity), maxQuantity(quantity), q2(quantity){};
    Package(const Package &other)
        : price(other.price), isBuy(other.isBuy), indexes(other.indexes), quantity(other.quantity), maxQuantity(other.maxQuantity), q2(other.q2)
    {
        RedBlackTree<int> temp(other.stocks);
        stocks = temp;
    }
    bool operator==(Package &rhs)
    {
        return (this->stocks == rhs.stocks);
    }

    Package operator*(int rhs)
    {
        RedBlackTree<int> temp = this->stocks;
        for (auto i : temp)
            temp.search(i.first) = i.second * rhs;
        return Package(temp, this->isBuy, this->price * rhs, this->indexes, this->quantity);
    }

    Package operator+(Package &rhs)
    {
        RedBlackTree<int> temp = this->stocks;
        for (auto i : temp)
            temp.search(i.first) = i.second * this->isBuy;
        for (auto i : rhs.stocks)
        {
            temp.search(i.first) = temp.search(i.first) + (i.second) * (rhs.isBuy);
        }
        int res = this->price * this->isBuy + rhs.price * rhs.isBuy;
        return Package(temp, 1, res, this->indexes, this->quantity);
    }

    bool isArbitrage()
    {
        for (auto i : stocks)
        {
            if (i.second != 0)
            {
                return false;
            }
        }
        return true;
    }
    void printPackage()
    {
        for (auto i : stocks)
        {
            std::cout << i.first.name << " " << i.second << " ";
        }
        std::cout << price << " ";
        char b;
        b = (isBuy == 1) ? 's' : 'b';
        std::cout << quantity << " max " << maxQuantity << " " << b << "#" << std::endl;
    }

    void set_max(RedBlackTree<myPair<int>> maxSum)
    {
        for (auto k : this->stocks)
        {
            auto a = this->maxQuantity;
            auto b = maxSum.search(k.first);
            auto c = this->stocks.search(k.first);
            auto d = (-1 * b.second + 1) / c;
            auto e = (b.first + 1) / (c * -1);
            if (c > 0)
            {
                if (b.second == 0)
                {
                    this->maxQuantity = 0;
                    break;
                }
                else
                {
                    if (a == 0)
                        this->maxQuantity = min(this->q2, d);
                    else
                        this->maxQuantity = min(a, d);
                }
            }
            else
            {
                if (b.first == 0)
                {
                    this->maxQuantity = 0;
                    break;
                }
                else
                {
                    if (a == 0)
                        this->maxQuantity = min(this->q2, e);
                    else
                        this->maxQuantity = min(a, e);
                }
            }
        }
    }
};
