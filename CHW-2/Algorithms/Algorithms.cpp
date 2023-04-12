#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>

struct Report {
    long long time;
    int comparisons_amount;
    int universal_signs_amount;
    std::vector<int> result;
    int number_of_letters;
};

Report NaiveAlgorithm(std::string text, std::string pattern) {
    Report results_report;
    results_report.time = 0;
    results_report.comparisons_amount = 0;
    results_report.universal_signs_amount = 0;
    results_report.number_of_letters = 0;
    for (int i = 0; i < pattern.length(); ++i) {
        if (pattern[i] == '?') {
            results_report.universal_signs_amount++;
        }
        if (pattern[i] == 'b') {
            results_report.number_of_letters = 2;
        }
    }
    if (results_report.number_of_letters == 0) {
        results_report.number_of_letters = 4;
    }
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < text.length(); ++i) {
        bool isSuitable = true;
        for (int j = 0; j < pattern.length(); ++j) {
            results_report.comparisons_amount++;
            if (text[i + j] != pattern[j] && pattern[j] != '?') {
                isSuitable = false;
                break;
            }
        }
        if (isSuitable) {
            results_report.result.push_back(i);
        }
    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long milliseconds =
        std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    results_report.time = milliseconds;
    return results_report;
}

Report KMPrattAlgorithmStandard(std::string text, std::string pattern) {
    Report results_report;
    results_report.time = 0;
    results_report.comparisons_amount = 0;
    results_report.universal_signs_amount = 0;
    results_report.number_of_letters = 0;
    for (int i = 0; i < pattern.length(); ++i) {
        if (pattern[i] == '?') {
            results_report.universal_signs_amount++;
        }
        if (pattern[i] == 'b') {
            results_report.number_of_letters = 2;
        }
    }
    if (results_report.number_of_letters == 0) {
        results_report.number_of_letters = 4;
    }
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> pi(pattern.size());
    int k = 0;
    for (uint64_t i = 1; i < pattern.size(); ++i) {
        while (k > 0 && pattern[i] != pattern[k] && pattern[i] != '?' && pattern[k] != '?') {
            results_report.comparisons_amount++;
            k = pi[k - 1];
        }
        results_report.comparisons_amount += 2;
        if (pattern[i] == pattern[k] || pattern[i] == '?' || pattern[k] == '?') {
            ++k;
        }
        pi[i] = k;
    }
    uint64_t kol = 0;
    for (uint64_t i = 0; i < text.size(); ++i) {
        while (kol > 0 && pattern[kol] != text[i] && pattern[kol] != '?') {
            results_report.comparisons_amount++;
            kol = pi[kol - 1];
        }
        results_report.comparisons_amount += 2;
        if (pattern[kol] == text[i] || pattern[kol] == '?') {
            kol++;
        }
        if (kol == pattern.size()) {
            results_report.result.push_back(i - pattern.size() + 1);
        }
    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long milliseconds =
        std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    results_report.time = milliseconds;
    return results_report;
}

Report KMPrattAlgorithmAdvanced(std::string text, std::string pattern) {
    Report results_report;
    results_report.time = 0;
    results_report.comparisons_amount = 0;
    results_report.universal_signs_amount = 0;
    results_report.number_of_letters = 0;
    for (int i = 0; i < pattern.length(); ++i) {
        if (pattern[i] == '?') {
            results_report.universal_signs_amount++;
        }
        if (pattern[i] == 'b') {
            results_report.number_of_letters = 2;
        }
    }
    if (results_report.number_of_letters == 0) {
        results_report.number_of_letters = 4;
    }
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> pi(pattern.size());
    int k = 0;
    for (uint64_t i = 1; i < pattern.size(); ++i) {
        while (k > 0 && pattern[i] != pattern[k] && pattern[i] != '?' && pattern[k] != '?') {
            results_report.comparisons_amount++;
            k = pi[k - 1];
        }
        results_report.comparisons_amount += 2;
        if (pattern[i] == pattern[k] || pattern[i] == '?' || pattern[k] == '?') {
            ++k;
        }
        pi[i] = k;
    }
    std::vector<int> brs(pattern.size(), 0);
    for (int i = 1; i < pattern.size(); ++i) {
        results_report.comparisons_amount += 3;
        if (pattern[pi[i] + 1] != pattern[i + 1] && pattern[pi[i] + 1] != '?' && pattern[i + 1] != '?') {
            brs[i] = pi[i];
        } else {
            brs[i] = brs[pi[i]];
        }
    }
    uint64_t kol = 0;
    for (uint64_t i = 0; i < text.size(); ++i) {
        while (kol > 0 && (kol == pattern.length() || pattern[kol] != text[i] && pattern[kol] != '?')) {
            results_report.comparisons_amount++;
            kol = brs[kol - 1];
        }
        results_report.comparisons_amount += 2;
        if (pattern[kol] == text[i] || pattern[kol] == '?') {
            kol++;
        }
        if (kol == pattern.size()) {
            results_report.result.push_back(i - pattern.size() + 1);
            kol = brs[kol - 1];
        }
    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long milliseconds =
        std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    results_report.time = milliseconds;
    return results_report;
}

int main() {
    std::ifstream in("..\\TestDataGenerator\\testData.txt");
    std::unordered_map<std::string, std::vector<std::string>> simpleTextsPatterns;
    std::unordered_map<std::string, std::vector<std::string>> complexTextsPatterns;
    if (in.is_open()) {
        for (int textAmount = 0; textAmount < 4; ++textAmount) {
            std::string text;
            in >> text;
            std::string pattern;
            std::vector<std::string> simplePatterns;
            in >> pattern;
            while (pattern != "!!!") {
                simplePatterns.push_back(pattern);
                in >> pattern;
            }
            simpleTextsPatterns.insert({ text, simplePatterns });
        }
        for (int textAmount = 0; textAmount < 4; ++textAmount) {
            std::string text;
            in >> text;
            std::string pattern;
            std::vector<std::string> complexPatterns;
            in >> pattern;
            while (pattern != "!!!") {
                complexPatterns.push_back(pattern);
                in >> pattern;
            }
            complexTextsPatterns.insert({ text, complexPatterns });
        }
    }
    in.close();
    std::ofstream out;
    out.open("naive.txt");
    if (out.is_open()) {
        for (auto i = simpleTextsPatterns.begin(); i != simpleTextsPatterns.end(); ++i) {
            for (std::string pattern : i->second) {
                Report report = NaiveAlgorithm(i->first, pattern);
                out << report.universal_signs_amount << " " << i->first.length() << " " << report.number_of_letters << " " << pattern.length() << " " << report.time << " " << report.comparisons_amount << "\n";
            }
        }
        for (auto i = complexTextsPatterns.begin(); i != complexTextsPatterns.end(); ++i) {
            for (std::string pattern : i->second) {
                Report report = NaiveAlgorithm(i->first, pattern);
                out << report.universal_signs_amount << " " << i->first.length() << " " << report.number_of_letters << " " << pattern.length() << " " << report.time << " " << report.comparisons_amount << "\n";
            }
        }
    }
    out.close();
    out.open("KMP_standard.txt");
    if (out.is_open()) {
        for (auto i = simpleTextsPatterns.begin(); i != simpleTextsPatterns.end(); ++i) {
            for (std::string pattern : i->second) {
                Report report = KMPrattAlgorithmStandard(i->first, pattern);
                out << report.universal_signs_amount << " " << i->first.length() << " " << report.number_of_letters << " " << pattern.length() << " " << report.time << " " << report.comparisons_amount << "\n";
            }
        }
        for (auto i = complexTextsPatterns.begin(); i != complexTextsPatterns.end(); ++i) {
            for (std::string pattern : i->second) {
                Report report = KMPrattAlgorithmStandard(i->first, pattern);
                out << report.universal_signs_amount << " " << i->first.length() << " " << report.number_of_letters << " " << pattern.length() << " " << report.time << " " << report.comparisons_amount << "\n";
            }
        }
    }
    out.close();
    out.open("KMP_Advanced.txt");
    if (out.is_open()) {
        for (auto i = simpleTextsPatterns.begin(); i != simpleTextsPatterns.end(); ++i) {
            for (std::string pattern : i->second) {
                Report report = KMPrattAlgorithmAdvanced(i->first, pattern);
                out << report.universal_signs_amount << " " << i->first.length() << " " << report.number_of_letters << " " << pattern.length() << " " << report.time << " " << report.comparisons_amount << "\n";
            }
        }
        for (auto i = complexTextsPatterns.begin(); i != complexTextsPatterns.end(); ++i) {
            for (std::string pattern : i->second) {
                Report report = KMPrattAlgorithmAdvanced(i->first, pattern);
                out << report.universal_signs_amount << " " << i->first.length() << " " << report.number_of_letters << " " << pattern.length() << " " << report.time << " " << report.comparisons_amount << "\n";
            }
        }
    }
    out.close();
}