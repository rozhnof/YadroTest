#pragma once

#include <unordered_map>

namespace model::service {

template <typename Entity>
class IRamRepository {
 public:
  virtual void Add(Entity) = 0;
  virtual void Update(Entity) = 0;
  virtual Entity GetById(const typename Entity::Id&) const = 0;
  virtual void Remove(const typename Entity::Id&) = 0;
  virtual bool Exists(const typename Entity::Id&) = 0;
  virtual const std::unordered_map<typename Entity::Id, Entity>& GetAll()
      const noexcept = 0;
  virtual ~IRamRepository() = default;
};

}  // namespace model::service