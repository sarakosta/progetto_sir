#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "sir.hpp"

#include <cassert>
#include <cmath>

#include "doctest.h"

TEST_CASE("testing that N is constant") {
  State state1{15, 10, 5};
  Epidemic sir{state1, 10};

  State state2 = sir.generation(state1, 10, 0.7, 0.2);

  {
    CHECK((state1.s + state1.i + state1.r) - (state2.s + state2.i + state2.r) ==
          doctest::Approx(0.));
  }
}

TEST_CASE("testing expansion") {
  State state1{20, 13, 8};
  Epidemic sir{state1, 15};

  State state2 = sir.generation(state1, 15, 0.7, 0.2);

  { CHECK((state1.r - state2.r) <= doctest::Approx(0.)); }

  { CHECK((state1.s - state2.s) >= doctest::Approx(0.)); }
}