#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

int XMAS_starting_in_place(const std::vector<std::string>& input, int row, int col) {
    int found = 0;
    // up
    if(
        row - 3 >= 0
        && input[row-0][col] == 'X'
        && input[row-1][col] == 'M'
        && input[row-2][col] == 'A'
        && input[row-3][col] == 'S'
        )
        found++;

    // up right
    if(
        row - 3 >= 0
        && col + 3 < input[0].size()
        && input[row-0][col+0] == 'X'
        && input[row-1][col+1] == 'M'
        && input[row-2][col+2] == 'A'
        && input[row-3][col+3] == 'S'
        )
        found++;

    // to the right
    if(
        col + 3 < input[0].size()
        && input[row][col+0] == 'X'
        && input[row][col+1] == 'M'
        && input[row][col+2] == 'A'
        && input[row][col+3] == 'S'
        )
        found++;

    // bottom right
    if(
        row + 3 < input.size()
        && col + 3 < input[0].size()
        && input[row+0][col+0] == 'X'
        && input[row+1][col+1] == 'M'
        && input[row+2][col+2] == 'A'
        && input[row+3][col+3] == 'S'
        )
        found++;

    // bottom
    if(
        row + 3 < input.size()
        && input[row+0][col] == 'X'
        && input[row+1][col] == 'M'
        && input[row+2][col] == 'A'
        && input[row+3][col] == 'S'
        )
        found++;

    // bottom left
    if(
        row + 3 < input.size()
        && col - 3 >= 0
        && input[row+0][col-0] == 'X'
        && input[row+1][col-1] == 'M'
        && input[row+2][col-2] == 'A'
        && input[row+3][col-3] == 'S'
        )
        found++;

    // to the left
    if(
        col - 3 >= 0
        && input[row][col-0] == 'X'
        && input[row][col-1] == 'M'
        && input[row][col-2] == 'A'
        && input[row][col-3] == 'S'
        )
        found++;

    // up left
    if(
        row - 3 >= 0
        && col - 3 >= 0
        && input[row-0][col-0] == 'X'
        && input[row-1][col-1] == 'M'
        && input[row-2][col-2] == 'A'
        && input[row-3][col-3] == 'S'
        )
        found++;
    return found;
}

int XMAS_around_place(const std::vector<std::string>& input, int row, int col) {
    if(input[row][col] != 'A') return 0;
    if(!(0 < row && row < input.size()-1)) return 0;
    if(!(0 < col && col < input[0].size()-1)) return 0;
    if(!(
        input[row-1][col-1] == 'M' && input[row+1][col+1] == 'S'
        || input[row-1][col-1] == 'S' && input[row+1][col+1] == 'M'
        )) return 0;

    if(!(
        input[row-1][col+1] == 'M' && input[row+1][col-1] == 'S'
        || input[row-1][col+1] == 'S' && input[row+1][col-1] == 'M'
        )) return 0;
    return 1;
}

int main()
{
    std::ifstream file("../input_04.txt");

    std::vector<std::string> lines;
    std::string line;
    while(std::getline(file, line)) {
        lines.emplace_back(std::move(line));
    }

    int found = 0;
    for(int row = 0; row < lines.size(); row++) {
        for(int col = 0; col < lines[0].size(); col++) {
            found += XMAS_around_place(lines, row, col);
        }
    }

    std::cout << found << std::endl;

    return 0;
}
