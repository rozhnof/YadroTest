#include <ComputerClub.h>
#include "model/Client.h"

void ComputerClubRun(std::istream& is, std::ostream& os) {
  view::Reader reader(is);
  view::Writer writer(os);

  if (!reader.ReadData()) {
    writer.WriteLine(reader.GetError());
    return;
  }

  auto computer_club_data = reader.ExtractComputerClubData();
  model::ComputerClub club(computer_club_data);

  repository::ClientRamRepository client_repository;
  repository::TableRamRepository table_repository;

  model::service::ComputerClubService service(client_repository,
                                              table_repository, club);
  controller::ComputerClubController controller(service);

  writer.WriteLine(computer_club_data.work_time.start_time);

  auto input_event_list = reader.ExtractInputEventList();
  for (auto& input_event : input_event_list) {
    std::optional output_event = controller.RunEvent(input_event);

    writer.WriteLine(input_event);
    if (output_event.has_value()) {
      writer.WriteLine(output_event.value());
    }
  }

  auto output_event_list = controller.CloseComputerClub();
  for (auto& output_event : output_event_list) {
    writer.WriteLine(output_event);
  }

  writer.WriteLine(computer_club_data.work_time.end_time);

  auto& table_hash_map = table_repository.GetAll();
  std::map<model::TableId, model::Table> table_map(table_hash_map.begin(),
                                                   table_hash_map.end());
  for (auto& [table_id, table] : table_map) {
    writer.WriteLine(table_id,
                     table.GetTotalProfit(computer_club_data.cost_per_hour),
                     table.GetTotalWorkTime());
  }
}