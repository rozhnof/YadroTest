#pragma once

#include <unordered_set>
#include <model/Table.h>
#include <model/service/ITableRamRepository.h>

namespace repository {

class TableRamRepository : public model::service::ITableRamRepository {
 public:
  int GetTakedTableCount() const noexcept override;
  void SetTableAsTaked(model::TableId table_id) override;
  void SetTableAsFree(model::TableId table_id) override;
  bool TableIsTaked(model::TableId table_id) const noexcept override;

 private:
  std::unordered_set<model::TableId> taked_table_list_;
};

}  // namespace repository