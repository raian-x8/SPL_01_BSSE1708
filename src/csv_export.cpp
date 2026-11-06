#include "csv_export.hpp"

#include <filesystem>

std::string escapeCsvField(const std::string &field)
{
    bool needsQuotes = false;

    for (char ch : field)
    {
        if (ch == ',' || ch == '"' ||
            ch == '\n' || ch == '\r')
        {
            needsQuotes = true;
            break;
        }
    }

    if (!needsQuotes)
    {
        return field;
    }

    std::string result;

    result.push_back('"');

    for (char ch : field)
    {
        if (ch == '"')
        {
            result.push_back('"');
        }

        result.push_back(ch);
    }

    result.push_back('"');

    return result;
}

void writeAnalysisOverviewCsv(
    std::ostream &output,
    const AnalysisReport &report)
{
    output << "metric,value\n";

    output << "student_folders,"
           << report.studentFolderCount << '\n';

    output << "source_files,"
           << report.aggregate.fileCount << '\n';

    output << "compared_file_pairs,"
           << report.comparedFilePairs << '\n';

    output << "total_source_lines,"
           << report.aggregate.totalLines << '\n';

    output << "blank_source_lines,"
           << report.aggregate.blankLines << '\n';

    output << "total_tokens,"
           << report.aggregate.totalTokens << '\n';

    output << "recognized_function_bodies,"
           << report.aggregate.totalRecognizedFunctionBodies << '\n';

    output << "type1_candidate_pairs,"
           << report.aggregate.type1CandidateCount << '\n';

    output << "type2_only_candidate_pairs,"
           << report.aggregate.type2OnlyCandidateCount << '\n';
}

namespace
{
    std::string studentFromRelativePath(
        const std::string &relativePath)
    {
        const std::filesystem::path path(relativePath);

        if (!path.has_parent_path())
        {
            return "";
        }

        return path.begin()->string();
    }

    std::string assignmentFromRelativePath(
        const std::string &relativePath)
    {
        const std::filesystem::path path(relativePath);

        return path.filename().string();
    }
}

void writeCloneCandidatesCsv(
    std::ostream &output,
    const AnalysisReport &report)
{
    output
        << "type,student_a,assignment_a,path_a,start_line_a,end_line_a,"
        << "student_b,assignment_b,path_b,start_line_b,end_line_b\n";

    for (const CloneSummaryEntry &candidate : report.cloneCandidates)
    {
        const std::string type =
            candidate.kind == CloneCandidateKind::Type1
                ? "Type-1"
                : "Type-2-only";

        output << escapeCsvField(type) << ',';

        output << escapeCsvField(
                      studentFromRelativePath(candidate.firstPath))
               << ',';

        output << escapeCsvField(
                      assignmentFromRelativePath(candidate.firstPath))
               << ',';

        output << escapeCsvField(candidate.firstPath) << ',';

        output << candidate.firstStartLine << ',';
        output << candidate.firstEndLine << ',';

        output << escapeCsvField(
                      studentFromRelativePath(candidate.secondPath))
               << ',';

        output << escapeCsvField(
                      assignmentFromRelativePath(candidate.secondPath))
               << ',';

        output << escapeCsvField(candidate.secondPath) << ',';

        output << candidate.secondStartLine << ',';
        output << candidate.secondEndLine << '\n';
    }
}

void writeStudentFindingsCsv(
    std::ostream &output,
    const AnalysisReport &report)
{
    output
        << "student_id,naming_evaluated,naming_deviation,naming_status,"
        << "commenting_evaluated,commenting_deviation,commenting_status\n";

    for (const StudentStyleFinding &finding : report.studentFindings)
    {
        std::string namingStatus = "not_evaluable";

        if (finding.namingEvaluated)
        {
            namingStatus =
                finding.namingDeviation ? "deviation" : "no_deviation";
        }

        std::string commentingStatus = "not_evaluable";

        if (finding.commentingEvaluated)
        {
            commentingStatus =
                finding.commentingDeviation ? "deviation" : "no_deviation";
        }

        output << escapeCsvField(finding.studentId) << ',';

        output << (finding.namingEvaluated ? "true" : "false") << ',';

        output << (finding.namingDeviation ? "true" : "false") << ',';

        output << namingStatus << ',';

        output << (finding.commentingEvaluated ? "true" : "false") << ',';

        output << (finding.commentingDeviation ? "true" : "false") << ',';

        output << commentingStatus << '\n';
    }
}