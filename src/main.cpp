
#include <iostream>

#include <fstream>

int main()
{
    std::cout << "================================\n";
    std::cout << "        CloneScope v0.1\n";
    std::cout << "================================\n";
    std::cout << "Code Clone Analysis Tool\n";
    std::cout << "Status: Development Started\n";

    // Open the sample C source file
    std::ifstream inputFile("samples/hello.c");

    // Check whether the file opened successfully
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Could not open source file.\n";
        return 1;
    }

    std::cout << "Source file opened successfully!\n";
    return 0;
}
