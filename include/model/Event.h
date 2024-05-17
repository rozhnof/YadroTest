#pragma once

#include <DTO/Time.h>
#include <optional>
#include <string>

namespace model {

class BaseEvent {
 public:
  enum Events {
    kClientEnter,
    kClientTakeTable,
    kClientWait,
    kClientLeave,
    kError,
  };

  Events GetId() const;
  dto::Time GetTime() const noexcept;
  const std::string& GetClientId() const;
  int GetTableId() const;

  template <typename T>
  static T CreateEvent(dto::Time time, Events event_id, std::string client_id,
                       std::optional<int> table_id = std::nullopt) {
    T event;
    event.time_ = time;
    event.id_ = event_id;
    event.client_id_ = std::move(client_id);
    event.table_id_ = table_id;
    return event;
  }

 protected:
  dto::Time time_;
  Events id_;
  std::string client_id_;
  std::optional<int> table_id_;
};

class InputEvent : public BaseEvent {
 public:
  static InputEvent CreateEvent(dto::Time time, Events event_id,
                                std::string client_id,
                                std::optional<int> table_id = std::nullopt);
};

class OutputEvent : public BaseEvent {
 public:
  static OutputEvent CreateEvent(dto::Time time, Events event_id,
                                 std::string client_id,
                                 std::optional<int> table_id = std::nullopt);
  static OutputEvent CreateErrorEvent(dto::Time time, std::string message);
  std::string GetErrorMessage() const;

 private:
  std::optional<std::string> error_message_;
};

}  // namespace model