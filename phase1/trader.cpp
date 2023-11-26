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

int find_all_c(std::vector<Package> &packages, std::vector<int> &results)
{
    int n = packages.size();
    int profit = 0;
    std::vector<int> c(n, 0);
    std::vector<int> ans(n, 0);
    c[n - 1] = 0;
    while (true)
    {
        Package sum;
        for (int i = 0; i < n; ++i)
        {
            Package temp = packages[i] * c[i];
            sum = sum + temp;
            // sum.printPackage();
            // std::cout <<std::endl << "-----" << std::endl;
        }

        if (sum.isArbitrage() && sum.price > profit)
        {
            ans = c;
            profit = sum.price;
        }

        // Increment the rightmost index
        int i = n - 1;
        while (i >= 0 && ++c[i] > packages[i].maxQuantity)
        {
            c[i--] = 0;
        }

        // Check if we've finished iterating
        if (i < 0)
        {
            break;
        }
    }
    results = ans;
    return profit;
}

int main(int argc, char *argv[])
{
    char choice = argv[1][0];
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
    if (choice == '1')
    {
        RedBlackTree<Stock> stocks;
        int check;
        for (auto i : input)
        {
            std::vector<std::string> order;
            order.resize(3);
            start = 0;
            end = 0;
            int k = 0;
            while ((end = i.find(delimiter, start)) != std::string::npos)
            {
                order[k] = i.substr(start, end - start);
                k++;
                start = end + 1;
            }
            order[k] = i.substr(start);

            mystring curr = mystring(order[0]);
            if (stocks.find(curr) == 0)
            {
                stocks.insert(curr, Stock(stoi(order[1])));
                stocks.search(curr).standard = stoi(order[1]);
                std::cout << order[0] << " " << order[1] << " ";
                if (order[2] == "s")
                    std::cout << "b\r\n";
                else
                    std::cout << "s\r\n";
            }
            else
            {
                if (order[2] == "s")
                {
                    if (stocks.search(curr).hasBestBuying)
                    {
                        if (stoi(order[1]) >= stocks.search(curr).bestBuying)
                        {
                            std::cout << "No Trade"
                                      << "\r\n";
                            continue;
                        }
                    }
                    if (stocks.search(curr).hasBestSelling)
                    {
                        if (stoi(order[1]) == stocks.search(curr).bestSelling)
                        {
                            std::cout << "No Trade"
                                      << "\r\n";
                            stocks.search(curr).hasBestSelling = 0;
                        }
                        else
                        {
                            goto banyan;
                        }
                    }
                    else
                    {
                    banyan:
                        if (stocks.search(curr).standard > stoi(order[1]))
                        {
                            std::cout << order[0] << " " << order[1] << " "
                                      << "b\r\n";
                            stocks.search(curr).standard = stoi(order[1]);
                            stocks.search(curr).hasBestBuying = 0;
                        }
                        else
                        {
                            std::cout << "No Trade"
                                      << "\r\n";
                            if (stocks.search(curr).hasBestBuying)
                            {
                                if (stocks.search(curr).bestBuying > stoi(order[1]))
                                {
                                    stocks.search(curr).bestBuying = stoi(order[1]);
                                }
                            }
                            else
                            {
                                stocks.search(curr).bestBuying = stoi(order[1]);
                                stocks.search(curr).hasBestBuying = 1;
                            }
                        }
                    }
                }
                else
                {
                    if (stocks.search(curr).hasBestSelling)
                    {
                        if (stoi(order[1]) <= stocks.search(curr).bestSelling)
                        {
                            std::cout << "No Trade"
                                      << "\r\n";
                            continue;
                        }
                    }
                    if (stocks.search(curr).hasBestBuying)
                    {
                        if (stoi(order[1]) == stocks.search(curr).bestBuying)
                        {
                            std::cout << "No Trade"
                                      << "\r\n";
                            stocks.search(curr).hasBestBuying = 0;
                        }
                        else
                        {
                            goto chaddi;
                        }
                    }
                    else
                    {
                    chaddi:
                        if (stocks.search(curr).standard < stoi(order[1]))
                        {
                            std::cout << order[0] << " " << order[1] << " "
                                      << "s\r\n";
                            stocks.search(curr).standard = stoi(order[1]);
                            stocks.search(curr).hasBestSelling = 0;
                        }
                        else
                        {
                            std::cout << "No Trade"
                                      << "\r\n";
                            if (stocks.search(curr).hasBestSelling)
                            {
                                if (stocks.search(curr).bestSelling < stoi(order[1]))
                                {
                                    stocks.search(curr).bestSelling = stoi(order[1]);
                                }
                            }
                            else
                            {
                                stocks.search(curr).bestSelling = stoi(order[1]);
                                stocks.search(curr).hasBestSelling = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    else if (choice == '2')
    {
        vector<Package> packages;
        int net_profit = 0;
        for (auto ms : input)
        {
            Package P1(ms);
            bool flag = 0;
            for (auto it = packages.begin(); it != packages.end(); it++)
            {
                auto i = *it;
                if (i == P1)
                {
                    if (i.isBuy == P1.isBuy)
                    {
                        if (P1.price * P1.isBuy <= i.price * i.isBuy)
                        {
                            flag = 1;
                            break;
                        }
                        else
                        {
                            packages.erase(it);
                            break;
                        }
                    }
                    else if (i.isBuy + P1.isBuy == 0)
                    {
                        if (i.price == P1.price)
                        {
                            flag = 1;
                            packages.erase(it);
                            break;
                        }
                    }
                }
            }
            if (flag)
            {
                std::cout << "No Trade" << std::endl;
                continue;
            }
            Package bestPackage;
            int maxProfit = 0;
            int n = packages.size();
            for (int i = 0; i < (1 << n); i++)
            {
                Package P = P1;
                P.indexes.push_back(n);
                for (int j = n - 1; j >= 0; j--)
                {
                    if ((i & (1 << j)) != 0)
                    {
                        P = P + packages[j];
                        P.indexes.push_back(j);
                    }
                }
                int check = P.isArbitrage();
                if (P.price > maxProfit && check)
                {
                    maxProfit = P.price;
                    bestPackage = P;
                }
            }
            packages.push_back(P1);
            if (bestPackage.indexes.size() == 0)
                std::cout << "No Trade" << std::endl;
            else
            {
                for (auto k : bestPackage.indexes)
                {
                    packages[k].printPackage();
                    char b = (packages[k].isBuy == 1) ? 's' : 'b';
                    std::cout << b << std::endl;
                    packages.erase(packages.begin() + k);
                }
                net_profit += bestPackage.price;
            }
        }
        std::cout << net_profit << std::endl;
    }
    else if (choice == '3')
    {
        vector<Package> packages;
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
                        P1.quantity += it->quantity;
                        P1.maxQuantity = P1.quantity + it->maxQuantity;
                        packages.erase(it);
                        flag = 0;
                        break;
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
                std::cout<<"No Trade"<<std::endl;
                get_max_sum(packages);
                continue;
            }

            if (!flag)
            {
                packages.push_back(P1);
            }

            vector<int> results;
            get_max_sum(packages);

            bool hasArbitrage = false;

            bool flag2 = false;
            net_profit += find_all_c(packages, results);
            int ind = results.size() - 1;
            for (int i = packages.size() - 1; i >= 0; i--)
            {
                if (results[ind] != 0)
                {
                    packages[i].printPackage();
                    char b;
                    b = (packages[i].isBuy == 1) ? 's' : 'b';
                    std::cout << results[ind] << " " << b << std::endl;
                    packages[i].quantity -= results[ind];
                    packages[i].maxQuantity = min(packages[i].maxQuantity, packages[i].quantity);
                    flag2 = true;
                    hasArbitrage = true;
                }
                ind--;
            }
            get_max_sum(packages);

            if (!hasArbitrage)
            {
                std::cout << "No Trade" << std::endl;
            }
        }
        std::cout << net_profit << std::endl;
    }
    return 0;
}