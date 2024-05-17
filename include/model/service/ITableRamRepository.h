#pragma once

#include <repository/RamRepository.h>
#include <model/Table.h>

namespace model::service {

class ITableRamRepository : public repository::RamRepository<model::Table> {
 public:
  virtual int GetTakedTableCount() const noexcept = 0;
  virtual void SetTableAsTaked(model::TableId) = 0;
  virtual void SetTableAsFree(model::TableId) = 0;
  virtual bool TableIsTaked(model::TableId) const noexcept = 0;
};

}  // namespace model::service