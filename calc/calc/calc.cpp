#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include "calc.h"

// Определение арифметических знаков
char ArithmeticSigns[]{ '+', '-', '*', '/', '^' };

// Проверка, является ли символ арифметическим знаком
bool thisIsArithmeticSign(char sign) {
    for (char arithmeticSign : ArithmeticSigns) {
        if (sign == arithmeticSign) {
            return true;
        }
    }
    return false;
}

// Разбиение входного выражения на токены
std::vector<std::string> ParsingAnExample(const std::string& example) {
    std::vector<std::string> tokens;
    std::string buffer;

    for (size_t i = 0; i < example.length(); ++i) {
        char ch = example[i];

        if (thisIsArithmeticSign(ch)) {
            if (!buffer.empty()) {
                tokens.push_back(buffer);
                buffer.clear();
            }
            tokens.push_back(std::string(1, ch));
        }
        else if (ch == '(' || ch == ')' || isalpha(ch)) {
            buffer += ch;
        }
        else if (isdigit(ch) || ch == '.' || ch == '-') {
            buffer += ch;
        }
        else if (ch == ' ' && !buffer.empty()) {
            tokens.push_back(buffer);
            buffer.clear();
        }
    }
    if (!buffer.empty()) {
        tokens.push_back(buffer);
    }
    return tokens;
}

// Преобразование строки в число с учётом функций
float StringToFloat(const std::string& str) {
    std::string newStr = str;
    float x = 0;

    try {
        if (newStr.find("sin") != std::string::npos) {
            x = sin(std::stof(newStr.substr(4, newStr.length() - 5)));
        }
        else if (newStr.find("cos") != std::string::npos) {
            x = cos(std::stof(newStr.substr(4, newStr.length() - 5)));
        }
        else if (newStr.find("sqrt") != std::string::npos) {
            x = sqrt(std::stof(newStr.substr(5, newStr.length() - 6)));
        }
        else if (newStr.front() == '(' && newStr.back() == ')') {
            x = std::stof(newStr.substr(1, newStr.length() - 2));
        }
        else {
            x = std::stof(newStr);
        }
    }
    catch (const std::exception&) {
        throw std::invalid_argument("Ошибка: неверный формат выражения: " + str);
    }

    return x;
}

// Выполнение арифметической операции
float Calculate(float x, float y, const std::string& action) {
    if (action == "+") 
        return x + y;
    if (action == "-")
        return x - y;
    if (action == "*") 
        return x * y;
    if (action == "/") {
        if (y == 0) throw std::invalid_argument("Ошибка: деление на ноль");
        return x / y;
    }
    if (action == "^") return pow(x, y);
    throw std::invalid_argument("Ошибка: неизвестная операция: " + action);
}

// Вычисление выражения на основе токенов
float EvaluateExpression(const std::vector<std::string>& tokens) {
    std::vector<float> values;
    std::vector<std::string> operators;

    for (const auto& token : tokens) {
        if (thisIsArithmeticSign(token[0])) {
            operators.push_back(token);
        }
        else {
            values.push_back(StringToFloat(token));
        }

        // Выполняем вычисление, если есть два значения и оператор
        while (values.size() >= 2 && !operators.empty()) {
            float y = values.back(); values.pop_back();
            float x = values.back(); values.pop_back();
            std::string op = operators.back(); operators.pop_back();
            values.push_back(Calculate(x, y, op));
        }
    }

    if (values.size() == 1) {
        return values[0];
    }
    throw std::runtime_error("Ошибка при вычислении выражения.");
}

int main() {

    setlocale(LC_ALL, "Russian");

    while (true) {
        std::string input;
        std::cout << "Введите выражение (или 'exit' для выхода): ";
        std::getline(std::cin, input);

        if (input == "exit") {
            std::cout << "Выход из программы." << std::endl;
            break;
        }

        try {
            auto tokens = ParsingAnExample(input); // Разбиваем выражение на токены
            float result = EvaluateExpression(tokens); // Вычисляем результат
            std::cout << "Результат: " << result << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return 0;
}
