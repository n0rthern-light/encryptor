#include "cryptor.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

std::vector<uint8_t> readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error: Cannot open file " + filename);
    }
    return std::vector<uint8_t>(std::istreambuf_iterator<char>(file), {});
}

void writeFile(const std::string& filename, const std::vector<uint8_t>& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error: Cannot write to file " + filename);
    }
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " -e|-d <input_file> <key_file>\n";
        return 1;
    }

    std::string mode = argv[1];
    std::string inputFile = argv[2];
    std::string keyFile = argv[3];

    try {
        cryptor::data_t input = readFile(inputFile);
        cryptor::data_t keyData = readFile(keyFile);

        if (keyData.size() != 32) {
            std::cerr << "Error: Key must be exactly 32 bytes.\n";
            return 1;
        }

        cryptor::key_t key;
        std::copy_n(keyData.begin(), 32, key.begin());

        cryptor::data_t output;
        if (mode == "-e") {
            cryptor::Encrypt(input, key, &output);
        } 
        else if (mode == "-d") {
            cryptor::Decrypt(input, key, &output);
        } 
        else {
            std::cerr << "Error: Invalid mode. Use -e (encrypt) or -d (decrypt).\n";
            return 1;
        }

        std::string outputFile = inputFile + ".out";
        writeFile(outputFile, output);
        std::cout << "Output written to: " << outputFile << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
