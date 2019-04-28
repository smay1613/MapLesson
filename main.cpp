#include <iostream>
#include <map>
#include <utility>

struct BusInfo
{
    size_t number;
    size_t fare;
};

std::ostream& operator<<(std::ostream& stream, const BusInfo& info) {
    stream << "N: " << std::to_string(info.number) << " - F:" << std::to_string(info.fare);
    return stream;
}

struct GreaterComparator
{
    bool operator()(const int lhs, const int rhs)
    {
        return lhs > rhs;
    }
};

template<class K, class V, class C>
void printMap(const std::map<K, V, C>& setToPrint)
{
    for (const std::pair<K, V>& entry : setToPrint) {
        std::cout << "{" << entry.first << ", " << entry.second << "}" << " " << std::endl;
    }
    std::cout << std::endl;
}

void investigateConstructors()
{
    // <key type, value type, comparator>
    std::map<int, int, GreaterComparator> marksGreaterMap {{0, 1},
                                                           {20, 2},
                                                           {40, 3},
                                                           {60, 4},
                                                           {80, 5}
                                                          };
    // try to use upper_bound/lower_bound for mapping marks from 0-100 to 1-5 degree

    std::cout << "Marks greater map: " << std::endl;
    printMap(marksGreaterMap);
}

void investigateAccessOperations(std::map<std::string, BusInfo>& busSchedule)
{
    std::cout << "Bus number at 08:15: " << busSchedule["08:15"].number << std::endl; // [] returns reference to element with key

    // if key is not found, {key, mapped_type {}} is inserted (default value)
    // be careful with it!
    std::cout << "Bus number at 08:20: " << busSchedule["08:20"].number << " ....OOPS!" << std::endl;
    // replace it with correct version
    printMap(busSchedule);

    std::cout << "Bus number at 08:45: " << busSchedule.at("08:45").number << std::endl;

    try {
        std::cout << "Bus number at 08:50: " << busSchedule.at("08:50").number << std::endl;
        std::cout << "Will never get here." << std::endl;
    } catch (const std::out_of_range& exception) {
        std::cout << "We can't find that bus for you, because exception was thrown at: "
                  << exception.what() << std::endl;
    }
}

void investigateModifiers(std::map<std::string, BusInfo> busSchedule)
{
    busSchedule.insert(std::make_pair("08:00", BusInfo{100, 100})); // too verbose
    busSchedule.emplace("08:00", BusInfo {300, 300});
    // insert/emplace with hint is also available

    std::cout << "Map after insertion:" << std::endl;
    printMap(busSchedule);

    auto newBus = busSchedule.emplace("08:00", BusInfo {300, 20});
    std::cout << "Map after double insertion:" << std::endl;
    printMap(busSchedule);

    if (!newBus.second) { // if such key was already presented in container
        newBus.first->second.fare = 20; // (newBus.first) - part of newBus pair (iterator;bool),
                                        // (->second) - value of pair (key, value)
                                        // .fare - BusInfo member
    }
}

int main()
{
    investigateConstructors();

    std::map<std::string, BusInfo> busSchedule {
        {"08:15", BusInfo {504, 50}},
        {"08:30", BusInfo {505, 40}},
        {"08:45", BusInfo {104, 50}},
        {"09:40", BusInfo {105, 30}},
        {"11:20", BusInfo {107, 10}},
        {"11:35", BusInfo {108, 20}},
        {"11:50", BusInfo {109, 30}}
    };

    investigateAccessOperations(busSchedule);
    investigateModifiers(busSchedule);

    return 0;
}
