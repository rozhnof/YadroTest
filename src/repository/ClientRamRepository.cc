#include <repository/ClientRamRepository.h>

namespace repository {

void ClientRamRepository::AddClientToQueue(const model::ClientId& client_id) {
  wait_queue_.push(client_id);
}

model::Client ClientRamRepository::ExtractClientFromQueue() {
  auto& client_list = GetAll();
  auto client_id = wait_queue_.front();
  auto client = client_list.find(client_id)->second;
  wait_queue_.pop();
  return client;
}

bool ClientRamRepository::EmptyQueue() const noexcept {
  return wait_queue_.empty();
}

int ClientRamRepository::QueueSize() const noexcept {
  return wait_queue_.size();
}

}  // namespace repository