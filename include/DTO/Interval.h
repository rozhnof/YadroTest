#pragma once

#include "DTO/Time.h"

namespace dto {

struct Interval {
  Time start_time;
  Time end_time;

  bool IncludeTime(Time time) const noexcept {
    return time >= start_time && time <= end_time;
  }

  Time GetIntervalTime() const noexcept {
    return end_time - start_time;
  }
};

}  // namespace dto