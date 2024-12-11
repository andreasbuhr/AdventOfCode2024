#include <algorithm>
#include <cassert>
#include <chrono>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

std::vector<uint64_t> blink(const std::vector<uint64_t>& stones) {
    static std::map<uint64_t, std::vector<uint64_t>> map;
    std::vector<uint64_t> result;
    result.reserve(stones.size()*2);
    for(const auto& stone : stones) {
        if(map.find(stone) == map.end()) {
            if(stone == 0) {
                map[0] = {1};
            } else if (auto s = std::to_string(stone); s.size() % 2 == 0) {
                auto first = (std::stoull(std::string(s.begin(), s.begin() + s.size() / 2)));
                auto second = (std::stoull(std::string(s.begin() + s.size() / 2, s.end())));
                map[stone] = {first, second};
            } else {
                map[stone] = {stone * 2024};
            }
        }
        const auto& vec = map.at(stone);
        result.insert(result.end(), vec.begin(), vec.end());
    }
    return result;
}

uint64_t how_many_becomes(uint64_t stone, int blinks) {
    static std::map<std::pair<uint64_t, int>, uint64_t> map;
    auto key = std::make_pair(stone, blinks);
    auto it = map.find(key);
    if(it == map.end()) {
        if(blinks > 5) {
            std::vector<uint64_t> stones = {stone};
            for(size_t i = 0; i < 5; ++i) {
                stones = blink(stones);
            }
            uint64_t stone_count = 0;
            for(size_t i = 0; i < stones.size(); ++i) {
                stone_count += how_many_becomes(stones[i], blinks - 5);
            }
            map.insert({key, stone_count});
        } else {
            std::vector<uint64_t> stones = {stone};
            for(size_t i = 0; i < blinks; ++i) {
                stones = blink(stones);
            }
            map.insert({key, stones.size()});
        }
        return map[key];
    } else {
        return it->second;
    }
}

int main() {
    std::ifstream file("../input_11.txt");
    std::string line;
    std::getline(file, line);
    std::vector<uint64_t> stones;
    std::istringstream iss(line);
    std::string stone;
    while (std::getline(iss, stone, ' ')) {
        stones.push_back(std::stoull(stone));
    }

    auto starttime = std::chrono::high_resolution_clock::now();

    uint64_t stone_count = 0;
    for(size_t i = 0; i < stones.size(); ++i) {
        stone_count += how_many_becomes(stones[i], 75);
    }
    std::cout << stone_count << std::endl;
    auto endtime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = endtime - starttime;
    std::cout << "Calculation time: " << diff.count() << std::endl;

    return 0;
}
