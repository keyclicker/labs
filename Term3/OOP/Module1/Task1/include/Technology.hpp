#pragma once
#include <set>
#include <string>

class Worker;
class Project;

class Technology {
private:
  std::string name;
  std::set<Worker*> workers;
  std::set<Project*> projects;

public:
  Technology(const std::string &name) : name(name) {}

  const std::string &getName() const {
    return name;
  }
  void setName(const std::string &name) {
    Technology::name = name;
  }

  void addWorker(Worker* worker) {
    workers.insert(worker);
  }
  void addProject(Project* project) {
    projects.insert(project);
  }

  const set<Worker *> &getWorkers() const {
    return workers;
  }
  const set<Project *> &getProjects() const {
    return projects;
  }

  bool operator==(const Technology &rhs) const {
    return name == rhs.name;
  }
  bool operator!=(const Technology &rhs) const {
    return !(rhs == *this);
  }

  friend std::ostream& operator<<(std::ostream& os, const Technology& t) {
    os << t.name;
    return os;
  }
};