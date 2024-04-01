#include <iostream>
#include <string>
#include <vector>

class Mouse;
class Monitor;
class Keyboard;
class Computer;

// --------------------------------------------------------------------
// the interface of visitor
class ComputerPartVisitor {
  public:
    virtual void visit_mouse(const Mouse* cptr) const = 0;
    virtual void visit_monitor(const Monitor* cptr) const = 0;
    virtual void visit_keyboard(const Keyboard* cptr) const = 0;
    virtual void visit_computer(const Computer* cptr) const = 0;
};

// --------------------------------------------------------------------
class ComputerPart {
  public:
    virtual ~ComputerPart() {}
    virtual void accept(ComputerPartVisitor* visitor) const = 0;
};

class Monitor : public ComputerPart {
  public:
    void accept(ComputerPartVisitor* visitor) const override {
      visitor->visit_monitor(this);
    }
};

class Mouse : public ComputerPart {
  public:
    void accept(ComputerPartVisitor* visitor) const override {
      visitor->visit_mouse(this);
    }
};

class Keyboard : public ComputerPart {
  public:
    void accept(ComputerPartVisitor* visitor) const override {
      visitor->visit_keyboard(this);
    }
};

class Computer : public ComputerPart {
  public:
    Computer() {
      parts.push_back(new Mouse);
      parts.push_back(new Monitor);
      parts.push_back(new Keyboard);
    }

    void accept(ComputerPartVisitor* visitor) const override {
      visitor->visit_computer(this);
      for (const auto pt : parts) {
        pt->accept(visitor);
      }
    }

  private:
    std::vector<ComputerPart*> parts;
};

// --------------------------------------------------------------------
class DisplayVisitor : public ComputerPartVisitor {
  public:
    void visit_mouse(const Mouse* cptr) const override {
      std::cout << "[1] display a mouse" << std::endl;
    }
    void visit_monitor(const Monitor* cptr) const override {
      std::cout << "[1] display a monitor" << std::endl;
    }
    void visit_keyboard(const Keyboard* cptr) const override {
      std::cout << "[1] display a keyboard" << std::endl;
    }
    void visit_computer(const Computer* cptr) const override {
      std::cout << "[1] display a computer" << std::endl;
    }
};

class CreateVisitor : public ComputerPartVisitor {
  public:
    void visit_mouse(const Mouse* cptr) const override {
      std::cout << "[2] create a mouse" << std::endl;
    }
    void visit_monitor(const Monitor* cptr) const override {
      std::cout << "[2] create a monitor" << std::endl;
    }
    void visit_keyboard(const Keyboard* cptr) const override {
      std::cout << "[2] create a keyboard" << std::endl;
    }
    void visit_computer(const Computer* cptr) const override {
      std::cout << "[2] create a computer" << std::endl;
    }
};

// --------------------------------------------------------------------
int main(int argc, char* argv[]) {
  ComputerPartVisitor *create_visitor = new CreateVisitor();
  ComputerPartVisitor *display_visitor = new DisplayVisitor();
  Computer* computer = new Computer();
  std::cout << "---------------------------------------" << std::endl;
  computer->accept(create_visitor);
  std::cout << "---------------------------------------" << std::endl;
  computer->accept(display_visitor);
  std::cout << "---------------------------------------" << std::endl;
}