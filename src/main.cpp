
#include <iostream>

#include <fstream>

#include <string>

using namespace std;

int main()
{
    cout << "================================\n";
    cout << "        CloneScope v0.1\n";
    cout << "================================\n";
    cout << "Code Clone Analysis Tool\n";
    cout << "Status: Development Started\n";

    // Read a user-selected C/C++ source file
    // Ask the user for a source file path
    string filePath;

    cout << "Enter source file path: ";
    getline(cin, filePath);

    // Open the selected source file
    ifstream inputFile(filePath);

    // Check whether the file opened successfully
    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open source file.\n";
        return 1;
    }

    cout << "Source file opened successfully!\n";

    // Store one line of source code
    string line;

    // Read and display each line
    while (getline(inputFile, line))
    {
        cout << line << '\n';
    }
    return 0;
}
