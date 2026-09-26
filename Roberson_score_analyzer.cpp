#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

void printArray(const int* scores, int scoreCount) {
    std::cout << "Original dynamic array values: ";
    for (int index = 0; index < scoreCount; ++index) {
        std::cout << scores[index] << (index + 1 == scoreCount ? '\n' : ' ');
    }
}

int findMinimum(const int* scores, int scoreCount) {
    int minimum = scores[0];
    for (int index = 1; index < scoreCount; ++index) {
        if (scores[index] < minimum) {
            minimum = scores[index];
        }
    }
    return minimum;
}

int findMaximum(const int* scores, int scoreCount) {
    int maximum = scores[0];
    for (int index = 1; index < scoreCount; ++index) {
        if (scores[index] > maximum) {
            maximum = scores[index];
        }
    }
    return maximum;
}

double calculateAverage(const int* scores, int scoreCount) {
    int total = 0;
    for (int index = 0; index < scoreCount; ++index) {
        total += scores[index];
    }
    return static_cast<double>(total) / scoreCount;
}

int countAboveAverage(const int* scores, int scoreCount, double average) {
    int count = 0;
    for (int index = 0; index < scoreCount; ++index) {
        if (scores[index] > average) {
            ++count;
        }
    }
    return count;
}

void printVector(const std::vector<int>& scores) {
    for (std::vector<int>::const_iterator iterator = scores.begin();
         iterator != scores.end(); ++iterator) {
        std::cout << *iterator << (iterator + 1 == scores.end() ? '\n' : ' ');
    }
}

int readInteger(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }

        std::cout << "Please enter an integer.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

int main() {
    int scoreCount;
    do {
        scoreCount = readInteger("How many scores will be entered? ");
        if (scoreCount < 1) {
            std::cout << "The number of scores must be at least 1.\n";
        }
    } while (scoreCount < 1);

    int* scores = new int[scoreCount];
    for (int index = 0; index < scoreCount; ++index) {
        do {
            scores[index] = readInteger("Enter score " + std::to_string(index + 1) +
                                        " (0-100): ");
            if (scores[index] < 0 || scores[index] > 100) {
                std::cout << "Score must be from 0 through 100.\n";
            }
        } while (scores[index] < 0 || scores[index] > 100);
    }

    printArray(scores, scoreCount);
    int minimum = findMinimum(scores, scoreCount);
    int maximum = findMaximum(scores, scoreCount);
    double average = calculateAverage(scores, scoreCount);
    std::cout << "Minimum: " << minimum << '\n';
    std::cout << "Maximum: " << maximum << '\n';
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average: " << average << '\n';
    std::cout << "Scores greater than average: "
              << countAboveAverage(scores, scoreCount, average) << '\n';

    std::cout << "Pointer arithmetic demonstration: ";
    int valuesToShow = std::min(scoreCount, 3);
    for (int index = 0; index < valuesToShow; ++index) {
        // *(scores + index) matches scores[index] because indexing is pointer offset plus dereference.
        std::cout << *(scores + index) << (index + 1 == valuesToShow ? '\n' : ' ');
    }

    std::vector<int> scoreVector(scores, scores + scoreCount);
    std::cout << "Vector values using iterators: ";
    printVector(scoreVector);

    int target = readInteger("Enter a target score to search for: ");
    if (std::find(scoreVector.begin(), scoreVector.end(), target) != scoreVector.end()) {
        std::cout << target << " is present in the vector.\n";
    } else {
        std::cout << target << " is not present in the vector.\n";
    }

    std::sort(scoreVector.begin(), scoreVector.end());
    std::cout << "Sorted vector: ";
    printVector(scoreVector);

    std::vector<int>::const_iterator vectorMinimum =
        std::min_element(scoreVector.begin(), scoreVector.end());
    std::vector<int>::const_iterator vectorMaximum =
        std::max_element(scoreVector.begin(), scoreVector.end());
    std::cout << "Vector minimum: " << *vectorMinimum << '\n';
    std::cout << "Vector maximum: " << *vectorMaximum << '\n';
    std::cout << "Vector size: " << scoreVector.size() << '\n';
    std::cout << "Vector capacity: " << scoreVector.capacity() << '\n';

    delete[] scores;
    scores = nullptr;

    return 0;
}