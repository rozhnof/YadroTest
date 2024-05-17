#pragma once

#include "DTO/Interval.h"

namespace dto {

struct ComputerClubData {
  Interval work_time;
  std::size_t cost_per_hour;
  std::size_t table_count;
};

}  // namespace dto