#include <iostream>
#include <vector>

void find_all_c(const std::vector<int>& a, const std::vector<int>& b, std::vector<std::vector<int>>& results) {
    int n = a.size();
    
    std::vector<int> c(n, 0);
    c[n-1] = 1;
    while (true) {
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += a[i] * c[i];
        }

        if (sum == 0) {
            results.push_back(c);
            for (auto i : c) std::cout << i << " ";
            std::cout << std::endl;
        }

        // Increment the rightmost index
        int i = n - 1;
        while (i >= 0 && ++c[i] > b[i]) {
            c[i--] = 0;
        }

        // Check if we've finished iterating
        if (i < 0) {
            break;
        }
    }
}

int main() {
    std::vector<int> a = {2, -3, 2};
    std::vector<int> b = {4, 4, 4};
    std::vector<std::vector<int>> results;
    find_all_c(a, b, results);
    return 0;
}
