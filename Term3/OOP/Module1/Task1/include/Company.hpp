#pragma once
#include <set>
#include <list>
#include <vector>
#include <memory>
#include <algorithm>

#include "Project.hpp"


class Company {
private:
  std::string name;
  std::set<std::unique_ptr<Project>> projects;

public:
  Company(const std::string &name = "company"): name(name) {}

  const std::set<std::unique_ptr<Project>> &getProjects() const {
    return projects;
  }

  void addProject(std::unique_ptr<Project> project) {
    projects.insert(std::move(project));
  }

  void listProjects() {
    for (auto &a : projects) {
      std::cout << *a << std::endl;
    }
  }

  void shortListProjects() {
    for (auto &a : projects) {
      std::cout << a->getName() << " - " << a->getCompleteness() * 100 << "%\n";
    }
  }

  void skipTime(float hours) {
    for (auto &a : projects) {
      a->skipTime(hours);
    }
  }

  auto getAllTechnologies() {
    std::set<std::shared_ptr<Technology>> techs;

    for (auto &a : projects) {
      techs.insert(a->getTechnologies().begin(),
                   a->getTechnologies().end());

      for (auto &b : a->getWorkers()) {
        techs.insert(b->getTechnologies().begin(),
                     b->getTechnologies().end());
      }
    }

    std::vector<std::shared_ptr<Technology>> ret;
    //sorry for that(((
    for (auto &a: techs)
      ret.push_back(a);

    return ret;
  }


  void technologiesByProjectCount() {
    auto t = getAllTechnologies();

    std::sort(t.begin(), t.end(), [](auto &a, auto &b) {
      return (a->getProjects().size() > b->getProjects().size());
    });

    std::cout << "Technologies sorted by project count:\n";
    for (auto &a : t) {
      std::cout << *a << " - " << a->getProjects().size() << std::endl;
    }
  }

  void technologiesByWorkersCount() {
    auto t = getAllTechnologies();

    std::sort(t.begin(), t.end(), [](auto &a, auto &b) {
      return (a->getWorkers().size() > b->getWorkers().size());
    });

    std::cout << "Technologies sorted by workers count:\n";
    for (auto &a : t) {
      std::cout << *a << " - " << a->getWorkers().size() << std::endl;
    }
  }

  void technologiesByTimeSpent() {
    auto t = getAllTechnologies();

    std::sort(t.begin(), t.end(), [](auto &a, auto &b) {
      float at = 0;
      for (auto &i: a->getProjects()) {
        at += i->getWorkHours();
      }
      float bt = 0;
      for (auto &i: b->getProjects()) {
        bt += i->getWorkHours();
      }

      return (at > bt);
    });

    std::cout << "Technologies sorted by time spent:\n";
    for (auto &a : t) {
      float at = 0;
      for (auto &i: a->getProjects()) {
        at += i->getWorkHours();
      }
      std::cout << *a << " - " << at << std::endl;
    }
  }
};