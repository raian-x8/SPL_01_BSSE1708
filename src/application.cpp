
#include <iostream>

#include <fstream>

#include <string>

#include <filesystem>

#include <sstream>

#include "application.hpp"

#include "preprocessor.hpp"

#include "tokenizer.hpp"

#include "function_region.hpp"

#include "type1_clone.hpp"

#include "type1_report.hpp"

#include <vector>

using namespace std;

namespace fs = std::filesystem;

struct AnalyzedSourceFile
{
    fs::path path;
    std::vector<Token> tokens;
    std::vector<CodeRegion> functionRegions;
};

int runCloneScope()
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

    fs::path sourcePath(filePath);

    // Check whether the input path is a directory
    if (fs::is_directory(sourcePath))
    {
        cout << "Folder detected successfully!\n";

        std::vector<AnalyzedSourceFile> analyzedFiles;

        // Visit each entry directly inside the folder
        for (const auto &entry : fs::directory_iterator(sourcePath))
        {
            if (entry.is_regular_file() &&
                (entry.path().extension() == ".c" ||
                 entry.path().extension() == ".cpp"))
            {
                cout << entry.path() << '\n';
                // Open the discovered source file
                ifstream sourceFile(entry.path());

                // Handle a file-opening failure
                if (!sourceFile.is_open())
                {
                    cerr << "Error: Could not open " << entry.path() << '\n';
                    continue;
                }

                cout << "Source file opened successfully!\n";

                // Read the complete discovered source file
                std::ostringstream buffer;
                buffer << sourceFile.rdbuf();

                std::string sourceCode = buffer.str();

                // Remove comments from this source file
                std::string cleanedCode = removeComments(sourceCode);

                // Display the processed source code
                cout << "Preprocessed source code:\n";
                cout << cleanedCode << '\n';

                // Tokenize the current source file.
                std::vector<Token> tokens = tokenize(cleanedCode);

                // Display the total token count for this file.
                cout << "Total tokens: " << tokens.size() << '\n';

                std::vector<CodeRegion> functionRegions =
                    findFunctionBodyRegions(tokens);

                cout << "Supported function-body regions: "
                     << functionRegions.size() << '\n';

                analyzedFiles.push_back(
                    AnalyzedSourceFile{entry.path(), tokens, functionRegions});
            }
        }

        cout << "\nAnalyzed source files stored: "
             << analyzedFiles.size() << '\n';

        std::size_t filePairCount = 0;

        for (std::size_t i = 0; i < analyzedFiles.size(); ++i)
        {
            for (std::size_t j = i + 1; j < analyzedFiles.size(); ++j)
            {
                const AnalyzedSourceFile &first = analyzedFiles[i];
                const AnalyzedSourceFile &second = analyzedFiles[j];

                cout << "Comparing files: "
                     << first.path.filename()
                     << " vs "
                     << second.path.filename() << '\n';

                std::vector<Type1BodyMatch> matches =
                    findType1BodyMatches(
                        first.tokens,
                        first.functionRegions,
                        second.tokens,
                        second.functionRegions);

                cout << "Type-1 body-level candidates: "
                     << matches.size() << '\n';

                if (!matches.empty())
                {
                    printType1BodyMatches(
                        cout,
                        first.path.filename().string(),
                        first.tokens,
                        second.path.filename().string(),
                        second.tokens,
                        matches);
                }

                ++filePairCount;
            }
        }

        cout << "Total source-file pairs: "
             << filePairCount << '\n';

        return 0;
    }

    // Open the selected source file
    ifstream inputFile(sourcePath);

    // Check whether the file opened successfully
    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open source file.\n";
        return 1;
    }

    cout << "Source file opened successfully!\n";

    // Read the complete source file into memory
    std::ostringstream buffer;
    buffer << inputFile.rdbuf();

    std::string sourceCode = buffer.str();

    // Remove comments from the source code
    std::string cleanedCode = removeComments(sourceCode);

    // Display the preprocessed source code.
    cout << "Preprocessed source code:\n";
    cout << cleanedCode;

    // Convert the preprocessed source into tokens.
    std::vector<Token> tokens = tokenize(cleanedCode);

    // Display how many tokens were produced.
    cout << "\nTotal tokens: " << tokens.size() << '\n';

    std::vector<CodeRegion> functionRegions =
        findFunctionBodyRegions(tokens);

    cout << "Supported function-body regions: "
         << functionRegions.size() << '\n';

    return 0;
}
