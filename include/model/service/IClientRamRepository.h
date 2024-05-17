#pragma once

#include <repository/RamRepository.h>
#include <model/Client.h>

namespace model::service {

class IClientRamRepository : public repository::RamRepository<model::Client> {
 public:
  virtual void AddClientToQueue(const model::ClientId&) = 0;
  virtual model::Client ExtractClientFromQueue() = 0;
  virtual bool EmptyQueue() const noexcept = 0;
  virtual int QueueSize() const noexcept = 0;
};

}  // namespace model::service