#pragma once

#include <model/Event.h>
#include <model/service/ComputerClubService.h>

namespace controller {

class ComputerClubController {
 public:
  explicit ComputerClubController(
      model::service::ComputerClubService& computer_club_service);

  std::optional<model::OutputEvent> RunEvent(model::InputEvent input_event);
  std::vector<model::OutputEvent> CloseComputerClub();

 private:
  model::service::ComputerClubService& computer_club_service_;
};

}  // namespace controller