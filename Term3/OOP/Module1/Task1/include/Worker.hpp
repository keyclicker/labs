#pragma once
#include <set>
#include <memory>
#include <string>

#include "Technology.hpp"
class Project;

class Worker {
private:
  std::string name;
  std::set<std::shared_ptr<Technology>> technologies;
  Project *project;

  float effectiveness;

public:
  Worker(const std::string &name = "worker", float effectiveness = 1):
         name(name), effectiveness(effectiveness) {}

  const std::string &getName() const {
    return name;
  }
  void setName(const std::string &name) {
    Worker::name = name;
  }

  void addTechnology(const std::shared_ptr<Technology> &technology) {
    technology->addWorker(this);
    technologies.insert(technology);
  }
  const set<std::shared_ptr<Technology>> &getTechnologies() const {
    return technologies;
  }

  Project *getProject() const {
    return project;
  }
  void setProject(Project *project) {
    Worker::project = project;
  }

  float getEffectiveness() const {
    return effectiveness;
  }
  void setEffectiveness(float effectiveness) {
    Worker::effectiveness = effectiveness;
  }

  friend std::ostream& operator<<(std::ostream& os, const Worker& w) {
    os << w.name << ' ' << w.effectiveness << ": ";
    for (auto &a : w.technologies) {
      os << *a << ", ";
    }
    return os;
  }
};

