#pragma once

#include <stdexcept>
#include <model/service/IRamRepository.h>

namespace repository {

template <typename Entity>
requires requires {
  typename Entity::Id;
}
class RamRepository : public model::service::IRamRepository<Entity> {
 public:
  void Add(Entity entity) override {
    entity_list_.emplace(entity.GetId(), std::move(entity));
  }

  void Update(Entity entity) override {
    auto entity_it = entity_list_.find(entity.GetId());
    if (entity_it == entity_list_.end()) {
      throw std::runtime_error("Update failed");
    }
    entity_it->second = std::move(entity);
  }

  Entity GetById(const typename Entity::Id& id) const override {
    auto table_it = entity_list_.find(id);
    if (table_it == entity_list_.end()) {
      throw std::runtime_error("Get failed");
    }
    return table_it->second;
  }

  void Remove(const typename Entity::Id& id) override {
    auto table_it = entity_list_.find(id);
    if (table_it == entity_list_.end()) {
      throw std::runtime_error("Remove failed");
    }
    entity_list_.erase(table_it);
  }

  bool Exists(const typename Entity::Id& id) override {
    auto table_it = entity_list_.find(id);
    return table_it != entity_list_.end();
  }

  const std::unordered_map<typename Entity::Id, Entity>& GetAll()
      const noexcept override {
    return entity_list_;
  }

 private:
  std::unordered_map<typename Entity::Id, Entity> entity_list_;
};

}  // namespace repository