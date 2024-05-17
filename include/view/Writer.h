#pragma once

#include "DTO/Time.h"
#include "model/Event.h"
#include <istream>
#include <iostream>
#include <ostream>
#include <optional>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <string>
#include <DTO/ComputerClubData.h>

namespace view {

template <typename T>
concept HasOstream = requires(std::ostream& os, T&& t) {
  { os << t } -> std::same_as<std::ostream&>;
};

class Writer {
 private:
  enum class InputEvents {
    kClientEnter = 1,
    kClientTakeTable = 2,
    kClientWait = 3,
    kClientLeave = 4
  };

  enum class OutputEvents {
    kClientLeave = 11,
    kClientTakeTable = 12,
    kError = 13
  };

 public:
  explicit Writer(std::ostream& os);

  template <typename T, typename... Args>
  void WriteLine(T arg, Args&&... args) {
    Write(std::forward<T>(arg), std::forward<Args>(args)...);
    os_ << '\n';
  }

 private:
  std::ostream& os_;

  static std::string ToString(model::OutputEvent event);
  static std::string ToString(model::InputEvent event);
  static std::string ToString(dto::Time time);

  static int OutputEventIdToInt(model::BaseEvent::Events event_id);
  static int InputEventIdToInt(model::BaseEvent::Events event_id);

  template <typename T>
  void Write(T arg) {
    if constexpr (HasOstream<T>) {
      os_ << std::forward<T>(arg);
    } else {
      os_ << ToString(std::forward<T>(arg));
    }
  }

  template <typename T, typename... Args>
  void Write(T arg, Args&&... args) {
    Write(std::forward<T>(arg));
    os_ << ' ';
    Write(std::forward<Args>(args)...);
  }
};

}  // namespace view