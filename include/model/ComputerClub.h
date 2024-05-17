#pragma once

#include <DTO/ComputerClubData.h>

namespace model {

class ComputerClub {
 public:
  explicit ComputerClub(dto::ComputerClubData data);

  dto::Interval GetWorkTime() const noexcept;
  int GetCost() const noexcept;
  int GetTableCount() const noexcept;

 private:
  dto::ComputerClubData data_;
};

}  // namespace model
