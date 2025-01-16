#pragma once

#include <chrono>
#include <fstream>
#include <sstream>
#include <string>

namespace monitor
{
struct Utils
{
    static double SecondPassed(
        const std::chrono::steady_clock::time_point &t1,
        const std::chrono::steady_clock::time_point &t2)
    {
        std::chrono::duration<double> time_second = std::chrono::duration<double>::zero();
        if (t1 >= t2) {
            time_second = t1 - t2;
        } else {
            time_second = t2 - t1;
        }
        return time_second.count();
    }
    // 读取一行
    static bool ReadLine(const std::string &file, std::vector<std::string> &words)
    {
        std::ifstream ifs(file);
        std::string line;
        std::getline(ifs, line);
        ifs.close();
        if (line.empty()) {
            return false;
        }

        std::istringstream line_ss(line);
        std::string word;
        while (line_ss >> word) {
            words.emplace_back(word);
        }
        return true;
    }
    // 读取所有行
    static bool ReadLines(const std::string &file, std::vector<std::vector<std::string>> &lines)
    {
        std::ifstream ifs(file);
        std::string line;
        while (std::getline(ifs, line)) {
            std::istringstream line_ss(line);
            std::string word;
            lines.push_back({});
            while (line_ss >> word) {
                lines.back().emplace_back(word);
            }
        }
        ifs.close();
        return true;
    }

    static std::vector<std::string> GetStatsLines(const std::string &stat_file,
                                                  const ssize_t line_count)
    {
        std::vector<std::string> stats_lines;
        std::ifstream buffer(stat_file);
        for (ssize_t line_num = 0; line_num < line_count; ++line_num) {
            std::string line;
            std::getline(buffer, line);
            if (line.empty()) {
                break;
            }
            stats_lines.push_back(line);
        }
        return stats_lines;
    }
};
} // namespace monitor