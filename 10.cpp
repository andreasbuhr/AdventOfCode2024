#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

struct position {
    int x;
    int y;
    friend bool operator<(const position &a, const position &b) {
        if (a.x == b.x)
            return a.y < b.y;
        return a.x < b.x;
    }
    friend bool operator==(const position &a, const position &b) { return a.x == b.x && a.y == b.y; }
};

bool all_reachable_nine(const std::vector<std::vector<int8_t>> &map, const std::deque<position> &reachable) {
    for (const auto &p: reachable) {
        if (map[p.x][p.y] != 9)
            return false;
    }
    return true;
}

typedef std::vector<position> trail;

int score(const std::vector<std::vector<int8_t>> &map, int row_trail_head, int col_trail_head) {
    if (map[row_trail_head][col_trail_head] != 0) {
        return 0;
    }
    std::deque<trail> unfinished_trails;
    std::vector<trail> finished_trails;
    unfinished_trails.push_back(trail({}));
    unfinished_trails.back().emplace_back(row_trail_head, col_trail_head);

    while (!unfinished_trails.empty()) {
        trail to_process = unfinished_trails.front();
        unfinished_trails.pop_front();

        if (map[to_process.back().x][to_process.back().y] == 9) {
            finished_trails.emplace_back(to_process);
            continue;
        } else {
            int current_height = map[to_process.back().x][to_process.back().y];

            // left
            if (to_process.back().x > 0) {
                if (map[to_process.back().x - 1][to_process.back().y] == current_height + 1) {
                    auto copy = to_process;
                    copy.emplace_back(to_process.back().x - 1, to_process.back().y);
                    unfinished_trails.emplace_back(copy);
                }
            }

            // right
            if (to_process.back().x + 1 < map[0].size()) {
                if (map[to_process.back().x + 1][to_process.back().y] == current_height + 1) {
                    auto copy = to_process;
                    copy.emplace_back(to_process.back().x + 1, to_process.back().y);
                    unfinished_trails.emplace_back(copy);
                }
            }

            // top
            if (to_process.back().y > 0) {
                if (map[to_process.back().x][to_process.back().y - 1] == current_height + 1) {
                    auto copy = to_process;
                    copy.emplace_back(to_process.back().x, to_process.back().y - 1);
                    unfinished_trails.emplace_back(copy);
                }
            }

            // bottom
            if (to_process.back().y + 1 < map.size()) {
                if (map[to_process.back().x][to_process.back().y + 1] == current_height + 1) {
                    auto copy = to_process;
                    copy.emplace_back(to_process.back().x, to_process.back().y + 1);
                    unfinished_trails.emplace_back(copy);
                }
            }
        }

        std::sort(unfinished_trails.begin(), unfinished_trails.end());
        unfinished_trails.erase(std::unique(unfinished_trails.begin(), unfinished_trails.end()),
                                unfinished_trails.end());
    }

    return finished_trails.size();
}

int main() {
    std::ifstream file("../input_10.txt");
    std::string line;

    std::vector<std::vector<int8_t>> map;

    while (std::getline(file, line)) {
        map.emplace_back();
        for (const auto &c: line) {
            if (c == '.')
                map.back().emplace_back(-1);
            else
                map.back().push_back(c - '0');
        }
    }

    int sum_score = 0;
    for (int rowTrailHead = 0; rowTrailHead < map.size(); ++rowTrailHead) {
        for (int colTrailHead = 0; colTrailHead < map[0].size(); ++colTrailHead) {
            sum_score += score(map, rowTrailHead, colTrailHead);
        }
    }

    std::cout << sum_score;


    return 0;
}
