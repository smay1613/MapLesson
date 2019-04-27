#include <iostream>
#include <set>
#include <utility>

class Student
{
public:
    Student() = default;
    /*explicit*/ Student(int mark) : m_averageMark {mark} {}

    int averageMark() const {
        return m_averageMark;
    }
private:
    int m_averageMark;
};

struct GreaterComparator
{
    bool operator()(const int lhs, const int rhs)
    {
        return lhs > rhs;
    }
};

bool someCustomComparator(const int lhs, const int rhs)
{
    return lhs / 2 < rhs / 2;
}

template<class T, class C>
void printSet(const std::set<T, C>& setToPrint)
{
    for (const T& entry : setToPrint) {
        std::cout << entry << " ";
    }
    std::cout << std::endl;
}

void investigateLookupOperations(std::set<std::string>& busSchedule)
{
    std::cout << "Number of buses at 8:15: " << busSchedule.count("08:15") << std::endl; // returns 0 or 1
    std::cout << "Number of buses at 8:00: " << busSchedule.count("08:00") << std::endl;

    std::cout << std::endl;

    auto targetBusTimeIt = busSchedule.find("11:50"); // returns end() iterator if no element found

    if (targetBusTimeIt != busSchedule.end()) {
        std::cout << "Target bus time found!" << std::endl;
    } else {
        std::cout << "No such bus for you..." << std::endl;
    }

    std::cout << std::endl;

    auto nearestBus = busSchedule.lower_bound("09:40"); // lower bound finds the greater than or equal, returns iterator or end()
    if (nearestBus != busSchedule.end()) {
        std::cout << "Nearest bus will be at... " << *nearestBus << std::endl;
    } else {
        std::cout << "Sorry, wait for tomorrow!" << std::endl;
    }

    std::cout << std::endl;

    auto nextBusAfter = busSchedule.upper_bound("09:40"); // greater than, but not equal; returns iterator or end()
    if (nearestBus != busSchedule.end()) {
        std::cout << "Next bus will be at... " << *nextBusAfter << std::endl;
    } else {
        std::cout << "Sorry, wait for tomorrow!" << std::endl;
    }

    std::cout << std::endl;

    std::pair<std::set<std::string>::iterator,
              std::set<std::string>::iterator> nearestAndNext = busSchedule.equal_range("09:30");
    // returns pair of iterators (lower_bound, upper_bound)

    if (nearestAndNext.first != busSchedule.begin()) {
        std::cout << "Nearest bus 1: " << *(--nearestAndNext.first) << std::endl;
    }
    if (nearestAndNext.second != busSchedule.end()) {
        std::cout << "Nearest bus 2: " << *nearestAndNext.second << std::endl;
    }

    std::cout << std::endl;
}

void investigateModifiers(std::set<std::string>& busSchedule)
{
    std::pair<std::set<std::string>::iterator,
              bool> insertResult = busSchedule.insert("20:00"); // adds value if unique
                                              /* or emplace */

    if (insertResult.second) { // result of insertion
        std::cout << *insertResult.first << " bus added! " << std::endl;
    } else {
        std::cout << *insertResult.first << " bus already exists!" << std::endl;
    }
    printSet(busSchedule);

    std::cout << std::endl;

    auto nearestBus = busSchedule.lower_bound("09:40");

    // The trick is that lower_bound returns the iterator where the key would be if it were in the set,
    // regardless of whether it actually is there.
    busSchedule.emplace_hint(nearestBus, "10:00");
    /* or busSchedule.insert(nearestBus, "10.00"); */
    std::cout << "Emplaced with hint: " << std::endl;
    printSet(busSchedule);
}

void investigateConstructors()
{
    std::set<int> marksSetFilled {1, 2, 3, 4, 5}; // by default, comparator is std::less (also <)

    std::cout << "Marks set filled: " << std::endl;
    printSet(marksSetFilled);

    std::set<int> assigningSet {marksSetFilled.begin(),
                                std::prev(marksSetFilled.end(), 2)}; // remind assigning constructor

    std::cout << "Assigned set: " << std::endl;
    printSet(assigningSet);

    std::set<int, GreaterComparator> marksGreaterSet {1, 2, 3, 4, 5};

    std::cout << "Marks greater set: " << std::endl;
    printSet(marksGreaterSet);

    auto customComparator = &someCustomComparator; // function or lambda
    std::set<int, decltype(customComparator)> marksCustomSet {customComparator}; // decltype allows to deduce customComparator type
    marksCustomSet = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    std::cout << "Some custom comparator via function:" << std::endl;
    printSet(marksCustomSet);

    auto markComparator = [](const Student& lhs, const Student& rhs) {
        return lhs.averageMark() < rhs.averageMark();
    };

    // NOTE: Student's constructor is not marked explicit, so we can use such "dangery" syntax.
    std::set<Student, decltype(markComparator)> studentsSet ({3, 5, 4}, markComparator);

    std::cout << "Student's marks: " << std::endl;
    for (const auto& student : studentsSet) {
        std::cout << student.averageMark() << " ";
    }
    std::cout << std::endl;
}

void investigateProperties()
{
    std::set<int> tryToNotUnique {1, 1, 2, 3, 5, 8, 13}; // Fibonacci numbers
    std::cout << "Only unique elements are added: " << std::endl;
    printSet(tryToNotUnique);
}

int main()
{
    investigateConstructors();
    investigateProperties();

    std::set<std::string> busSchedule {
        "08:15",
        "08:30",
        "08:45",
        "09:40",
        "11:20",
        "11:35",
        "11:50"
    };


    std::cout << std::endl << "Bus schedule: " << std::endl;
    printSet(busSchedule);

    std::cout << std::endl;

    investigateLookupOperations(busSchedule);
    investigateModifiers(busSchedule);

    return 0;
}
