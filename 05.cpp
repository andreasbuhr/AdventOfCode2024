#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

int main()
{
    std::ifstream file("../input_05.txt");

    std::vector<std::string> lines;
    std::string line;
    std::set<std::pair<int, int>> orderings_set;
    std::vector<std::vector<int>> updates;

    while(std::getline(file, line)) {
        if(line.empty()) break;

        std::stringstream ss(line);
        std::string number1;
        std::getline(ss, number1, '|');
        std::string number2;
        std::getline(ss, number2);

        if(number1.empty() || number2.empty()) {
            std::cout << "Error in input" << std::endl;
        }
        orderings_set.insert(std::make_pair(stoi(number1), stoi(number2)));
    }

    while(std::getline(file, line)) {
        std::vector<int> update;
        std::stringstream ss(line);
        std::string number;
        while(std::getline(ss, number, ',')) {
            update.push_back(stoi(number));
        }
        updates.emplace_back(std::move(update));
    }

    size_t sum = 0;
    size_t wrong_sum = 0;
    for(auto& update : updates) {
        auto pred = [&](int i, int j) {
            if(orderings_set.find(std::make_pair(i,j)) != orderings_set.end()) {
                return true;
            }
            return false;
        };

        if(std::is_sorted(update.begin(), update.end(), pred)) {
            sum += update[update.size()/2];
        } else {
            std::sort(update.begin(), update.end(), pred);
            wrong_sum += update[update.size()/2];
        }
    }

    std::cout << sum << std::endl;
    std::cout << wrong_sum << std::endl;

    return 0;
}
