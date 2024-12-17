#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define MAX_PATH 255

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

std::vector<uint8_t> readBytesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<uint8_t> byteArray;
    std::string line;

    if (file.is_open()) {
        std::cerr << "Reading from " << filename << std::endl;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string byteStr;
            while (std::getline(ss, byteStr, ',')) {
                byteArray.push_back(static_cast<uint8_t>(std::stoi(byteStr)));
            }
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }

    return byteArray;
}

void writeBytesToBinaryFile(const std::string& filename, const std::vector<uint8_t>& byteArray) {
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    if (file.is_open()) {
        if (!byteArray.empty()) {
            file.write(reinterpret_cast<const char*>(byteArray.data()), byteArray.size());
            if (file.good()) {
                std::cout << "Wrote " << byteArray.size() << " bytes to " << filename << std::endl;
            }
            else {
                std::cerr << "Error occurred while writing to file: " << filename << std::endl;
            }
        }
        else {
            std::cerr << "Byte array is empty, nothing to write to file: " << filename << std::endl;
        }
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

void printByteArray(const std::vector<uint8_t>& byteArray) {
    for (const auto& byte : byteArray) {
        std::cout << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc !=3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::string inputFilename = argv[1];
    if (!fileExists(inputFilename)) {
        std::cerr << "file does not exist: " << inputFilename << std::endl;
		return 1;
    }
    std::vector<uint8_t> byteArray = readBytesFromFile(inputFilename);
    // printByteArray(byteArray);

    std::string outputFileName = argv[2];
    writeBytesToBinaryFile(outputFileName, byteArray);
}
