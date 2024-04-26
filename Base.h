#ifndef BASE_H
#define BASE_H
class Base {
 public:
  virtual std::string displayMenu() = 0;
  virtual void getUserInput() = 0;
};
#endif