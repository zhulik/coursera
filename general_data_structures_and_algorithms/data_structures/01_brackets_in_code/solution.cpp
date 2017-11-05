#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Bracket {
public:
  Bracket(char type, int position) : m_type(type), m_position(position) {}

  bool Match(char c) {
    if (m_type == '[' && c == ']')
      return true;
    if (m_type == '{' && c == '}')
      return true;
    if (m_type == '(' && c == ')')
      return true;
    return false;
  }

  char type() const { return m_type; }
  int position() const { return m_position; }

private:
  char m_type;
  int m_position;
};

int main() {
  string text;
  getline(cin, text);

  stack<Bracket> opening_brackets_stack;
  int unmatched_index = -1;
  for (int position = 0; position < text.length(); ++position) {
    char next = text[position];

    if (next == '(' || next == '[' || next == '{') {
      opening_brackets_stack.push(Bracket(next, position));
    }

    if (next == ')' || next == ']' || next == '}') {
      if (opening_brackets_stack.empty()) {
        if (unmatched_index == -1)
          unmatched_index = position;
        continue;
      }
      if (opening_brackets_stack.top().Match(next))
        opening_brackets_stack.pop();
      else {
        if (unmatched_index == -1)
          unmatched_index = position;
      }
    }
  }

  if (opening_brackets_stack.empty() && unmatched_index == -1) {
    cout << "Success";
  } else {
    if (unmatched_index == -1) {
      cout << opening_brackets_stack.top().position() + 1;
    } else {
      cout << unmatched_index + 1;
    }
  }
  cout << endl;

  return 0;
}
