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

int find_all_c(std::vector<Package>& packages, std::vector<int>& results) {
    int n = packages.size();
    int profit = 0;
    std::vector<int> c(n, 0);
    std::vector<int> ans(n, 0);
    c[n-1] = 0;
    while (true) {
        Package sum;
        for (int i = 0; i < n; ++i) {
            Package temp = packages[i] * c[i];
            sum = sum + temp;
            // sum.printPackage();
            // std::cout <<std::endl << "-----" << std::endl;
        }

        if (sum.isArbitrage() && sum.price > profit) {
            ans = c;
            profit = sum.price;
        }

        // Increment the rightmost index
        int i = n - 1;
        while (i >= 0 && ++c[i] > packages[i].maxQuantity) {
            c[i--] = 0;
        }

        // Check if we've finished iterating
        if (i < 0) {
            break;
        }
    }
    results = ans;
    return profit;
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
    int net_profit = 0;
    bool skip = false;
    for(auto ms : input){
        Package P1(ms);
        bool flag = 0;
        // std::cout << P1.quantity << std::endl;
        for(auto it = packages.begin(); it != packages.end(); it++){
            auto i = *it;
            if(i == P1 && i.price == P1.price){
                if(P1.isBuy == i.isBuy){
                    it->quantity += P1.quantity;
                    it->maxQuantity += P1.quantity;
                }else{
                    if(i.quantity > P1.quantity){
                        it->quantity -= P1.quantity;
                        skip = true;
                    }else{
                        P1.quantity = P1.quantity - i.quantity;
                        packages.erase(it);
                        if(P1.quantity!=0) {
                            flag = 0;
                            break;
                        }else{
                            skip = true;
                        }
                        
                    }
                }
                flag = 1;
                break;
            }
        }

        if(skip){
            skip = false;
            get_max_sum(packages);
            continue;
        }

        if(!flag) {
            packages.push_back(P1);
        }

        vector<int> results;
        get_max_sum(packages);

        // for(auto i : packages){
        //     std::cout << i.maxQuantity << " " << std::endl;
        // }

        bool hasArbitrage = false;

            bool flag2 = false;
            net_profit  +=  find_all_c(packages, results);
            int ind = results.size()-1;
            for(int i = packages.size()-1; i>=0; i--){
                if(results[ind]!=0){
                    packages[i].printPackage();
                    char b;
                    b = (packages[i].isBuy == 1) ? 's' : 'b';
                    std::cout << results[ind] << " " << b << std::endl;
                    packages[i].quantity -= results[ind];
                    packages[i].maxQuantity -= results[ind];
                    flag2 = true;
                    hasArbitrage = true;
                }
                ind--;
            }
            get_max_sum(packages);

        if(!hasArbitrage){
            std::cout << "No Trade" << std::endl;
        }

    }
    std::cout << net_profit << std::endl;
    return 0;
}