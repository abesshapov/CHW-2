#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

std::string BinaryAlphabetText(int length) {
    std::string text;
    std::vector<char> letters{ 'a', 'b' };
    for (int i = 0; i < length; ++i) {
        text += letters[std::rand() % 2];
    }
    return text;
}

std::string DNAcidSequenceText(int length) {
    std::string text;
    std::vector<char> letters{ 'a', 'g', 't', 'c' };
    for (int i = 0; i < length; ++i) {
        text += letters[std::rand() % 4];
    }
    return text;
}

std::string SimpleTextPatternGeneration(std::string text, int length) {
    int i = std::rand() % (text.length() - length);
    return text.substr(i, length);
}

std::string ComplexTextPatternGeneration(std::string text, int length) {
    int i = std::rand() % (text.length() - length);
    int universalSymbolsAmount = std::rand() % 5;
    universalSymbolsAmount += universalSymbolsAmount == 0 ? 1 : 0;
    std::string pattern = text.substr(i, length);
    for (; universalSymbolsAmount > 0; --universalSymbolsAmount) {
        int position = std::rand() % length;
        pattern[position] = '?';
    }
    return pattern;
}

int main()
{
    std::vector<std::string> textSamples;
    textSamples.push_back(BinaryAlphabetText(10000));
    textSamples.push_back(BinaryAlphabetText(100000));
    textSamples.push_back(DNAcidSequenceText(10000));
    textSamples.push_back(DNAcidSequenceText(100000));
    std::unordered_map<std::string, std::vector<std::string>> simpleTextsPatterns;
    std::unordered_map<std::string, std::vector<std::string>> complexTextsPatterns;
    for (std::string text : textSamples) {
        std::vector<std::string> simplePatterns;
        std::vector<std::string> complexPatterns;
        for (int length = 100; length <= 3000; length += 100) {
            simplePatterns.push_back(SimpleTextPatternGeneration(text, length));
            complexPatterns.push_back(ComplexTextPatternGeneration(text, length));
        }
        simpleTextsPatterns.insert({ text, simplePatterns });
        complexTextsPatterns.insert({ text, complexPatterns });
    }
    std::ofstream out;
    out.open("testData.txt");
    if (out.is_open()) {
        for (auto i = simpleTextsPatterns.begin(); i != simpleTextsPatterns.end(); ++i) {
            out << i->first << " ";
            for (std::string pattern : i->second) {
                out << pattern << " ";
            }
            out << "!!!\n";
        }
        for (auto i = complexTextsPatterns.begin(); i != complexTextsPatterns.end(); ++i) {
            out << i->first << " ";
            for (std::string pattern : i->second) {
                out << pattern << " ";
            }
            out << "!!!\n";
        }
    }
    out.close();
}