#pragma once

#include <string>
#include "model/Table.h"

namespace model {

using TableId = int;
using ClientId = std::string;

class Client {
 public:
  using Id = std::string;

  explicit Client(const ClientId& id);

  ClientId GetId() const noexcept;
  TableId GetTableId() const;

  bool HasTable() const noexcept;
  void SetTable(TableId id) noexcept;
  void ResetTable() noexcept;

 private:
  ClientId id_;
  std::optional<TableId> table_id_;
};

}  // namespace model
