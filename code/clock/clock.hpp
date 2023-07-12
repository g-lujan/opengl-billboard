#pragma once

#include <SDL2/SDL.h>

struct Clock {
  Clock();
  void update_delta();
  float delta(){ return delta_; }

private:
  Uint64 now_;
  Uint64 last_;
  float delta_;
};

extern Clock CLOCK;