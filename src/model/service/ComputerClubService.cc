#include <model/service/ComputerClubService.h>
#include "model/Table.h"

namespace model::service {

ComputerClubService::ComputerClubService(IClientRepository& client_repository,
                                         ITableRepository& table_repository,
                                         model::ComputerClub& computer_club)
    : client_repository_(client_repository),
      table_repository_(table_repository),
      computer_club_(computer_club) {
  for (int i = 1; i < computer_club.GetTableCount(); ++i) {
    model::Table table(i);
    table_repository_.Add(std::move(table));
  }
}

std::optional<model::OutputEvent> ComputerClubService::ClientEnter(
    const model::InputEvent& input_event) {
  auto client_id = input_event.GetClientId();
  auto event_time = input_event.GetTime();

  if (!computer_club_.GetWorkTime().IncludeTime(event_time)) {
    return model::OutputEvent::CreateErrorEvent(input_event.GetTime(),
                                                "NotOpenYet");
  } else if (client_repository_.Exists(client_id)) {
    return model::OutputEvent::CreateErrorEvent(input_event.GetTime(),
                                                "YouShallNotPass");
  }

  model::Client new_client(std::move(client_id));
  client_repository_.Add(std::move(new_client));

  return std::nullopt;
}

std::optional<model::OutputEvent> ComputerClubService::ClientTakeTable(
    const model::InputEvent& input_event) {
  auto client_id = input_event.GetClientId();
  auto table_id = input_event.GetTableId();
  auto event_time = input_event.GetTime();

  if (!client_repository_.Exists(client_id)) {
    return model::OutputEvent::CreateErrorEvent(event_time, "ClientUnknown");
  } else if (table_repository_.TableIsTaked(table_id)) {
    return model::OutputEvent::CreateErrorEvent(event_time, "PlaceIsBusy");
  }

  if (!table_repository_.Exists(table_id)) {
    model::Table new_table(table_id);
    table_repository_.Add(new_table);
  }

  TakeTable(client_id, table_id, event_time);

  return std::nullopt;
}

std::optional<model::OutputEvent> ComputerClubService::ClientWait(
    const model::InputEvent& input_event) {
  auto client_id = input_event.GetClientId();

  if (table_repository_.GetTakedTableCount() < computer_club_.GetTableCount()) {
    return model::OutputEvent::CreateErrorEvent(input_event.GetTime(),
                                                "ICanWaitNoLonger!");
  } else if (client_repository_.QueueSize() > computer_club_.GetTableCount()) {
    client_repository_.Remove(client_id);
    return model::OutputEvent::CreateEvent(
        input_event.GetTime(), model::OutputEvent::Events::kClientLeave,
        client_id);
  }

  client_repository_.AddClientToQueue(client_id);

  return std::nullopt;
}

std::optional<model::OutputEvent> ComputerClubService::ClientLeave(
    const model::InputEvent& input_event) {
  auto client_id = input_event.GetClientId();
  auto event_time = input_event.GetTime();

  if (!client_repository_.Exists(client_id)) {
    return model::OutputEvent::CreateErrorEvent(event_time, "ClientUnknown");
  }

  std::optional<model::OutputEvent> output_event;
  auto client = client_repository_.GetById(client_id);

  if (client.HasTable()) {
    auto table_id = client.GetTableId();

    ReleaseTable(std::move(client), event_time);

    if (!client_repository_.EmptyQueue()) {
      output_event = ClientFromQueueTakeTable(table_id, event_time);
    }
  }

  client_repository_.Remove(client_id);

  return output_event;
}

std::vector<model::OutputEvent> ComputerClubService::LeaveAll() {
  auto event_time = computer_club_.GetWorkTime().end_time;
  auto& rem_client_list = client_repository_.GetAll();

  std::vector<model::OutputEvent> output;

  for (auto& [client_id, client] : rem_client_list) {
    if (client.HasTable()) {
      ReleaseTable(std::move(client), event_time);
    }
    output.push_back(model::OutputEvent::CreateEvent(
        event_time, model::OutputEvent::Events::kClientLeave,
        std::move(client_id)));
  }

  std::sort(output.begin(), output.end(),
            [](const model::OutputEvent& e1, const model::OutputEvent& e2) {
              return e1.GetClientId() < e2.GetClientId();
            });

  return output;
}

void ComputerClubService::TakeTable(const model::ClientId& client_id,
                                    model::TableId table_id, dto::Time time) {
  auto client = client_repository_.GetById(client_id);
  auto table = table_repository_.GetById(table_id);
  TakeTable(std::move(client), std::move(table), time);
}

void ComputerClubService::ReleaseTable(const model::ClientId& client_id,
                                       dto::Time time) {
  auto client = client_repository_.GetById(client_id);
  ReleaseTable(std::move(client), time);
}

void ComputerClubService::TakeTable(model::Client client, model::Table table,
                                    dto::Time time) {
  auto client_id = client.GetId();
  auto table_id = table.GetId();

  table_repository_.SetTableAsTaked(table_id);

  client.SetTable(table_id);
  table.SetClient(client_id, time);

  client_repository_.Update(std::move(client));
  table_repository_.Update(std::move(table));
}

void ComputerClubService::ReleaseTable(model::Client client, dto::Time time) {
  auto table_id = client.GetTableId();
  auto table = table_repository_.GetById(table_id);

  table_repository_.SetTableAsFree(table_id);

  client.ResetTable();
  table.ResetClient(time);

  client_repository_.Update(std::move(client));
  table_repository_.Update(std::move(table));
}

model::OutputEvent ComputerClubService::ClientFromQueueTakeTable(
    model::TableId table_id, dto::Time event_time) {
  auto client = client_repository_.ExtractClientFromQueue();
  auto table = table_repository_.GetById(table_id);
  auto client_id = client.GetId();

  TakeTable(std::move(client), std::move(table), event_time);

  return model::OutputEvent::CreateEvent(
      event_time, model::OutputEvent::Events::kClientTakeTable, client_id,
      table_id);
}

}  // namespace model::service