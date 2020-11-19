#pragma once
#include <set>
#include <list>
#include <memory>

#include "Worker.hpp"

class Technology;
class Company;

class Project {
private:
  std::string name;
  std::set<std::unique_ptr<Worker>> workers;
  std::set<std::shared_ptr<Technology>> technologies;
  std::set<Project*> dependencies;
  Company *company;

  float workHours = 0; // hours of one worker with effectiveness 1
  float complexity = 1; // hours of one worker with effectiveness 1

public:
  Project(const std::string &name = "project") : name(name) {}

  const std::string &getName() const {
    return name;
  }
  void setName(const std::string &name) {
    Project::name = name;
  }

  Company *getCompany() const {
    return company;
  }
  float getWorkHours() const {
    return workHours;
  }
  float getCompleteness() const {
    return workHours / complexity;
  }
  float getComplexity() const {
    return complexity;
  }
  void setComplexity(float complexity) {
    Project::complexity = complexity;
  }
  bool isComplete() const {
    return workHours >= complexity;
  }

  const std::set<std::unique_ptr<Worker>> &getProjects() const {
    return workers;
  }
  const std::set<std::shared_ptr<Technology>> &getTechnologies() const {
    return technologies;
  }

  const std::set<Project*> &getDependencies() const {
    return dependencies;
  }

  void addDependencies(Project* project) {
    dependencies.insert(project);
  }

  set<std::unique_ptr<Worker>> &getWorkers() {
    return workers;
  }
  void addWorker(std::unique_ptr<Worker> worker) {

    bool k = false;
    for (auto a : technologies) {
      if (worker->getTechnologies().contains(a)) k = true;
    }

    if (k) {
      worker->setProject(this);
      workers.insert(std::move(worker));
    }
    else {
      std::cout << worker->getName()
      << " can't be added to the project, because of lack of skills(((" << endl;
    }
  }

  void addTechnology(const std::shared_ptr<Technology> &technology) {
    technology->addProject(this);
    technologies.insert(technology);
  }

  void skipTime(float hours) {
    for (auto &a : workers) {
      bool k = true;
      for (auto &a: dependencies) {
        if(!a->isComplete())
          k = false;
      }

      if (!isComplete() && k)
        workHours += a->getEffectiveness() * hours;

      if (isComplete())
        workHours = complexity;
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const Project& p) {
    os << p.name << " - " << p.getCompleteness() * 100 << "% :\n";
    os << "  Complexity = " << p.complexity << std::endl;
    os << "  WorkHours = " << p.workHours << std:: endl;
    os << "  Completeness = " << p.getCompleteness() << std::endl;

    os << "  Technologies: ";
    for (auto &a : p.technologies) {
      os << *a << ' ';
    }
    os << endl;

    os << "  Workers:\n";
    for (auto &a : p.workers) {
      os << "  " << *a << std::endl;
    }
    return os;
  }
};

