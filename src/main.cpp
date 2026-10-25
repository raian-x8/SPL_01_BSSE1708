
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

    // Open the sample C source file
    ifstream inputFile("samples/hello.c");

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
