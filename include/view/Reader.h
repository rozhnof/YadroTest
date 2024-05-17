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

class Reader {
 private:
  enum class InputEvents {
    kClientEnter = 1,
    kClientTakeTable = 2,
    kClientWait = 3,
    kClientLeave = 4
  };

 public:
  explicit Reader(std::istream& is);

  bool ReadData();
  std::string GetError();

  std::vector<model::InputEvent> ExtractInputEventList();
  dto::ComputerClubData ExtractComputerClubData();

 private:
  bool IsCorrectEventFormat(const std::string& str);

  void ReadComputerClubData(std::istream& is);
  bool ReadEvent(std::string str, model::InputEvent& event);
  dto::Time ReadTime(std::istream& is);
  model::BaseEvent::Events ReadEventId(std::istream& is);
  std::string ReadClientId(std::istream& is);
  int ReadTableId(std::istream& is);
  std::string GetToken(std::istream& is);

  model::BaseEvent::Events IntToEventId(int event_id);

 private:
  std::istream& is_;
  const std::regex pattern;
  dto::ComputerClubData data_;
  std::vector<model::InputEvent> event_list_;
  std::optional<std::string> error_event_;
};

}  // namespace view