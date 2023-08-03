#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "assign_and_process.h"

struct FileData {
    std::vector<std::vector<long double>> data;
    int rowSize;
};

FileData readNumbersFromFile(const std::string& filename);

int main() {
    // Replace "input.txt" with the name of your file containing numbers.
    std::string filename = "writer.txt";

    try {
        FileData fileData = readNumbersFromFile(filename);

        // Access the data and row size from the FileData struct
        std::vector<std::vector<long double>> numbers = fileData.data;
        int rowSize = fileData.rowSize;

        // Print the 2D vector and row size to verify the data.
        for (size_t i = 0; i < numbers.size(); ++i) {
            for (size_t j = 0; j < numbers[i].size(); ++j) {
                std::cout << "numbers[" << i << "][" << j << "] = " << numbers[i][j] << std::endl;
            }
        }
        std::cout << "Row size: " << rowSize << std::endl;
        assign(rowSize,numbers);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; // Return an error code to indicate failure.
    }

    return 0;
}

FileData readNumbersFromFile(const std::string& filename) {
    FileData fileData;
    fileData.rowSize = 0;

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<long double> row;
        std::istringstream iss(line);
        long double num;

        while (iss >> num) {
            row.push_back(num);
        }
        std::cout << num << " ";

        if (fileData.rowSize == 0) {
            fileData.rowSize = row.size();
        } else if (fileData.rowSize != row.size()) {
            std::cout << "\n" << fileData.rowSize << " " << row.size();
            file.close();
            throw std::runtime_error("\nInconsistent number of elements in the file.(Make sure there is no blacnk spaces or empty lines)");
        }

        fileData.data.push_back(row);

        iss.clear();
    }

    file.close();

    return fileData;
}
