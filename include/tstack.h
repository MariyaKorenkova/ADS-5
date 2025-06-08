// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  static const int _size = size;
  T arr[size];
  int t;

 public:
  TStack() : t(-1) {}
  bool isEmpty() const {
    return t == -1;
  }
  bool isFull() const {
    return t == _size - 1;
  }
  T getT() const {
    return arr[t];
  }
  void push(const T& value) {
    if (!isFull()) {
      arr[++t] = value;
    }
  }
  void pop() {
    if (!isEmpty()) {
      --t;
    }
  }
};

#endif  // INCLUDE_TSTACK_H_
