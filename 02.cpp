#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>

bool is_safe(const std::vector<int>& report) {
    if(report.size() < 2) return false;
    bool increasing = false;
    if(report[0] < report[1]) {
        increasing = true;
    }

    for(int i = 1; i < report.size(); i++) {
        const int difference = report[i] - report[i-1];
        if(increasing) {
            if(!(1 <= difference && difference <= 3)) {
                return false;
            }
        } else {
            if(!(-3 <= difference && difference <= -1)) {
                return false;
            }
        }
    }

    return true;
}

bool is_safe(const std::string& report, bool tolerate_one_wrong = false) {
    std::istringstream iss(report);
    std::vector<int> numbers;
    int number;
    while (iss >> number) {
        numbers.push_back(number);
    }
    if(is_safe(numbers)) {
        return true;
    }
    if(tolerate_one_wrong) {
        for(int dropped = 0; dropped < numbers.size(); dropped++) {
            auto copy = numbers;
            copy.erase(copy.begin() + dropped);
            if(is_safe(copy)) {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    std::ifstream file("../input_02.txt");
    std::string report;

    int save_reports = 0;
    while (std::getline(file, report)){
        if(is_safe(report, true)) {
            save_reports++;
        } else {
            std::cout << report << " is not safe" << std::endl;
        }
    }

    std::cout << "The number of safe reports is " << save_reports << std::endl;
    return 0;
}
