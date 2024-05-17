#pragma once

#include <optional>
#include <model/ComputerClub.h>
#include <model/Client.h>
#include <model/Table.h>
#include <model/Event.h>
#include <DTO/Time.h>
#include <model/service/IClientRamRepository.h>
#include <model/service/ITableRamRepository.h>

namespace model::service {

class ComputerClubService {
 public:
  using IClientRepository = model::service::IClientRamRepository;
  using ITableRepository = model::service::ITableRamRepository;

  ComputerClubService(IClientRepository& client_repository,
                      ITableRepository& table_repository,
                      model::ComputerClub& computer_club);

  std::optional<model::OutputEvent> ClientEnter(
      const model::InputEvent& input_event);
  std::optional<model::OutputEvent> ClientTakeTable(
      const model::InputEvent& input_event);
  std::optional<model::OutputEvent> ClientWait(
      const model::InputEvent& input_event);
  std::optional<model::OutputEvent> ClientLeave(
      const model::InputEvent& input_event);
  std::vector<model::OutputEvent> LeaveAll();

 private:
  IClientRepository& client_repository_;
  ITableRepository& table_repository_;
  model::ComputerClub& computer_club_;

  void TakeTable(const model::ClientId& client_id, model::TableId table_id,
                 dto::Time time);
  void TakeTable(model::Client client, model::Table table, dto::Time time);
  void ReleaseTable(const model::ClientId& client_id, dto::Time time);
  void ReleaseTable(model::Client client, dto::Time time);

  model::OutputEvent ClientFromQueueTakeTable(model::TableId table_id,
                                              dto::Time event_time);
};

}  // namespace model::service