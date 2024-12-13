#include <algorithm>
#include <cassert>
#include <chrono>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <vector>

struct vector {
    long double x1;
    long double x2;
};

vector operator*(long double v1, vector v2) {
    v2.x1 *= v1;
    v2.x2 *= v1;
    return v2;
}

vector operator+(vector v1, vector v2) {
    return {v1.x1 + v2.x1, v2.x2 + v1.x2};
}

vector operator-(vector v1, vector v2) {
    return {v1.x1 - v2.x1, v2.x2 - v1.x2};
}

struct matrix {
    long double x11;
    long double x12;
    long double x21;
    long double x22;
};

int main() {
    std::ifstream file("../input_13.txt");
    std::string line;

    size_t required_tokens = 0;
    while (std::getline(file, line)) {
        // skip empty liens
        while (line.empty()) {
            if (!std::getline(file, line)) {
                break;
            }
        }

        // parse A line
        std::regex regexA("Button A[:] X[+](\\d+), Y[+](\\d+)");
        std::smatch matchA;
        std::regex_match(line, matchA, regexA);

        if (!matchA.size()) {
            std::cout << "A did not match: " << line << std::endl;
        }
        vector a {std::stold(matchA[1]), std::stold(matchA[2])};

        // parse b line
        std::getline(file, line);
        std::regex regexB("Button B[:] X[+](\\d+), Y[+](\\d+)");
        std::smatch matchB;
        std::regex_match(line, matchB, regexB);

        if (!matchB.size()) {
            std::cout << "B did not match: " << line << std::endl;
        }
        vector b {std::stold(matchB[1]), std::stold(matchB[2])};

        // parse price position
        std::getline(file, line);
        std::regex regexP("Prize[:] X[=](\\d+), Y[=](\\d+)");
        std::smatch matchP;
        std::regex_match(line, matchP, regexP);

        if (!matchP.size()) {
            std::cout << "P did not match: " << line << std::endl;
        }
        vector p {std::stold(matchP[1]), std::stold(matchP[2])};

        // for part two
        p.x1 += 10000000000000;
        p.x2 += 10000000000000;

        // construct basis change matrix
        matrix new_to_old;
        new_to_old.x11 = a.x1;
        new_to_old.x21 = a.x2;
        new_to_old.x12 = b.x1;
        new_to_old.x22 = b.x2;

        // do matrix inversion
        double division = new_to_old.x11 * new_to_old.x22 - new_to_old.x12 * new_to_old.x21;
        matrix old_to_new;
        old_to_new.x11 = new_to_old.x22 / division;
        old_to_new.x21 = - new_to_old.x21 / division;
        old_to_new.x12 = - new_to_old.x12 / division;
        old_to_new.x22 = new_to_old.x11 / division;

        // do matrix vector
        // old_to_new * price
        vector price_in_new_basis;
        price_in_new_basis.x1 = old_to_new.x11 * p.x1 + old_to_new.x12 * p.x2;
        price_in_new_basis.x2 = old_to_new.x21 * p.x1 + old_to_new.x22 * p.x2;

        // check if position in new base is integer
        if (std::abs(price_in_new_basis.x1 - std::round(price_in_new_basis.x1)) < 0.1) {
            if (std::abs(price_in_new_basis.x2 - std::round(price_in_new_basis.x2)) < 0.1) {
                // both more or less integer
                int64_t buttonapresses = std::round(price_in_new_basis.x1);
                int64_t buttonbpresses = std::round(price_in_new_basis.x2);

                if (buttonapresses > 100 || buttonbpresses > 100) {
                    // remove for part two
                    //continue; // as per definition
                }
                if (buttonbpresses < 0 || buttonbpresses < 0 ) {
                    continue;
                }

                std::cout << std::endl;
                std::cout << "found it: " << std::endl;
                std::cout << buttonapresses << " button a presses" << std::endl;
                std::cout << buttonbpresses << " button b presses" << std::endl;
                auto x = buttonapresses * a + buttonbpresses * b;
                std::cout << "we are at " << x.x1 << ", " << x.x2 << std::endl;
                std::cout << "price is at " << p.x1 << ", " << p.x2 << std::endl;
                auto offset = x - p;
                if (offset.x1 > 0.1 || offset.x2 > 0.1) {
                    continue;
                }


                required_tokens += 3*buttonapresses + buttonbpresses;
            }
        }
    }

    std::cout << "required tokens: " << required_tokens << std::endl;


    return 0;
}
