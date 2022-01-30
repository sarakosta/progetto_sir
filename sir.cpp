#include "sir.hpp"

#include <cmath>
State Epidemic::generation(State& state, int duration_in_days, double beta,
                           double gamma) {
  int N = std::round(state.s + state.i + state.r);
  double s1 = state.s;
  double i1 = state.i;
  state.s *= 1 - (beta * i1 / N);
  state.i *= 1 + (beta * s1 / N) - gamma;
  state.r += gamma * i1;
  return state;
}