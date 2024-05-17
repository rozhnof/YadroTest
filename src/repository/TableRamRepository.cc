#include <repository/TableRamRepository.h>

namespace repository {

int TableRamRepository::GetTakedTableCount() const noexcept {
  return taked_table_list_.size();
}

void TableRamRepository::SetTableAsTaked(model::TableId table_id) {
  taked_table_list_.emplace(table_id);
}

void TableRamRepository::SetTableAsFree(model::TableId table_id) {
  taked_table_list_.erase(table_id);
}

bool TableRamRepository::TableIsTaked(model::TableId table_id) const noexcept {
  return taked_table_list_.contains(table_id);
}

}  // namespace repository