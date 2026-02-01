#pragma once
#include <glad.h>
#include <iostream>
#include <fstream>
#include <string>

void ParseShader(const std::string& file_path, std::string& parsed_string);
unsigned int CompileShader(unsigned int type, const std::string& source);
int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);