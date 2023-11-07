#include <iostream>
#include <stack>
#include <string>

void MoveStackElements(std::stack<int>& hat, std::stack<int>& help_hat,
                       std::stack<int>& extra_hat,
                       std::stack<int>& extra_help_hat) {
  while (!hat.empty()) {
    extra_hat.push(hat.top());
    if (extra_help_hat.empty()) {
      extra_help_hat.push(hat.top());
    } else {
      extra_help_hat.push(std::min(hat.top(), extra_help_hat.top()));
    }
    hat.pop();
    help_hat.pop();
  }
}

void GetEnqueued(std::stack<int>& hat, std::stack<int>& help_hat,
                 int& iqlevel) {
  hat.push(iqlevel);
  if (help_hat.empty()) {
    help_hat.push(iqlevel);
  } else {
    help_hat.push(std::min(help_hat.top(), iqlevel));
  }
  std::cout << "ok" << '\n';
}

void GetDequeued(std::stack<int>& hat, std::stack<int>& help_hat,
                 std::stack<int>& extra_hat, std::stack<int>& extra_help_hat) {
  if (hat.empty() && extra_hat.empty()) {
    std::cout << "error" << '\n';
  } else {
    if (extra_hat.empty()) {
      MoveStackElements(hat, help_hat, extra_hat, extra_help_hat);
    }
    std::cout << extra_hat.top() << '\n';
    extra_hat.pop();
    extra_help_hat.pop();
  }
}

void GetFronted(std::stack<int>& hat, std::stack<int>& help_hat,
                std::stack<int>& extra_hat, std::stack<int>& extra_help_hat) {
  if (hat.empty() && extra_hat.empty()) {
    std::cout << "error";
  } else {
    if (extra_hat.empty()) {
      MoveStackElements(hat, help_hat, extra_hat, extra_help_hat);
    }
    std::cout << extra_hat.top();
  }
  std::cout << '\n';
}

void GetCleared(std::stack<int>& hat, std::stack<int>& help_hat,
                std::stack<int>& extra_hat, std::stack<int>& extra_help_hat) {
  while (!hat.empty()) {
    hat.pop();
    help_hat.pop();
  }
  while (!extra_hat.empty()) {
    extra_hat.pop();
    extra_help_hat.pop();
  }
  std::cout << "ok" << '\n';
}

void GetMin(std::stack<int>& help_hat, std::stack<int>& extra_help_hat) {
  if (extra_help_hat.empty() && help_hat.empty()) {
    std::cout << "error" << '\n';
  }
  if (!extra_help_hat.empty() && help_hat.empty()) {
    std::cout << extra_help_hat.top() << '\n';
  }
  if (extra_help_hat.empty() && !help_hat.empty()) {
    std::cout << help_hat.top() << '\n';
  }
  if (!extra_help_hat.empty() && !help_hat.empty()) {
    std::cout << std::min(help_hat.top(), extra_help_hat.top()) << '\n';
  }
}

int main() {
  std::stack<int> hat;
  std::stack<int> help_hat;
  std::stack<int> extra_hat;
  std::stack<int> extra_help_hat;
  std::string input;
  int iqlevel = 0;
  int number_of_operations = 0;
  std::cin >> number_of_operations;
  for (int tmp = 0; tmp < number_of_operations; ++tmp) {
    std::cin >> input;
    if (input == "enqueue") {
      std::cin >> iqlevel;
      GetEnqueued(hat, help_hat, iqlevel);
    }
    if (input == "dequeue") {
      GetDequeued(hat, help_hat, extra_hat, extra_help_hat);
    }
    if (input == "front") {
      GetFronted(hat, help_hat, extra_hat, extra_help_hat);
    }
    if (input == "size") {
      std::cout << hat.size() + extra_hat.size() << '\n';
    }
    if (input == "clear") {
      GetCleared(hat, help_hat, extra_hat, extra_help_hat);
    }
    if (input == "min") {
      GetMin(help_hat, extra_help_hat);
    }
  }
}