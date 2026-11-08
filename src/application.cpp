
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

#include "type2_clone.hpp"

#include "type2_report.hpp"

#include "clone_summary.hpp"

#include "analysis_report.hpp"

#include "report_file_export.hpp"

#include "source_statistics.hpp"

#include "identifier_style.hpp"

#include "identifier_history.hpp"

#include "comment_style.hpp"

#include "comment_history.hpp"

#include "assignment_order.hpp"

#include <vector>

#include <map>

#include <algorithm>

#include <cmath>

using namespace std;

namespace fs = std::filesystem;

struct AnalyzedSourceFile
{
    fs::path path;
    std::vector<Token> tokens;
    std::vector<CodeRegion> functionRegions;
    SourceStatistics statistics;
    IdentifierStyleStatistics identifierStats;
    CommentStyleStatistics commentStats;
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

        AggregateStatistics aggregate;

        std::vector<fs::directory_entry> entries;

        string scanChoice;

        cout << "Scan subfolders recursively? (y/n): ";
        getline(cin, scanChoice);
        if (scanChoice == "y" || scanChoice == "Y")
        {
            for (const auto &entry :
                 fs::recursive_directory_iterator(sourcePath))
            {
                entries.push_back(entry);
            }
        }
        else
        {
            for (const auto &entry :
                 fs::directory_iterator(sourcePath))
            {
                entries.push_back(entry);
            }
        }

        // Visit each entry directly inside the folder
        for (const auto &entry : entries)
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

                // Analyze comments using the original and cleaned source.
                CommentStyleStatistics commentStats =
                    calculateCommentStyleStatistics(sourceCode, cleanedCode);

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

                // Calculate statistics for the current source file.
                SourceStatistics statistics = calculateSourceStatistics(
                    sourceCode,
                    tokens.size(),
                    functionRegions.size());

                // Display source-line statistics.
                cout << "Total source lines: "
                     << statistics.totalLines << '\n';

                cout << "Blank source lines: "
                     << statistics.blankLines << '\n';

                cout << "Lines containing comments: "
                     << commentStats.commentLines << '\n';

                cout << "Comment-only lines: "
                     << commentStats.commentOnlyLines << '\n';

                cout << "Inline-comment lines: "
                     << commentStats.inlineCommentLines << '\n';

                // Calculate identifier-naming statistics for this source file.
                IdentifierStyleStatistics identifierStats =
                    calculateIdentifierStyleStatistics(tokens);

                // Display the number of unique identifiers.
                cout << "Unique identifier names: "
                     << identifierStats.uniqueIdentifierCount << '\n';

                // Display the naming-style distribution.
                cout << "camelCase identifiers: "
                     << identifierStats.camelCase << '\n';

                cout << "PascalCase identifiers: "
                     << identifierStats.pascalCase << '\n';

                cout << "snake_case identifiers: "
                     << identifierStats.snakeCase << '\n';

                cout << "Lowercase identifiers: "
                     << identifierStats.lowercase << '\n';

                cout << "Single-letter identifiers: "
                     << identifierStats.singleLetter << '\n';

                cout << "Other identifier styles: "
                     << identifierStats.other << '\n';

                // Add this file's statistics to the aggregate totals.
                accumulateSourceStatistics(aggregate, statistics);

                analyzedFiles.push_back(
                    AnalyzedSourceFile{
                        entry.path(),
                        tokens,
                        functionRegions,
                        statistics,
                        identifierStats,
                        commentStats});
            }
        }

        cout << "\nAnalyzed source files stored: "
             << analyzedFiles.size() << '\n';

        // Group analyzed source files by their student folder.
        std::map<std::string, std::vector<std::size_t>> studentFileIndices;

        for (std::size_t i = 0; i < analyzedFiles.size(); ++i)
        {
            const fs::path relativePath =
                analyzedFiles[i].path.lexically_relative(sourcePath);

            // Files directly inside the selected folder have no student folder.
            if (!relativePath.has_parent_path())
            {
                continue;
            }

            // The first folder component represents the student.
            const std::string studentId =
                (*relativePath.begin()).string();

            studentFileIndices[studentId].push_back(i);
        }

        // Display the detected student groups.
        cout << "\nStudent folders detected: "
             << studentFileIndices.size() << '\n';

        for (const auto &student : studentFileIndices)
        {
            cout << "Student: " << student.first
                 << " | Source files: " << student.second.size()
                 << '\n';
        }

        // Analyze historical identifier-naming patterns for each student.
        cout << "\nExperimental student style history:\n";

        std::vector<StudentStyleFinding> studentFindings;

        for (auto &student : studentFileIndices)
        {
            studentFindings.push_back(StudentStyleFinding{});
            StudentStyleFinding &finding = studentFindings.back();
            finding.studentId = student.first;

            std::vector<std::size_t> &fileIndices = student.second;

            // Require at least two historical files and one current file.
            if (fileIndices.size() < 3)
            {
                cout << "Student: " << student.first
                     << " | Insufficient historical submissions.\n";
                continue;
            }

            // Collect filenames for numeric assignment ordering.
            std::vector<std::string> filenames;

            for (std::size_t index : fileIndices)
            {
                filenames.push_back(
                    analyzedFiles[index].path.filename().string());
            }

            // Validate filenames and determine chronological order.
            const AssignmentOrderResult assignmentOrder =
                determineAssignmentOrder(filenames);

            // Avoid historical comparisons when assignment order is uncertain.
            if (!assignmentOrder.valid)
            {
                cout << "Student: " << student.first
                     << " | Historical analysis skipped: "
                     << assignmentOrder.reason << '\n';

                continue;
            }

            // Translate the ordered positions back to analyzed-file indices.
            std::vector<std::size_t> orderedFileIndices;

            for (std::size_t position : assignmentOrder.orderedPositions)
            {
                orderedFileIndices.push_back(fileIndices[position]);
            }

            fileIndices = orderedFileIndices;

            // Collect statistics from all preceding assignments.
            std::vector<IdentifierStyleStatistics> historicalFiles;
            std::vector<CommentHistorySample> historicalCommentFiles;

            for (std::size_t i = 0; i + 1 < fileIndices.size(); ++i)
            {
                const AnalyzedSourceFile &historicalFile =
                    analyzedFiles[fileIndices[i]];

                historicalFiles.push_back(
                    historicalFile.identifierStats);

                historicalCommentFiles.push_back(
                    CommentHistorySample{
                        historicalFile.statistics.totalLines,
                        historicalFile.statistics.blankLines,
                        historicalFile.commentStats.commentLines});
            }

            // The last assignment is treated as the current submission.
            const AnalyzedSourceFile &currentFile =
                analyzedFiles[fileIndices.back()];

            const IdentifierHistoryResult result =
                analyzeIdentifierHistory(
                    historicalFiles,
                    currentFile.identifierStats);

            const CommentHistorySample currentCommentSample{
                currentFile.statistics.totalLines,
                currentFile.statistics.blankLines,
                currentFile.commentStats.commentLines};

            const CommentHistoryResult commentResult =
                analyzeCommentHistory(
                    historicalCommentFiles,
                    currentCommentSample);

            finding.namingEvaluated =
                result.sufficientData && result.stableHistoricalStyle;
            finding.namingDeviation =
                finding.namingEvaluated && result.reviewRecommended;
            finding.commentingEvaluated =
                commentResult.sufficientData &&
                commentResult.stableHistoricalRate;
            finding.commentingDeviation =
                finding.commentingEvaluated && commentResult.reviewRecommended;

            cout << "Student: " << student.first
                 << " | Current file: "
                 << currentFile.path.filename().string()
                 << '\n';

            // Display conventions only when historical analysis is meaningful.
            if (result.sufficientData && result.stableHistoricalStyle)
            {
                cout << "Historical convention: "
                     << identifierStyleName(result.historicalDominantStyle)
                     << '\n';

                cout << "Current convention: "
                     << identifierStyleName(result.currentDominantStyle)
                     << '\n';
            }

            if (!result.sufficientData)
            {
                cout << "Insufficient identifier evidence.\n";
            }
            else if (!result.stableHistoricalStyle)
            {
                cout << "No stable historical naming convention.\n";
            }
            else if (result.reviewRecommended)
            {
                cout << "Naming-style deviation detected.\n";
                cout << "Human review recommended; "
                     << "this is not proof of plagiarism.\n";
            }
            else
            {
                cout << "No clear naming-style deviation detected.\n";
            }

            // Report historical commenting-style analysis.
            cout << "Commenting-style history:\n";

            if (!commentResult.sufficientData)
            {
                cout << "Insufficient source-line evidence "
                     << "for commenting-history analysis.\n";
            }
            else if (!commentResult.stableHistoricalRate)
            {
                cout << "No stable historical commenting rate.\n";
            }
            else
            {
                cout << "Historical comment rate: "
                     << std::lround(
                            commentResult.historicalCommentRate * 100.0)
                     << "%\n";

                cout << "Current comment rate: "
                     << std::lround(
                            commentResult.currentCommentRate * 100.0)
                     << "%\n";

                if (commentResult.reviewRecommended)
                {
                    cout << "Commenting-style deviation detected.\n";
                    cout << "Human review recommended; "
                         << "this is not proof of plagiarism.\n";
                }
                else
                {
                    cout << "No clear commenting-style deviation detected.\n";
                }
            }
        }

        // Display combined source-file statistics.
        cout << "Aggregate source files: "
             << aggregate.fileCount << '\n';

        cout << "Aggregate source lines: "
             << aggregate.totalLines << '\n';

        cout << "Aggregate blank lines: "
             << aggregate.blankLines << '\n';

        cout << "Aggregate tokens: "
             << aggregate.totalTokens << '\n';

        cout << "Aggregate recognized function bodies: "
             << aggregate.totalRecognizedFunctionBodies << '\n';

        std::size_t filePairCount = 0;
        std::vector<CloneSummaryEntry> candidateDetails;

        for (std::size_t i = 0; i < analyzedFiles.size(); ++i)
        {
            for (std::size_t j = i + 1; j < analyzedFiles.size(); ++j)
            {
                const AnalyzedSourceFile &first = analyzedFiles[i];
                const AnalyzedSourceFile &second = analyzedFiles[j];

                const std::string firstRelativePath =
                    first.path.lexically_relative(sourcePath).generic_string();

                const std::string secondRelativePath =
                    second.path.lexically_relative(sourcePath).generic_string();

                cout << "Comparing files: "
                     << firstRelativePath
                     << " vs "
                     << secondRelativePath << '\n';

                std::vector<Type1BodyMatch> matches =
                    findType1BodyMatches(
                        first.tokens,
                        first.functionRegions,
                        second.tokens,
                        second.functionRegions);

                aggregate.type1CandidateCount += matches.size();

                cout << "Type-1 body-level candidates: "
                     << matches.size() << '\n';

                if (!matches.empty())
                {
                    printType1BodyMatches(
                        cout,
                        firstRelativePath,
                        first.tokens,
                        secondRelativePath,
                        second.tokens,
                        matches);

                    for (const Type1BodyMatch &match : matches)
                    {
                        if (!appendCloneSummaryEntry(
                                candidateDetails,
                                CloneCandidateKind::Type1,
                                firstRelativePath,
                                first.tokens,
                                match.firstRegion,
                                secondRelativePath,
                                second.tokens,
                                match.secondRegion))
                        {
                            cerr << "Warning: invalid Type-1 summary boundaries.\n";
                        }
                    }
                }

                std::vector<Type2BodyMatch> type2Matches =
                    findType2BodyMatches(
                        first.tokens,
                        first.functionRegions,
                        second.tokens,
                        second.functionRegions);

                aggregate.type2OnlyCandidateCount += type2Matches.size();

                cout << "Type-2 body-level candidates: "
                     << type2Matches.size() << '\n';

                if (!type2Matches.empty())
                {
                    printType2BodyMatches(
                        cout,
                        firstRelativePath,
                        first.tokens,
                        secondRelativePath,
                        second.tokens,
                        type2Matches);

                    for (const Type2BodyMatch &match : type2Matches)
                    {
                        if (!appendCloneSummaryEntry(
                                candidateDetails,
                                CloneCandidateKind::Type2Only,
                                firstRelativePath,
                                first.tokens,
                                match.firstRegion,
                                secondRelativePath,
                                second.tokens,
                                match.secondRegion))
                        {
                            cerr << "Warning: invalid Type-2 summary boundaries.\n";
                        }
                    }
                }

                ++filePairCount;
            }
        }

        cout << "Total source-file pairs: "
             << filePairCount << '\n';

        // Display the aggregate clone-candidate summary.
        cout << "\nClone candidate summary:\n";

        cout << "Total Type-1 body candidates: "
             << aggregate.type1CandidateCount << '\n';

        cout << "Total Type-2-only body candidates: "
             << aggregate.type2OnlyCandidateCount << '\n';

        // Consolidate already computed evidence for human-readable reporting.
        AnalysisReport report;
        report.studentFolderCount = studentFileIndices.size();
        report.comparedFilePairs = filePairCount;
        report.aggregate = aggregate;
        report.cloneCandidates = candidateDetails;
        report.studentFindings = studentFindings;

        printCombinedAnalysisReport(cout, report);

        // Export the already-computed analysis results.
        fs::path exportDirectory;
        std::string exportError;

        if (!exportAnalysisReportFiles(
                report,
                "clonescope_reports",
                exportDirectory,
                exportError))
        {
            cerr << "\nError: CSV/JSON report export failed.\n";
            cerr << exportError << '\n';

            return 1;
        }

        cout << "\n========================================\n";
        cout << "CSV/JSON REPORT EXPORT COMPLETE\n";
        cout << "========================================\n";

        cout << "Output folder: "
             << fs::absolute(exportDirectory).string() << '\n';

        cout << "Saved: analysis_overview.csv\n";
        cout << "Saved: clone_candidates.csv\n";
        cout << "Saved: student_findings.csv\n";
        cout << "Saved: analysis_report.json\n";

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

    // Analyze commenting patterns in the selected source file.
    CommentStyleStatistics commentStats =
        calculateCommentStyleStatistics(sourceCode, cleanedCode);

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

    // Calculate statistics for the current source file.
    SourceStatistics statistics = calculateSourceStatistics(
        sourceCode,
        tokens.size(),
        functionRegions.size());

    // Display the calculated line statistics.
    cout << "Total source lines: "
         << statistics.totalLines << '\n';

    cout << "Blank source lines: "
         << statistics.blankLines << '\n';

    cout << "Lines containing comments: "
         << commentStats.commentLines << '\n';

    cout << "Comment-only lines: "
         << commentStats.commentOnlyLines << '\n';

    cout << "Inline-comment lines: "
         << commentStats.inlineCommentLines << '\n';

    // Calculate identifier-naming statistics for the selected file.
    IdentifierStyleStatistics identifierStats =
        calculateIdentifierStyleStatistics(tokens);

    // Display unique identifier count.
    cout << "Unique identifier names: "
         << identifierStats.uniqueIdentifierCount << '\n';

    // Display identifier naming patterns.
    cout << "camelCase identifiers: "
         << identifierStats.camelCase << '\n';

    cout << "PascalCase identifiers: "
         << identifierStats.pascalCase << '\n';

    cout << "snake_case identifiers: "
         << identifierStats.snakeCase << '\n';

    cout << "Lowercase identifiers: "
         << identifierStats.lowercase << '\n';

    cout << "Single-letter identifiers: "
         << identifierStats.singleLetter << '\n';

    cout << "Other identifier styles: "
         << identifierStats.other << '\n';

    return 0;
}
