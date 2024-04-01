#include <iostream>
#include <string>
#include <memory>

// Lazy Singleton
class Singleton {
  private:
    // just declaration
    static Singleton* instance;

  private:
    Singleton() {}
    ~Singleton() {}
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

  public:
    static Singleton* get_instance() {
      if (instance == nullptr)
        instance = new Singleton;
      return instance;
    }

  public:
    void set(const std::string& str) {
      m_str = str;
    }
    std::string get() {
      return m_str;
    }

  private:
    std::string m_str;
};

Singleton* Singleton::instance = nullptr;

int main() {
  auto entity_one = Singleton::get_instance();
  auto entity_two = Singleton::get_instance();

  entity_one->set("TensorFlow");
  std::cout << entity_two->get() << std::endl;

  entity_two->set("PyTorch");
  std::cout << entity_one->get() << std::endl;
}