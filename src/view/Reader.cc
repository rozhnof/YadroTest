#include <view/Reader.h>
#include <sstream>
#include <stdexcept>
#include <string>

namespace view {

Reader::Reader(std::istream& is)
    : is_(is),
      pattern("^[0-9]{2}:[0-9]{2}[ ][0-9][ ][a-z0-9_-]*([ ][0-9]{1,})?$") {
}

bool Reader::ReadData() {
  try {
    ReadComputerClubData(is_);
    for (std::string str; std::getline(is_, str); ) {
        model::InputEvent event = ReadEvent(str);
        event_list_.push_back(std::move(event));
    }
  } catch (...) {
    return false;
  }
  return true;
}

std::vector<model::InputEvent> Reader::ExtractInputEventList() {
  return std::move(event_list_);
}

dto::ComputerClubData Reader::ExtractComputerClubData() {
  return std::move(data_);
}

std::string Reader::GetError() {
  return error_event_.value();
}

bool Reader::IsCorrectEventFormat(const std::string& str) {
  return std::regex_match(str, pattern);
}

void Reader::ReadComputerClubData(std::istream& is) {
  data_.table_count = std::stoull(GetToken(is));
  data_.work_time.start_time = ReadTime(is);
  data_.work_time.end_time = ReadTime(is);
  data_.cost_per_hour = std::stoull(GetToken(is));

  if (data_.table_count < 0) {
    throw std::invalid_argument("Table count cannot be negative");
  } 
}

model::InputEvent Reader::ReadEvent(std::string str) {
  if (!IsCorrectEventFormat(str)) {
    error_event_ = str;
    throw std::runtime_error("Incorrect event format");
  }

  std::stringstream ss(std::move(str));
  auto event_time = ReadTime(ss);
  auto event_id = ReadEventId(ss);
  auto client_id = ReadClientId(ss);
  std::optional<int> table_id;
  if (event_id == model::BaseEvent::Events::kClientTakeTable) {
    table_id = ReadTableId(ss);
  }

  return
      model::InputEvent::CreateEvent(event_time, event_id, client_id, table_id);
}

dto::Time Reader::ReadTime(std::istream& is) {
  std::size_t hour = std::stoull(GetToken(is));
  std::size_t minute = std::stoull(GetToken(is));

  if (hour >= 24) {
    throw std::invalid_argument("Provided hour is incorrect");
  } else if (minute >= 60) {
    throw std::invalid_argument("Provided minute is incorrect");
  } 

  return {hour, minute};
}

model::BaseEvent::Events Reader::ReadEventId(std::istream& is) {
  return IntToEventId(std::stoull(GetToken(is)));
}

std::string Reader::ReadClientId(std::istream& is) {
  return GetToken(is);
}

int Reader::ReadTableId(std::istream& is) {
  return std::stoull(GetToken(is));
}

std::string Reader::GetToken(std::istream& is) {
  std::string token;
  std::string delim_list = ": \n";

  for (char ch; is.get(ch);) {
    if (delim_list.find(ch) != std::string::npos) {
      break;
    }
    token += ch;
  }

  return token;
}

model::BaseEvent::Events Reader::IntToEventId(int event_id) {
  switch (static_cast<InputEvents>(event_id)) {
    case InputEvents::kClientEnter:
      return model::BaseEvent::kClientEnter;
    case InputEvents::kClientTakeTable:
      return model::BaseEvent::kClientTakeTable;
    case InputEvents::kClientWait:
      return model::BaseEvent::kClientWait;
    case InputEvents::kClientLeave:
      return model::BaseEvent::kClientLeave;
    default:
      throw std::runtime_error("Invalid value for event Id");
  }
}

}  // namespace view