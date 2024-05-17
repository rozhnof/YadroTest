#include <model/Table.h>

namespace model {

Table::Table(TableId id)
    : id_(id) {
}

TableId Table::GetId() const noexcept {
  return id_;
}

const ClientId& Table::GetClientId() const {
  return client_id_.value();
}

bool Table::HasClient() const noexcept {
  return client_id_.has_value();
}

void Table::SetClient(ClientId id, dto::Time time) noexcept {
  work_time_list_.push_back(dto::Interval{time});
  client_id_ = id;
}

void Table::ResetClient(dto::Time time) noexcept {
  work_time_list_.back().end_time = time;
  client_id_.reset();
}

dto::Time Table::GetTotalWorkTime() const noexcept {
  dto::Time sum;

  for (auto& interval : work_time_list_) {
    sum = sum + interval.GetIntervalTime();
  }

  return sum;
}

std::size_t Table::GetTotalProfit(std::size_t cost_per_hour) const noexcept {
  std::size_t profit = 0;
  for (auto& interval : work_time_list_) {
    auto interval_time = interval.GetIntervalTime();
    auto hours = interval_time.hour + (interval_time.minute > 0);
    profit += (hours * cost_per_hour);
  }
  return profit;
}

}  // namespace model
