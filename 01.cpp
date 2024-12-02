#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

int main()
{
    std::ifstream file("../input_01.txt");
    std::vector<int> first_list, second_list;
    std::map<int, int> counter;
    int a,b;
    while(file >> a >> b) {
        first_list.push_back(a);
        second_list.push_back(b);
        counter[b]++;
    }
    std::ranges::sort(first_list);
    std::ranges::sort(second_list);

    size_t difference = 0;
    size_t similarity = 0;
    for(size_t i = 0; i < first_list.size(); ++i) {
        difference += std::abs(first_list[i] - second_list[i]);
        similarity += first_list[i] * counter[first_list[i]];
    }

    std::cout << "The total difference is " << difference << std::endl;
    std::cout << "The similarity score is " << similarity << std::endl;
    return 0;
}
