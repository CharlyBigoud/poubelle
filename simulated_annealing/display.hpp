#pragma once

#include <iostream>
#include <string.h>

// void bar();
// void print(const int it, const double energy);
// std::string red(const std::string&);

template<typename T>
std::string to_string(const T& t)
{
    return std::to_string(t);
}

        std::string red(const std::string& s)
        {
            return "\033[31m" + s + "\033[0m";
        }

        template<typename T>
        std::string red(const T& t)
        {
            return "\033[31m" + to_string(t) + "\033[0m";
        }

        std::string green(const std::string& s)
        {
            return "\033[32m" + s + "\033[0m";
        }

        template<typename T>
        std::string green(const T& t)
        {
            return "\033[32m" + to_string(t) + "\033[0m";
        }

        std::string white(const std::string& s)
        {
            return "\033[37m" + s + "\033[0m";
        }

        template<typename T>
        std::string white(const T& t)
        {
            return "\033[37m" + to_string(t) + "\033[0m";
        }

void bar()
{
    std::cout << "it\tT\tDT\tE\tDE" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
}

// template<typename Solver, typename Color>
// template<typename Solver, typename T, typename Color = std::string (*Color)(T&)>
template<typename T, std::string (*Color)(const T&), typename Solver>
void print(
      const Solver& s
    // , const Color& c
    )
{
    std::cout << Color(s.current_it) << "\t";
    std::cout << Color(s.current_temperature) << "\t";
    std::cout << Color(s.current_temperature - s.temperature(s.current_temperature)) << "\t";
    std::cout << Color(s.current_energy) << "\t";
    // // std::cout << s.d_energy << "\t";
    std::cout << std::endl;
}