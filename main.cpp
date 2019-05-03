#include <iostream>
#include <map>

int main()
{
    std::multimap<std::string, size_t> storeGoods {
        {"Apple", 2},
        {"Pear", 2},
        {"Apple", 7},
        {"Orange", 2},
        {"Apple", 9}
    };

    std::string searchKey {"Apple"};

    auto searchRange = storeGoods.equal_range(searchKey); // pair (lower_bound, upper_bound)
    if (searchRange.first == searchRange.second) {
        std::cout << "No element with key " << searchKey << std::endl;
    } else {
        std::cout << "Elements with key " << searchKey << std::endl;
        for (auto fruitIt = searchRange.first; fruitIt != searchRange.second; ++fruitIt) {
            std::cout << fruitIt->second << " ";
        }
    }

    std::cout << std::endl;

    return 0;
}
