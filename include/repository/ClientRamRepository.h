#pragma once

#include <queue>
#include <model/Client.h>
#include <model/service/IClientRamRepository.h>

namespace repository {

class ClientRamRepository : public model::service::IClientRamRepository {
 public:
  void AddClientToQueue(const model::ClientId& client_id) override;
  model::Client ExtractClientFromQueue() override;
  bool EmptyQueue() const noexcept override;
  int QueueSize() const noexcept override;

 private:
  std::queue<model::ClientId> wait_queue_;
};

}  // namespace repository