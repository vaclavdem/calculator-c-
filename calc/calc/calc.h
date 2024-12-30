#pragma once

#include <string>
#include <vector>

std::vector<std::string> ParsingAnExample(const std::string& example);

float StringToFloat(const std::string& str);

float Calculate(float x, float y, const std::string& action);

float EvaluateExpression(const std::vector<std::string>& tokens);
