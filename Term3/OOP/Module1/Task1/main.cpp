#include <iostream>
#include <memory>
using namespace std;

#include "include/Company.hpp"

int main() {
  Company company("K-28");

  auto oopTech = make_shared<Technology>("OOP");
  auto pythonTech = make_shared<Technology>("Python");

  auto oopLab2 = make_unique<Project>("OOP Lab 2");
  oopLab2->setComplexity(20);
  oopLab2->addTechnology(oopTech);

  auto workerMykola = make_unique<Worker>("Mykola Chykivchuk", 1.21);
  auto workerGleb = make_unique<Worker>("Gleb Navka", 1.13);
  auto workerMisha = make_unique<Worker>("Misha Tiron", 1.2);

  workerMykola->addTechnology(oopTech);
  workerGleb->addTechnology(oopTech);

  workerGleb->addTechnology(pythonTech);
  workerMisha->addTechnology(pythonTech);

  oopLab2->addWorker(std::move(workerMykola));
  oopLab2->addWorker(std::move(workerGleb));
  //won't be added because lack of OOP technology knowledge
  oopLab2->addWorker(std::move(workerMisha));

  auto oopLab3 = make_unique<Project>("OOP Lab 3");
  oopLab3->setComplexity(30);
  oopLab3->addTechnology(pythonTech);
  oopLab3->addDependencies(oopLab2.get());

  auto workerOstap = make_unique<Worker>("Ostap Mykytuk", 10);
  workerOstap->addTechnology(pythonTech);
  workerOstap->addTechnology(oopTech);

  oopLab3->addWorker(std::move(workerOstap));

  company.addProject(std::move(oopLab2));
  company.addProject(std::move(oopLab3));

  company.listProjects();

  cout << "Skiping 1 hour" << endl;
  company.skipTime(1);
  company.shortListProjects();
  cout << endl;

  cout << "Skiping 5 hour" << endl;
  company.skipTime(5);
  company.shortListProjects();
  cout << endl;

  cout << "Skiping 10 hour" << endl;
  company.skipTime(10);
  company.shortListProjects();
  cout << endl;

  cout << "Skiping 20 hour" << endl;
  company.skipTime(20);
  company.shortListProjects();
  cout << endl;

  company.listProjects();

  company.technologiesByProjectCount();
  company.technologiesByWorkersCount();
  company.technologiesByTimeSpent();

  return 0;
}
