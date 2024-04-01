#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <list>

using namespace std;

// ------------------------------------------------------------------

class CookerZeff {
  public:
    void make_dsx()  { cout << "make di san xian" << endl; }
    void make_gbjd() { cout << "make gong bao ji ding" << endl; }
    void make_yxrs() { cout << "make yu xiang rou si" << endl; }
    void make_hspg() { cout << "make hong shao pai gu" << endl; }
};

// ------------------------------------------------------------------

class AbstractCommand {
  public:
    AbstractCommand(CookerZeff* receiver) : m_cooker(receiver) {}
    virtual void execute() = 0;
    virtual string name() = 0;

  protected:
    CookerZeff* m_cooker = nullptr;
};

class DSXCommand : public AbstractCommand {
  public:
    using AbstractCommand::AbstractCommand;
    void execute() override {
      m_cooker->make_dsx();
    }
    string name() override {
      return "di san xian";
    }
};

class GBJDCommand : public AbstractCommand {
  public:
    using AbstractCommand::AbstractCommand;
    void execute() override {
      m_cooker->make_gbjd();
    }
    string name() override {
      return "gong bao ji ding";
    }
};

class YXRSCommand : public AbstractCommand {
  public:
    using AbstractCommand::AbstractCommand;
    void execute() override {
      m_cooker->make_yxrs();
    }
    string name() override {
      return "yu xiang rou si";
    }
};


class HSPGCommand : public AbstractCommand {
  public:
    using AbstractCommand::AbstractCommand;
    void execute() override {
      m_cooker->make_hspg();
    }
    string name() override {
      return "hong shao pai gu";
    }
};

// ------------------------------------------------------------------

class Waiter {
  public:
    void setOrder(int idx, AbstractCommand* cmd) {
      cout << "table " << idx << ": place an order " << cmd->name() << endl;

      if (m_cmd_list.find(idx) == m_cmd_list.end()) {
        list<AbstractCommand*> new_list{ cmd };
        m_cmd_list.insert(make_pair(idx, new_list));
      } else {
        m_cmd_list[idx].push_back(cmd);
      }
    }

    void cancelOrder(int idx, AbstractCommand* cmd) {
      if (m_cmd_list.find(idx) != m_cmd_list.end()) {
        m_cmd_list[idx].remove(cmd);
        cout << "table " << idx << ": cancel " << cmd->name() << endl;
      }
    }

    void checkout(int idx) {
      cout << "table " << idx << " list:" << endl;
      for (const auto& item : m_cmd_list[idx]) {
        cout << item->name() << ", ";
      }
      cout << endl;
    }

    void notify(int idx) {
      for (const auto& item : m_cmd_list[idx]) {
        cout << "table " << idx << ": ";
        item->execute();
      }
    }

  private:
    map<int, list<AbstractCommand*>> m_cmd_list;
};

void test() {
  CookerZeff* cooker = new CookerZeff;
  Waiter* waiter = new Waiter;

  YXRSCommand* yxrs = new YXRSCommand(cooker);
  GBJDCommand* gbjd = new GBJDCommand(cooker);
  DSXCommand*  dsx  = new DSXCommand(cooker);
  HSPGCommand* hspg = new HSPGCommand(cooker);

  cout << "-------------- start order ----------------" << endl;
  waiter->setOrder(1, yxrs);
  waiter->setOrder(1, dsx);
  waiter->setOrder(1, gbjd);
  waiter->setOrder(1, hspg);
  waiter->setOrder(2, dsx);
  waiter->setOrder(2, hspg);
  waiter->setOrder(2, gbjd);
  cout << "-------------- cancel order ---------------" << endl;
  waiter->cancelOrder(1, dsx);
  cout << "-------------- start cooking --------------" << endl;
  waiter->notify(1);
  waiter->notify(2);
  cout << "-------------- checkout -------------------" << endl;
  waiter->checkout(1);
  waiter->checkout(2);
}

int main() {
  test();
  return 0;
}