#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

enum DIR { UP, DOWN, LEFT, RIGHT };
struct position {
  int x;
  int y;
  friend bool operator<(const position &lhs, const position &rhs) {
    if (lhs.x == rhs.x)
      return lhs.y < rhs.y;
    return lhs.x < rhs.x;
  }
};

struct state {
  position pos;
  DIR dir;
  friend bool operator<(const state &lhs, const state &rhs) {
    if (lhs.pos < rhs.pos)
      return true;
    if (rhs.pos < lhs.pos)
      return false;
    return lhs.dir < rhs.dir;
  }
};

// returns whether we have a loop
bool do_walk(state current_state,
             const std::vector<std::vector<bool>> &obstructions) {

  std::set<state> visited_states;

  size_t iteration = 0;
  while (true) {
    iteration++;
    // log every thousands state.
    // No need to log every state in a loop
    if(iteration % 1000 == 0)
      visited_states.insert(current_state);

    auto next_state = current_state;
    if (next_state.dir == DIR::UP)
      next_state.pos.x--;
    if (next_state.dir == DIR::DOWN)
      next_state.pos.x++;
    if (next_state.dir == DIR::LEFT)
      next_state.pos.y--;
    if (next_state.dir == DIR::RIGHT)
      next_state.pos.y++;

    // are we out?
    if (next_state.pos.x < 0 || next_state.pos.y < 0 ||
        next_state.pos.x >= obstructions.size() ||
        next_state.pos.y >= obstructions[0].size())
      break;

    // are we obstructed?
    if (obstructions[next_state.pos.x][next_state.pos.y]) {
      // abort moving, start turning
      next_state = current_state;
      if (next_state.dir == DIR::UP)
        next_state.dir = DIR::RIGHT;
      else if (next_state.dir == DIR::DOWN)
        next_state.dir = DIR::LEFT;
      else if (next_state.dir == DIR::LEFT)
        next_state.dir = DIR::UP;
      else if (next_state.dir == DIR::RIGHT)
        next_state.dir = DIR::DOWN;
    }

    // in field and not obstructed: move!
    current_state = next_state;
    if (visited_states.find(current_state) != visited_states.end()) {
      // found a loop
      return true;
    }
    //visited_positions.insert(current_state.pos);
  }

  // std::cout << visited_positions.size() << std::endl;
  return false;
}
int main() {
  std::ifstream file("../input_06.txt");

  position start_position = {0, 0};
  DIR start_direction = DIR::UP;

  // read file
  std::vector<std::vector<bool>> obstructions;
  std::string line;
  while (std::getline(file, line)) {
    std::vector<bool> o;
    for (const char c : line) {
      if (c == 'v' || c == '^' || c == '<' || c == '>') {
        start_position = {(int)obstructions.size(), (int)o.size()};
        if (c == 'v') {
          start_direction = DIR::DOWN;
        }
        if (c == '^') {
          start_direction = DIR::UP;
        }
        if (c == '<') {
          start_direction = DIR::LEFT;
        }
        if (c == '>') {
          start_direction = DIR::RIGHT;
        }
        o.push_back(false);
      } else if (c == '#') {
        o.push_back(true);
      } else {
        o.push_back(false);
      }
    }
    obstructions.push_back(o);
  }

  state start_state = {start_position, start_direction};

  int loops_found = 0;
  for (int row = 0; row < obstructions.size(); row++) {
    for (int col = 0; col < obstructions[0].size(); col++) {
      if (obstructions[row][col]) {
        continue; // there is already something
      }
      if (row == start_position.x && col == start_position.y) {
        continue;
        ; // there is the guard
      }
      auto obstructions_copy = obstructions;
      obstructions_copy[row][col] = true;
      if (do_walk(start_state, obstructions_copy)) {
        loops_found++;
      }
    }
  }

  std::cout << loops_found << std::endl;
  return 0;
}
