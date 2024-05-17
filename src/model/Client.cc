#include <model/Client.h>

namespace model {

Client::Client(const ClientId& id)
    : id_(id) {
}

ClientId Client::GetId() const noexcept {
  return id_;
}

TableId Client::GetTableId() const {
  return table_id_.value();
}

bool Client::HasTable() const noexcept {
  return table_id_.has_value();
}

void Client::SetTable(TableId id) noexcept {
  table_id_ = id;
}

void Client::ResetTable() noexcept {
  table_id_.reset();
}

}  // namespace model
