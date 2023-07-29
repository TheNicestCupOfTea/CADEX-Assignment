#pragma once

#include <iostream>
#include <iomanip>
#include <iostream>
#include <windows.h>
#include <string>
#include <functional>
#include "Curves.h"

//Function to get a function out of a loaded DLL lib.
template <typename T>
std::function<T> loadDllFunc(const std::string& dllName, const std::string& funcName);

//Function to load a table of functions from a DLL library.
Curves::func_table* loadFuncTable(const std::string libname);

int main();

