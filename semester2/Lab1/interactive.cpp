#include "interactive.hpp"
#include "Database.hpp"
#include "Message.hpp"
#include <iostream>
#include <string>
#include <ctime>
#include <map>
using namespace std;

map<string, Database<Message>> databases;

void interactive() {
  cout << "Welcome to Lab1 interactive mode!"<< endl;
  cout << "type \"help\" to get list of commands with descriptions"<< endl;

  string cmd;
  while (cmd != "exit") {
    cin >> cmd;

    if (cmd == "send") send();
    else if (cmd == "ls") ls();
    else if (cmd == "lsdb") lsdb();
    else if (cmd == "edit") edit();
    else if (cmd == "help") help();
    else if (cmd == "add") add();
    else if (cmd == "load") load();
    else if (cmd == "save") save();
    else if (cmd == "demo") demo();
    else if (cmd == "create") create();
    else if (cmd == "deldb") deldb();
    else if (cmd == "del") del();
    else if (cmd == "gen") gen();
    else if (cmd == "search") search();
    else help();
  }
}

void lsdb() {
  for (auto a : databases) {
    cout << a.first << ": " << a.second.getData().size() << " messages" << endl;
  }
}

void create() {
  string name;
  cin >> name;
  if (name == "help") {
    cout << "create -database_name-" << endl;
    return;
  }
  databases.insert(make_pair(name, Database<Message>()));
}

void deldb() {
  string name;
  cin >> name;
  if (name == "help") {
    cout << "deldb -database_name-" << endl;
    return;
  }
  databases.erase(name);
}

void help () {
  cout << "Database management:\n";
  cout << "  " << setw(10) << left << "create" << "Create database" << endl;
  cout << "  " << setw(10) << left << "deldb"<< "Delete database" << endl;
  cout << "  " << setw(10) << left << "lsdb" << "List databases" << endl;
  cout << "  " << setw(10) << left << "add" << "Add (push) database from file" << endl;
  cout << "  " << setw(10) << left << "load" << "Load database from file" << endl;
  cout << "  " << setw(10) << left << "save" << "Save database to file" << endl;
  cout << "  " << setw(10) << left << "gen" << "Generate random database" << endl;
  cout << "  " << setw(10) << left << "search" << "Search messages and write to database" << endl;
  cout << "\nMessage management:\n";
  cout << "  " << setw(10) << left << "send" << "Create new message" << endl;
  cout << "  " << setw(10) << left << "ls" << "List messages in database" << endl;
  cout << "  " << setw(10) << left << "edit" << "Edit message" << endl;
  cout << "  " << setw(10) << left << "del" << "Delete message" << endl;
  cout << "\nOther:\n";
  cout << "  " << setw(10) << left << "help" << "Help list" << endl;
  cout << "  " << setw(10) << left << "demo" << "Run demo" << endl;
  cout << "  " << setw(10) << left << "exit" << "Exit from program" << endl;

  cout << "\ntype \"-command_name- help\" to get command info\n\n";

}

void send() {
  Message msg;
  string db, type;

  cin >> db;
  if (db == "help") {
    cout << "send -database_name-\n\n-sender_login- -receiver_login-\n"
            "-message_type-\n-message_text-\n\n"
            "-message_type- є {news, question, answer, invite, commentOnEvent, commentOnMessage, none}" << endl;
    return;
  }

  cin >> msg.senderLogin >> msg.receiverLogin;
  cin >> type; cin.get();
  msg.type = Message::stotype(type);
  getline(cin, msg.text);

  msg.spamProbability = (float) rand() / RAND_MAX;

  time_t t = std::time(0);   // get time now
  tm* now = std::localtime(&t);

  msg.time = Time {(uint8_t)now->tm_hour, (uint8_t)now->tm_min, (uint8_t)now->tm_sec,
                   (uint8_t)now->tm_mday, (uint8_t)now->tm_mon, int16_t(now->tm_year + 1900)};

  databases[db].push(msg);

  cout << endl;
}

void edit() {
  string name, par;
  int id;

  cin >> par;
  if (par == "help") {
    cout << "edit -parameter- -database_name- -message_id-" << endl;
    return;
  }

  cin >> name >> id;

  auto &msg = *next(databases[name].getData().begin(), id);

  if (par == "-sender") {
    cin >> msg.senderLogin;
  }
  if (par == "-receiver") {
    cin >> msg.receiverLogin;
  }
  if (par == "-type") {
    string type;
    cin >> type;
    msg.type = Message::stotype(type);
  }
  if (par == "-time") {
    cin >> msg.time;
  }
  if (par == "-text") {
    getline(cin, msg.text);
  }
}

void load() {
  string mode;
  cin >> mode;
  if (mode == "help") {
    cout << "load -save_mode- -database_name- -file_path-\n"
            "-save_mode- : -b - binary file\n"
            "              -t - text file" << endl;
    return;
  }
  string name, path;
  cin >> name >> path;

  if (mode == "-t")
    databases[name].loadFromTextFile(path);
  else if (mode == "-b")
    databases[name].loadFromBinFile(path);
  else
    help();
}

void add() {
  string mode;
  cin >> mode;
  if (mode == "help") {
    cout << "add -save_mode- -database_name- -file_path-\n"
            "-save_mode- : -b - binary file\n"
            "              -t - text file" << endl;
    return;
  }
  string name, path;
  cin >> name >> path;

  if (mode == "-t")
    databases[name].addFromTextFile(path);
  else if (mode == "-b")
    databases[name].addFromBinFile(path);
  else
    help();
}

void save() {
  string mode;
  cin >> mode;
  if (mode == "help") {
    cout << "save -save_mode- -database_name- -file_path-\n"
            "-save_mode- : -b - binary file\n"
            "              -t - text file" << endl;
    return;
  }
  string name, path;
  cin >> name >> path;

  if (mode == "-t")
    databases[name].saveToTextFile(path);
  else if (mode == "-b")
    databases[name].saveToBinFile(path);
  else
    help();
}

void ls() {
  string name;
  cin >> name;
  if (name == "help") {
    cout << "ls -database_name-" << endl;
    return;
  }
  databases[name].print();
}

void del() {
  string name;
  cin >> name;
  if (name == "help") {
    cout << "del -database_name-" << endl;
    return;
  }
  size_t id;
  cin >> id;

  databases[name].getData().erase(std::next(databases[name].getData().begin(), id));
};

void gen() {
  string name;
  cin >> name;
  if (name == "help") {
    cout << "gen -database_name- -count-" << endl;
    return;
  }
  int count;
  cin >> count;

  databases[name] = Database<Message>::Generate(count);
}

void search() {
  string filter;
  cin >> filter;
  if (filter == "help") {
    cout << "search -filter- : -contains -text-\n"
            "                  -sender -sender-\n"
            "                  -receiver -receiver-\n"
            "                  -spam_range -r1- -r2-\n"
            "                  -type -type-\n"
            "                  -before -time-\n"
            "                  -after -time-\n"
            "                  -time_range -t1- -t2-\n" << endl;
    return;
  }

  string from, to;
  cin >> from >> to;

  auto &dbf = databases[from];
  auto &dbt = databases[to];

  if (filter == "-contains") {
    string text;
    cin.get();
    getline(cin, text);

    dbt = dbf.contains(text);
  }
  else if (filter == "-sender") {
    string login;
    cin >> login;
    dbt = dbf.ofSender(login);
  }
  else if (filter == "-receiver") {
    string login;
    cin >> login;
    dbt = dbf.ofReceiver(login);
  }
  else if (filter == "-spam_range") {
    int r1, r2;
    cin >> r1 >> r2;
    dbt = dbf.inSpamRange(r1, r2);
  }
  else if (filter == "-type") {
    string type;
    cin >> type;
    dbt = dbf.ofType(Message::stotype(type));
  }
  else if (filter == "-before") {
    Time time;
    cin >> time;
    dbt = dbf.sentBefore(time);
  }
  else if (filter == "-after") {
    Time time;
    cin >> time;
    dbt = dbf.sentAfter(time);
  }
  else if (filter == "-time_range") {
    Time t1, t2;
    cin >> t1 >> t2;
    dbt = dbf.inTimeRange(t1, t2);
  }

}

void demo() {
  static string devider = "--------------------------------------------\n";

  cout << "Generating random database DB sized 2" << endl;
  auto DB = Database<Message>::Generate(2);

  cout << "Printing DB" << endl;
  cout << devider;
  DB.print();
  cout << devider;

  cout << "Saving DB as text file to demo.txt" << endl;
  DB.saveToTextFile("demo.txt");

  cout << "Saving DB as bin file to demo.bin" << endl;
  DB.saveToBinFile("demo.bin");

  cout << "Loading BIN from demo.bin" << endl;
  Database<Message> BIN;
  BIN.loadFromBinFile("demo.bin");

  cout << "Loading TXT from demo.txt" << endl;
  Database<Message> TXT;
  TXT.loadFromTextFile("demo.txt");

  cout << "Printing BIN:" << endl;
  cout << devider;
  BIN.print();
  cout << devider;

  cout << "Printing TXT:" << endl;
  cout << devider;
  TXT.print();
  cout << devider;

  cout << "\n//Search demos\n" << endl;

  cout << "Generating random database F sized 20" << endl;;
  auto F = Database<Message>::Generate(20);

  cout << "Printing messages from F...\n" << endl;
  
  cout << "...containing \"lorem\":" << endl;
  cout << devider;
  F.contains("lorem").print();
  cout << devider;

  cout << "...sended by Ivanov42:" << endl;
  cout << devider;
  F.ofSender("Ivanov42").print();
  cout << devider;

  cout << "...recieved by Zhereb228:" << endl;
  cout << devider;
  F.ofReceiver("Zhereb228").print();
  cout << devider;

  cout << "...in spam range 0.4 - 0,5" << endl;
  cout << devider;
  F.inSpamRange(0.4, 0.5).print();
  cout << devider;

  cout << "...of type \"news\"" << endl;
  cout << devider;
  F.ofType(Message::Type::news).print();
  cout << devider;

  cout << "...sent before 22:00:00 22.05.1980" << endl;
  cout << devider;
  F.sentBefore(Time{22,00,00,22,05,1985}).print();
  cout << devider;

  cout << "...sent after 22:00:00 22.05.2005" << endl;
  cout << devider;
  F.sentAfter(Time{22,00,00,22,05,2005}).print();
  cout << devider;
}


