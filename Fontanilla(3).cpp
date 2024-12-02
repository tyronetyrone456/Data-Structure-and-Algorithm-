#include <iostream>
#include <stack>
#include <cctype>
#include <sstream>
#include <unordered_map>

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int applyOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

int evaluatePostfix(const std::string& postfix) {
    std::stack<int> values;
    std::stringstream ss(postfix);
    std::string token;

    while (ss >> token) {
        if (isdigit(token[0])) {
            values.push(std::stoi(token));
        } else {
            int b = values.top(); values.pop();
            int a = values.top(); values.pop();
            values.push(applyOperation(a, b, token[0]));
        }
    }

    return values.top();
}


std::string infixToPostfix(const std::string& expression) {
    std::stack<char> operators;
    std::stringstream output;
    std::unordered_map<char, int> precedenceMap = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

    for (size_t i = 0; i < expression.length(); i++) {
        char token = expression[i];

        if (isspace(token)) continue;

        if (isdigit(token)) {
            while (i < expression.length() && isdigit(expression[i])) {
                output << expression[i];
                i++;
            }
            i--;
            output << ' ';
        }
        else if (token == '(') {
            operators.push(token);
        }
        else if (token == ')') {
            while (!operators.empty() && operators.top() != '(') {
                output << operators.top() << ' ';
                operators.pop();
            }
            operators.pop();
        }
        else {
            while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                output << operators.top() << ' ';
                operators.pop();
            }
            operators.push(token);
        }
    }

    while (!operators.empty()) {
        output << operators.top() << ' ';
        operators.pop();
    }

    return output.str();
}

int main() {
    std::string infixExpression;
    std::cout << "Enter an infix expression: ";
    std::getline(std::cin, infixExpression);

    std::string postfixExpression = infixToPostfix(infixExpression);
    std::cout << "Postfix Expression: " << postfixExpression << std::endl;

    int result = evaluatePostfix(postfixExpression);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
