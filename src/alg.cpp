// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int Priority(char op) {
  switch (op) {
    case '(':
      return 0;
    case ')':
      return 1;
    case '+': case '-':
      return 2
    case '*': case '/':
      return 3;
    default:
      return -1;
  }
}

void Postfix(TStack<char, 100>& stack, std::string& px) {
  if (!px.empty() && px.back() != ' ') {
    px += ' ';
  }
  px += stack.getTop();
  stack.pop();
}


std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string px;
  bool Space = false;
  for (char ch : inf) {
    if (isdigit(ch)) {
      if (Space) {
        px += ' ';
        Space = false;
      }
      px += ch;
    } else if (ch == '(') {
      stack.push(ch);
    } else if (ch == ')') {
      while (!stack.isEmpty() && stack.getTop() != '(') {
        Postfix(stack, px);
      }
      if (!stack.isEmpty()) {
        stack.pop();
      }
    } else if (Priority(ch) > 1) {
      while (!stack.isEmpty() &&
        Priority(stack.getTop()) >= Priority(ch)) {
        Postfix(stack, px);
      }
      stack.push(ch);
      Space = true;
    }
  }
  while (!stack.isEmpty()) {
    Postfix(stack, px);
  }
  return px;
}

int eval(const std::string& pref) {
  std::stack<int> stack;
  std::string px;
  for (char ch : pref) {
    if (ch == ' ') {
      if (!px.empty()) {
        stack.push(std::stoi(px));
        px.clear();
      }
      continue;
    }
    if (isdigit(ch)) {
      px += ch;
    } else {
      if (!px.empty()) {
        stack.push(std::stoi(px));
        px.clear();
      }
      int b = stack.top();
      stack.pop();
      int a = stack.top();
      stack.pop();
      switch (ch) {
        case '+':
          stack.push(a + b);
          break;
        case '-':
          stack.push(a - b);
          break;
        case '*':
          stack.push(a * b);
          break;
        case '/':
          stack.push(a / b);
          break;
      }
    }
  }
  return stack.top();
}
