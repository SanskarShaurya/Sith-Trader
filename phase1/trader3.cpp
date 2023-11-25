#include "receiver.h"
#include <vector>
#include <string>
#include "Stock.h"
#include "Package.h"

void get_max_sum(vector<Package> &packages)
{
    RedBlackTree<myPair<int>> maxSum;
    for (auto i : packages)
    {
        for (auto j : i.stocks)
        {
            if (j.second * i.isBuy > 0)
            {
                maxSum.search(j.first).first += j.second * i.isBuy * i.q2;
            }
            else
            {
                maxSum.search(j.first).second += j.second * i.isBuy * i.q2;
            }
        }
    }
    for (auto it = packages.begin(); it != packages.end(); it++)
        it->set_max(maxSum);
    bool flag = true;
    for (auto it = packages.begin(); it != packages.end(); it++)
    {
        if (it->q2 != it->maxQuantity)
        {
            it->q2 = it->maxQuantity;
            flag = false;
        }
    }
    if (flag)
    {
        for (auto it = packages.begin(); it != packages.end(); it++)
            it->q2 = it->quantity;
        return;
    }
    if (!flag)
        get_max_sum(packages);
}

int main()
{
    Receiver rcv;
    std::string message = "";
    while (true)
    {
        message += rcv.readIML();
        if (message[message.size() - 1] == '$')
            break;
    }
    char delimiter = '#';
    std::vector<std::string> input;
    size_t start = 0, end = 0;
    while ((end = message.find(delimiter, start)) != std::string::npos)
    {
        input.push_back(message.substr(start, end - start));
        start = end + 2;
    }
    delimiter = ' ';
    vector<Package> packages;
    RedBlackTree<myPair<int>> maxSum;
    int net_profit = 0;
    bool skip = false;
    for (auto ms : input)
    {
        Package P1(ms);
        bool flag = 0;
        // std::cout << P1.quantity << std::endl;
        for (auto it = packages.begin(); it != packages.end(); it++)
        {
            auto i = *it;
            if (i == P1 && i.price == P1.price)
            {
                if (P1.isBuy == i.isBuy)
                {
                    it->quantity += P1.quantity;
                }
                else
                {
                    if (i.quantity > P1.quantity)
                    {
                        it->quantity -= P1.quantity;
                        skip = true;
                    }
                    else
                    {
                        P1.quantity = P1.quantity - i.quantity;
                        packages.erase(it);
                        if (P1.quantity != 0)
                        {
                            flag = 0;
                            break;
                        }
                        else
                        {
                            skip = true;
                        }
                    }
                }
                flag = 1;
                break;
            }
        }

        if (skip)
        {
            skip = false;
            continue;
        }

        if (!flag)
        {
            packages.push_back(P1);
        }
        get_max_sum(packages);
        std::cout << "No Trade" << std::endl;
    }
    for (auto i : packages)
    {
        i.printPackage();
    }
    return 0;
}