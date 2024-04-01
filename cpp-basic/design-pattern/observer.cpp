#include <iostream>
#include <string>
#include <list>

class Subject;

class Observer {
  public:
    Observer(Subject* sbj) : subject(sbj) { }
    virtual void update(std::string msg) = 0;

  private:
    Subject* subject;
};


class Subject {
  public:
    Subject(int val) : observers({}), status(val) { }

  public:
    void set_status(int val) { 
      if (status != val) {
        status = val; 
        notify();
      }
    }

    int get_status() { 
      return status; 
    }

  public:
    void attach(Observer* obj) {
      observers.push_back(obj);
    }

    void notify() {
      for (auto element : observers) {
        element->update(std::to_string(status));
      }
    }

  private:
    std::list<Observer*> observers;
    int status;
};

class HexObserver : public Observer {
  public:
    HexObserver(Subject* sbj) : Observer(sbj) {

    }
    void update(std::string msg) override {
      std::cout << "hex: " << msg << std::endl;
    }
};


class DecObserver : public Observer {
  public:
    DecObserver(Subject* sbj) : Observer(sbj) {
      
    }
    void update(std::string msg) override {
      std::cout << "dec: " << msg << std::endl;
    } 
};


int main() {
  Subject* subobj = new Subject(0);
  HexObserver* hex = new HexObserver(subobj);
  DecObserver* dec = new DecObserver(subobj);

  subobj->attach(hex);
  subobj->attach(dec);

  std::cout << "-----------------------------" << std::endl;
  subobj->set_status(100);
  std::cout << "-----------------------------" << std::endl;
  subobj->set_status(200);
  std::cout << "-----------------------------" << std::endl;

  delete subobj;
  delete hex;
  delete dec;
}