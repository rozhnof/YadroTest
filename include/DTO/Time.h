#pragma once

#include <cstddef>

namespace dto {

struct Time {
  std::size_t hour = 0;
  std::size_t minute = 0;

  bool operator<=(Time other) const {
    return hour <= other.hour || (hour == other.hour && minute <= other.minute);
  }

  bool operator>=(Time other) const {
    return other <= *this;
  }

  Time operator-(Time other) const {
    return MinutesToTime(TimeToMinutes(*this) - other.TimeToMinutes(other));
  }

  Time operator+(Time other) const {
    return MinutesToTime(TimeToMinutes(*this) + other.TimeToMinutes(other));
  }

  static std::size_t TimeToMinutes(Time time) noexcept {
    return time.hour * 60 + time.minute;
  }

  static Time MinutesToTime(std::size_t minutes) noexcept {
    return Time{minutes / 60, minutes % 60};
  }
};

}  // namespace dto