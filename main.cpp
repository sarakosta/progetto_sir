#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "sir.hpp"

void print(State const& state, int duration_in_days) {
  auto N = state.s + state.i + state.r;
  std::cout << "│ " << std::setw(7) << std::setprecision(0) << duration_in_days
            << " │ " << std::setw(7) << std::setprecision(0)
            << std::round(state.s) << " │ " << std::setw(7)
            << std::setprecision(0) << std::round(state.i) << " │ "
            << std::setw(7) << std::setprecision(0)
            << N - std::round(state.s) - std::round(state.i) << " │\n";
}

int main() {
  auto beginning = []() { std::cout << "Enter initial state" << '\n'; };
  beginning();
  State state;  // initial state
  std::cin >> state.s >> state.i >> state.r;
  try {
    if (state.s <= 0 || state.i <= 0 || state.r < 0) {
      throw std::range_error(
          "The program can only accept integer values the initial state");
    }
  } catch (std::range_error const& e) {
    std::cout << e.what() << '\n';
    return EXIT_FAILURE;
  }

  auto par = []() { std::cout << "Enter parameters beta and gamma" << '\n'; };
  par();
  double beta;
  double gamma;
  std::cin >> beta >> gamma;
  try {
    if (beta <= 0 || beta >= 1 || gamma <= 0 || gamma >= 1) {
      throw std::range_error(
          "The program can only accept values that are between 0 and 1 for "
          "the parameters");
    }
  } catch (std::range_error const& e) {
    std::cout << e.what() << '\n';
    return EXIT_FAILURE;
  }

  auto time = []() { std::cout << "Enter time duration" << '\n'; };
  time();
  int duration_in_days;
  std::cin >> duration_in_days;
  try {
    bool t = duration_in_days >= 0;
    if (t == false) {
      throw std::range_error(
          "The simulation can't start: the duration has to be expressed "
          "using an integer");
    }
  } catch (std::range_error const& e) {
    std::cout << e.what() << '\n';
    return EXIT_FAILURE;
  }

  Epidemic sir{state, duration_in_days};

  std::ofstream file_s;
  std::ofstream file_i;
  std::ofstream file_r;
  file_s.open("file_s.dat");
  file_i.open("file_i.dat");
  file_r.open("file_r.dat");
  file_s << state.s << '\n';
  file_i << state.i << '\n';
  file_r << state.r << '\n';

  std::cout << "┌─────────┬─────────┬─────────┬─────────┐\n"
               "│   day   │    s    │    i    │    r    │\n"
               "├─────────┼─────────┼─────────┼─────────┤\n"
            << std::fixed;
  print(state, 0);  // print initial state - day 0
  int N = state.s + state.i + state.r;
  for (int j = 1; j <= duration_in_days; ++j) {
    State new_state = sir.generation(state, duration_in_days, beta, gamma);
    print(new_state, j);
    file_s << std::round(new_state.s) << '\n';
    file_i << std::round(new_state.i) << '\n';
    file_r << std::round(N - new_state.s - new_state.i) << '\n';
  }
  std::cout << "└─────────┴─────────┴─────────┴─────────┘\n";

  file_s.close();
  file_i.close();
  file_r.close();
}