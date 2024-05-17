#include <view/Writer.h>

namespace view {

Writer::Writer(std::ostream& os)
    : os_(os) {
}

std::string Writer::ToString(model::OutputEvent event) {
  auto event_time = event.GetTime();
  auto event_id = event.GetId();

  std::string str;

  str += ToString(event_time);
  str += " " + std::to_string(OutputEventIdToInt(event_id));

  if (event_id == model::OutputEvent::kClientLeave) {
    str += " " + event.GetClientId();
  } else if (event_id == model::OutputEvent::kClientTakeTable) {
    str += " " + event.GetClientId() + " " + std::to_string(event.GetTableId());
  } else if (event_id == model::OutputEvent::kError) {
    str += " " + event.GetErrorMessage();
  }

  return str;
}

std::string Writer::ToString(model::InputEvent event) {
  auto event_id = event.GetId();

  std::string str;
  str += ToString(event.GetTime());
  str += " " + std::to_string(InputEventIdToInt(event_id));
  str += " " + event.GetClientId();

  if (event_id == model::InputEvent::kClientTakeTable) {
    str += " " + std::to_string(event.GetTableId());
  }

  return str;
}

int Writer::OutputEventIdToInt(model::BaseEvent::Events event_id) {
  switch (event_id) {
    case model::BaseEvent::kClientLeave:
      return static_cast<int>(OutputEvents::kClientLeave);
    case model::BaseEvent::kClientTakeTable:
      return static_cast<int>(OutputEvents::kClientTakeTable);
    case model::BaseEvent::kError:
      return static_cast<int>(OutputEvents::kError);
    default:
      throw std::runtime_error("Invalid output event Id");
  }
}

int Writer::InputEventIdToInt(model::BaseEvent::Events event_id) {
  switch (event_id) {
    case model::BaseEvent::kClientEnter:
      return static_cast<int>(InputEvents::kClientEnter);
    case model::BaseEvent::kClientTakeTable:
      return static_cast<int>(InputEvents::kClientTakeTable);
    case model::BaseEvent::kClientWait:
      return static_cast<int>(InputEvents::kClientWait);
    case model::BaseEvent::kClientLeave:
      return static_cast<int>(InputEvents::kClientLeave);
    default:
      throw std::runtime_error("Invalid input event Id");
  }
}

std::string Writer::ToString(dto::Time time) {
  std::stringstream ss;
  ss << std::setw(2) << std::setfill('0');
  ss << time.hour;
  ss << ':';
  ss << std::setw(2) << std::setfill('0');
  ss << time.minute;
  return ss.str();
}

}  // namespace view