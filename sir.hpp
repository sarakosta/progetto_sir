#ifndef SIR_HPP
#define SIR_HPP

struct State {
  double s;
  double i;
  double r;
};

class Epidemic {
  State m_state;
  int m_duration;

 public:
  Epidemic(State& state, int duration_in_days)
      : m_state{state}, m_duration{duration_in_days} {}
  State generation(State& state, int duration_in_days, double beta,
                  double gamma);
};
#endif