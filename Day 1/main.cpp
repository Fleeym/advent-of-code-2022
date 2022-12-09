#include <iostream>
#include <fstream>
#include <string>
#include <array>

namespace fs = std::filesystem;

typedef std::array<uint32_t, 3> top3_t;

/**
 * Returns index of the first found element smaller than the sum.
 * If sum is smaller than all elements, return -1
*/
int isHigherThanTop3(top3_t const& currentTop3, uint32_t sum) {
    const size_t ARRAY_SIZE = currentTop3.size();

    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        if (sum > currentTop3.at(i)) return i;
    }
    return -1;
}

top3_t updateTopThree(top3_t const& currentTop3, uint32_t sum) {
    top3_t new_top = currentTop3;
    int index = isHigherThanTop3(currentTop3, sum);
    if (index != -1) {
        uint32_t old_item = new_top.at(index);
        new_top.at(index) = sum;
        // Send the element we replaced one position down, moving the other elements down aswell
        if (index < new_top.size() - 1) {
            const size_t size = new_top.size();
            for (size_t i = index + 1; i < size; i++) {
                uint32_t temp = new_top.at(i);
                new_top.at(i) = old_item;
                old_item = temp;
            }
        }
    }
    return new_top;
}

top3_t getTopThreeCalories(std::string const& file_name) {
    std::ifstream inputFile(file_name);
    top3_t top_three = {0, 0, 0};
    uint32_t currentSum = 0;
    for (std::string line; std::getline(inputFile, line);) {
        if (line.empty()) {
            top_three = updateTopThree(top_three, currentSum);
            currentSum = 0;
            continue;
        }
        currentSum += std::stoi(line);
    }
    inputFile.close();
    return top_three;
}
       
int main() {
    top3_t calories = getTopThreeCalories("input.txt");
    uint32_t sum = 0;
    std::cout << "The top 3 is...\n";
    for (size_t i = 0; i < 3; i++) {
        sum += calories.at(i);
        std::cout << i << ". " << calories.at(i) << "\n";
    }
    std::cout << "And their sum is: " << sum;
    return 0;
}
