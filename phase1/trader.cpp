#include "receiver.h"
#include "map.h"
#include <vector>
#include <string>
#include "Stock.h"


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
                if(stocks.search(curr).hasBestBuying)
                {
                    if(stoi(order[1]) >= stocks.search(curr).bestBuying)
                    {
                        std::cout << "No trade" << "\r\n";
                        continue;
                    }
                }
                if (stocks.search(curr).hasBestSelling)
                {
                    if (stoi(order[1]) == stocks.search(curr).bestSelling)
                    {
                        std::cout << "No trade"
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
                        std::cout << "No trade"
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
                if(stocks.search(curr).hasBestSelling)
                {
                    if(stoi(order[1]) <= stocks.search(curr).bestSelling)
                    {
                        std::cout << "No trade" << "\r\n";
                        continue;
                    }
                }
                if (stocks.search(curr).hasBestBuying)
                {
                    if (stoi(order[1]) == stocks.search(curr).bestBuying)
                    {
                        std::cout << "No trade"
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
                        std::cout << "No trade"
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
    return 0;
}