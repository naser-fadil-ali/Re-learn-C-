#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1,2,5,4,3};

    std::sort(numbers.begin(), numbers.end());

    std::cout << "Sorted: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}



