#include <model/Event.h>

namespace model {

dto::Time BaseEvent::GetTime() const noexcept {
  return time_;
}

BaseEvent::Events BaseEvent::GetId() const {
  return id_;
}

const std::string& BaseEvent::GetClientId() const {
  return client_id_;
}

int BaseEvent::GetTableId() const {
  return table_id_.value();
}

InputEvent InputEvent::CreateEvent(dto::Time time, Events event_id,
                                   std::string client_id,
                                   std::optional<int> table_id) {
  return BaseEvent::CreateEvent<InputEvent>(time, event_id, client_id,
                                            table_id);
}

OutputEvent OutputEvent::CreateEvent(dto::Time time, Events event_id,
                                     std::string client_id,
                                     std::optional<int> table_id) {
  return BaseEvent::CreateEvent<OutputEvent>(time, event_id, client_id,
                                             table_id);
}

OutputEvent OutputEvent::CreateErrorEvent(dto::Time time, std::string message) {
  OutputEvent event =
      BaseEvent::CreateEvent<OutputEvent>(time, Events::kError, "");
  event.error_message_ = message;
  return event;
}

std::string OutputEvent::GetErrorMessage() const {
  return error_message_.value();
}

}  // namespace model