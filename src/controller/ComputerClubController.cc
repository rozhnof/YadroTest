#include <controller/ComputerClubController.h>

namespace controller {

ComputerClubController::ComputerClubController(
    model::service::ComputerClubService& computer_club_service)
    : computer_club_service_(computer_club_service) {
}

std::optional<model::OutputEvent> ComputerClubController::RunEvent(
    model::InputEvent input_event) {
  std::optional<model::OutputEvent> output_event;

  auto event_id = input_event.GetId();
  if (event_id == model::InputEvent::kClientEnter) {
    output_event = computer_club_service_.ClientEnter(input_event);
  } else if (event_id == model::InputEvent::kClientTakeTable) {
    output_event = computer_club_service_.ClientTakeTable(input_event);
  } else if (event_id == model::InputEvent::kClientWait) {
    output_event = computer_club_service_.ClientWait(input_event);
  } else if (event_id == model::InputEvent::kClientLeave) {
    output_event = computer_club_service_.ClientLeave(input_event);
  }

  return output_event;
}

std::vector<model::OutputEvent> ComputerClubController::CloseComputerClub() {
  return computer_club_service_.LeaveAll();
}

}  // namespace controller