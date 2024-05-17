#pragma once

#include <optional>
#include <vector>
#include <DTO/Time.h>
#include <DTO/Interval.h>
#include <model/Client.h>

namespace model {

using TableId = int;
using ClientId = std::string;

class Table {
 public:
  using Id = int;

  explicit Table(TableId id);

  TableId GetId() const noexcept;
  const ClientId& GetClientId() const;

  bool HasClient() const noexcept;
  void SetClient(ClientId id, dto::Time time) noexcept;
  void ResetClient(dto::Time time) noexcept;

  dto::Time GetTotalWorkTime() const noexcept;
  std::size_t GetTotalProfit(std::size_t cost_per_hour) const noexcept;

 private:
  TableId id_;
  std::vector<dto::Interval> work_time_list_;
  std::optional<ClientId> client_id_;
};

}  // namespace model
