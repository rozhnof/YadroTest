#include <model/ComputerClub.h>

namespace model {

ComputerClub::ComputerClub(dto::ComputerClubData data)
    : data_(data) {
}

dto::Interval ComputerClub::GetWorkTime() const noexcept {
  return data_.work_time;
}

int ComputerClub::GetCost() const noexcept {
  return data_.cost_per_hour;
}

int ComputerClub::GetTableCount() const noexcept {
  return data_.table_count;
}

}  // namespace model
