#include "json_export.hpp"

#include <filesystem>

void writeJsonString(
    std::ostream &output,
    const std::string &value)
{
    constexpr char hex[] = "0123456789ABCDEF";

    output << '"';

    for (unsigned char ch : value)
    {
        switch (ch)
        {
        case '"':
            output << "\\\"";
            break;

        case '\\':
            output << "\\\\";
            break;

        case '\b':
            output << "\\b";
            break;

        case '\f':
            output << "\\f";
            break;

        case '\n':
            output << "\\n";
            break;

        case '\r':
            output << "\\r";
            break;

        case '\t':
            output << "\\t";
            break;

        default:
            if (ch < 0x20)
            {
                output << "\\u00"
                       << hex[(ch >> 4) & 0x0F]
                       << hex[ch & 0x0F];
            }
            else
            {
                output << static_cast<char>(ch);
            }
            break;
        }
    }

    output << '"';
}

void writeJsonSummary(
    std::ostream &output,
    const AnalysisReport &report)
{
    output << "{\n";

    output << "  \"dataset_overview\": {\n";

    output << "    \"student_folders\": "
           << report.studentFolderCount << ",\n";

    output << "    \"source_files\": "
           << report.aggregate.fileCount << ",\n";

    output << "    \"compared_file_pairs\": "
           << report.comparedFilePairs << '\n';

    output << "  },\n";

    output << "  \"source_statistics\": {\n";

    output << "    \"total_source_lines\": "
           << report.aggregate.totalLines << ",\n";

    output << "    \"blank_source_lines\": "
           << report.aggregate.blankLines << ",\n";

    output << "    \"total_tokens\": "
           << report.aggregate.totalTokens << ",\n";

    output << "    \"recognized_function_bodies\": "
           << report.aggregate.totalRecognizedFunctionBodies << '\n';

    output << "  },\n";

    output << "  \"clone_detection\": {\n";

    output << "    \"type1_candidate_pairs\": "
           << report.aggregate.type1CandidateCount << ",\n";

    output << "    \"type2_only_candidate_pairs\": "
           << report.aggregate.type2OnlyCandidateCount << ",\n";

    output << "    \"total_candidate_pairs\": "
           << (report.aggregate.type1CandidateCount +
               report.aggregate.type2OnlyCandidateCount)
           << '\n';

    output << "  }\n";

    output << "}";
}

namespace
{
    std::string jsonStudentFromPath(
        const std::string &relativePath)
    {
        const std::filesystem::path path(relativePath);

        if (!path.has_parent_path())
        {
            return "";
        }

        return path.begin()->string();
    }

    void writeJsonLocation(
        std::ostream &output,
        const std::string &relativePath,
        std::size_t startLine,
        std::size_t endLine)
    {
        const std::filesystem::path path(relativePath);

        output << "{\n";

        output << "      \"student_id\": ";
        writeJsonString(
            output,
            jsonStudentFromPath(relativePath));
        output << ",\n";

        output << "      \"assignment\": ";
        writeJsonString(output, path.filename().string());
        output << ",\n";

        output << "      \"path\": ";
        writeJsonString(output, relativePath);
        output << ",\n";

        output << "      \"start_line\": "
               << startLine << ",\n";

        output << "      \"end_line\": "
               << endLine << '\n';

        output << "    }";
    }
}

void writeJsonCloneCandidates(
    std::ostream &output,
    const AnalysisReport &report)
{
    if (report.cloneCandidates.empty())
    {
        output << "[]";
        return;
    }

    output << "[\n";

    for (std::size_t i = 0;
         i < report.cloneCandidates.size();
         ++i)
    {
        const CloneSummaryEntry &candidate =
            report.cloneCandidates[i];

        if (i != 0)
        {
            output << ",\n";
        }

        output << "  {\n";

        output << "    \"type\": ";

        writeJsonString(
            output,
            candidate.kind == CloneCandidateKind::Type1
                ? "Type-1"
                : "Type-2-only");

        output << ",\n";

        output << "    \"first\": ";

        writeJsonLocation(
            output,
            candidate.firstPath,
            candidate.firstStartLine,
            candidate.firstEndLine);

        output << ",\n";

        output << "    \"second\": ";

        writeJsonLocation(
            output,
            candidate.secondPath,
            candidate.secondStartLine,
            candidate.secondEndLine);

        output << "\n  }";
    }

    output << "\n]";
}

namespace
{
    std::string jsonStyleStatus(
        bool evaluated,
        bool deviation)
    {
        if (!evaluated)
        {
            return "not_evaluable";
        }

        return deviation ? "deviation" : "no_deviation";
    }
}

void writeJsonStudentFindings(
    std::ostream &output,
    const AnalysisReport &report)
{
    if (report.studentFindings.empty())
    {
        output << "[]";
        return;
    }

    output << "[\n";

    for (std::size_t i = 0;
         i < report.studentFindings.size();
         ++i)
    {
        const StudentStyleFinding &finding =
            report.studentFindings[i];

        if (i != 0)
        {
            output << ",\n";
        }

        output << "  {\n";

        output << "    \"student_id\": ";
        writeJsonString(output, finding.studentId);
        output << ",\n";

        output << "    \"naming\": {\n";

        output << "      \"evaluated\": "
               << (finding.namingEvaluated ? "true" : "false")
               << ",\n";

        output << "      \"deviation\": "
               << (finding.namingDeviation ? "true" : "false")
               << ",\n";

        output << "      \"status\": ";

        writeJsonString(
            output,
            jsonStyleStatus(
                finding.namingEvaluated,
                finding.namingDeviation));

        output << "\n    },\n";

        output << "    \"commenting\": {\n";

        output << "      \"evaluated\": "
               << (finding.commentingEvaluated ? "true" : "false")
               << ",\n";

        output << "      \"deviation\": "
               << (finding.commentingDeviation ? "true" : "false")
               << ",\n";

        output << "      \"status\": ";

        writeJsonString(
            output,
            jsonStyleStatus(
                finding.commentingEvaluated,
                finding.commentingDeviation));

        output << "\n    }\n";

        output << "  }";
    }

    output << "\n]";
}

void writeAnalysisReportJson(
    std::ostream &output,
    const AnalysisReport &report)
{
    output << "{\n";

    output << "  \"tool\": {\n";
    output << "    \"name\": \"CloneScope\",\n";
    output << "    \"format_version\": 1\n";
    output << "  },\n";

    output << "  \"summary\": ";
    writeJsonSummary(output, report);
    output << ",\n";

    output << "  \"clone_candidates\": ";
    writeJsonCloneCandidates(output, report);
    output << ",\n";

    output << "  \"student_findings\": ";
    writeJsonStudentFindings(output, report);
    output << ",\n";

    output << "  \"human_review_indicators\": ";
    writeJsonHumanReviewIndicators(output, report);
    output << ",\n";

    output << "  \"interpretation_warning\": ";

    writeJsonString(
        output,
        "Human review required; similarity is not proof of plagiarism.");

    output << "\n}\n";
}

void writeJsonHumanReviewIndicators(
    std::ostream &output,
    const AnalysisReport &report)
{
    const HumanReviewIndicators indicators =
        collectHumanReviewIndicators(report);

    output << "{\n";

    output << "    \"student_count\": "
           << indicators.size() << ",\n";

    if (indicators.empty())
    {
        output << "    \"students\": []\n";
        output << "  }";
        return;
    }

    output << "    \"students\": [\n";

    bool firstStudent = true;

    for (const auto &student : indicators)
    {
        if (!firstStudent)
        {
            output << ",\n";
        }

        firstStudent = false;

        output << "      {\n";

        output << "        \"student_id\": ";
        writeJsonString(output, student.first);
        output << ",\n";

        output << "        \"reasons\": [";

        bool firstReason = true;

        for (const std::string &reason : student.second)
        {
            if (!firstReason)
            {
                output << ", ";
            }

            firstReason = false;

            writeJsonString(output, reason);
        }

        output << "]\n";

        output << "      }";
    }

    output << "\n    ]\n";
    output << "  }";
}