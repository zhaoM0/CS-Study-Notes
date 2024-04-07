#include <iostream>
using namespace std;

enum class RequestType:char {
  DayOff, 
  SalaryRaise, 
  Resignation
};

class AbstractManager {
public:
  void setNext(AbstractManager* manager) { _next = manager; }
  virtual void handleRequest(RequestType type) = 0;
  virtual ~AbstractManager() {}
protected:
  AbstractManager* _next = nullptr;
};

// middle leader
class Manager : public AbstractManager {
public:
  void handleRequest(RequestType type) {
    switch (type) {
      case RequestType::DayOff: { 
        cout << "leader: ok, hava a good rest." << endl; 
      }; break;
      case RequestType::SalaryRaise: {
        cout << "leader: I can't decide this, I need to ask the CEO." << endl;
        _next->handleRequest(type);
      }; break;
      case RequestType::Resignation: {
        cout << "leader: I need to ask superiors for permission to resign." << endl;
        _next->handleRequest(type);
      };break;
      default:
        break;
    }
  }
};

// CEO
class CEO : public AbstractManager {
public:
  void handleRequest(RequestType type) {
    switch (type) {
      case RequestType::DayOff: { 
        cout << "CEO: ok, hava a good rest." << endl; 
      }; break;
      case RequestType::SalaryRaise: {
        cout << "CEO: No, you're underperforming." << endl;
      }; break;
      case RequestType::Resignation: {
        cout << "CEO: I need to give feedback to boss." << endl;
        _next->handleRequest(type);
      };break;
      default:
        break;
    }
  }
};

// BOSS
class Boss : public AbstractManager {
public:
  void handleRequest(RequestType type) {
    switch (type) {
      case RequestType::DayOff: { 
        cout << "Boss: No, you will take a break after this period." << endl; 
      }; break;
      case RequestType::SalaryRaise: {
        cout << "Boss: No, Salary increases are not possible." << endl;
      }; break;
      case RequestType::Resignation: {
        cout << "Boss: You're free to go." << endl;
      };break;
      default:
        break;
    }
  }
};

class Precariat {
public:
  void request(RequestType type, AbstractManager* manager) {
    manager->handleRequest(type);
  }
};

int main() {
  Manager* leader = new Manager;
  CEO* ceo = new CEO;
  Boss* boss = new Boss;
  leader->setNext(ceo);
  ceo->setNext(boss);

  Precariat* person = new Precariat;
  cout << "============== Requests to leader ==============" << std::endl;
  person->request(RequestType::DayOff, leader);
  person->request(RequestType::SalaryRaise, leader);
  person->request(RequestType::Resignation, leader);
  cout << "================ Requests to CEO ===============" << std::endl;
  person->request(RequestType::DayOff, ceo);
  person->request(RequestType::SalaryRaise, ceo);
  person->request(RequestType::Resignation, ceo);
  cout << "=============== Requests to boss ===============" << std::endl;
  person->request(RequestType::DayOff, boss);
  person->request(RequestType::SalaryRaise, boss);
  person->request(RequestType::Resignation, boss);

  return 0;
}