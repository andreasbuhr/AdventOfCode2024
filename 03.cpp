#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <vector>

int main()
{
    std::ifstream file("../input_03.txt");
    std::string filecontent(std::istreambuf_iterator<char>{file}, {});
    std::regex regex("(mul[(]([0-9]+)[,]([0-9]+)[)])|(do(n[']t)?[(][)])");
    auto muls_iterator = std::sregex_iterator(filecontent.begin(), filecontent.end(), regex);
    auto muls_iterator_end = std::sregex_iterator();
    std::cout << "Found " << std::distance(muls_iterator, muls_iterator_end) << " matches.\n";

    int64_t sum = 0;
    bool disabled = false;
    for (auto i = muls_iterator; i != muls_iterator_end; ++i)
    {
        std::smatch match = *i;

        if(match.str() == "do()") {
            disabled = false;
            continue;
        }

        if(match.str() == "don't()") {
            disabled = true;
            continue;
        }

        if(disabled) continue;
        sum += std::stoi(match[2]) * std::stoi(match[3]);
    }
    std::cout << "Sum of products is " << sum << '\n';

    return 0;
}
