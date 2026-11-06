#include "analysis_report.hpp"

#include <filesystem>
#include <map>
#include <set>

namespace
{
    std::string studentFromPath(const std::string &relativePath)
    {
        const std::filesystem::path path(relativePath);

        if (!path.has_parent_path())
        {
            return "";
        }

        // Match application.cpp: the first relative folder is the student ID.
        return (*path.begin()).string();
    }

    void printStudentList(std::ostream &output,
                          const std::set<std::string> &students)
    {
        if (students.empty())
        {
            output << "None";
            return;
        }

        bool first = true;
        for (const std::string &student : students)
        {
            if (!first)
            {
                output << ", ";
            }
            output << student;
            first = false;
        }
    }
}

void printCombinedAnalysisReport(
    std::ostream &output,
    const AnalysisReport &report)
{
    std::set<std::string> type1Students;
    std::set<std::string> type2Students;
    std::map<std::string, std::set<std::string>> reviewReasons;

    for (const CloneSummaryEntry &candidate : report.cloneCandidates)
    {
        const std::string first = studentFromPath(candidate.firstPath);
        const std::string second = studentFromPath(candidate.secondPath);
        std::set<std::string> &participants =
            candidate.kind == CloneCandidateKind::Type1
                ? type1Students
                : type2Students;
        const std::string reason =
            candidate.kind == CloneCandidateKind::Type1
                ? "Type-1 body-level candidate"
                : "Type-2-only body-level candidate";

        for (const std::string &student : {first, second})
        {
            if (!student.empty())
            {
                participants.insert(student);
                reviewReasons[student].insert(reason);
            }
        }
    }

    std::size_t namingCount = 0;
    std::size_t commentingCount = 0;
    std::size_t namingEvaluable = 0;
    std::size_t commentingEvaluable = 0;
    std::set<std::string> namingStudents;
    std::set<std::string> commentingStudents;
    std::set<std::string> namingNotEvaluable;
    std::set<std::string> commentingNotEvaluable;

    for (const StudentStyleFinding &finding : report.studentFindings)
    {
        if (finding.namingEvaluated)
        {
            ++namingEvaluable;
            if (finding.namingDeviation)
            {
                ++namingCount;
                namingStudents.insert(finding.studentId);
                reviewReasons[finding.studentId].insert(
                    "Historical naming-style deviation");
            }
        }
        else
        {
            namingNotEvaluable.insert(finding.studentId);
        }

        if (finding.commentingEvaluated)
        {
            ++commentingEvaluable;
            if (finding.commentingDeviation)
            {
                ++commentingCount;
                commentingStudents.insert(finding.studentId);
                reviewReasons[finding.studentId].insert(
                    "Historical commenting-style deviation");
            }
        }
        else
        {
            commentingNotEvaluable.insert(finding.studentId);
        }
    }

    output << "\n====================================================\n"
           << "             CLONESCOPE ANALYSIS REPORT\n"
           << "====================================================\n";

    output << "\n1. DATASET OVERVIEW\n"
           << "----------------------------------------------------\n"
           << "Student folders analyzed: " << report.studentFolderCount << '\n'
           << "Source files processed: " << report.aggregate.fileCount << '\n'
           << "Source-file pairs compared: " << report.comparedFilePairs << '\n';

    output << "\n2. SOURCE CODE STATISTICS\n"
           << "----------------------------------------------------\n"
           << "Total source lines: " << report.aggregate.totalLines << '\n'
           << "Total blank lines: " << report.aggregate.blankLines << '\n'
           << "Total tokens: " << report.aggregate.totalTokens << '\n'
           << "Recognized function bodies: "
           << report.aggregate.totalRecognizedFunctionBodies << '\n';

    output << "\n3. CODE CLONE DETECTION\n"
           << "----------------------------------------------------\n"
           << "Type-1 body-level candidates: "
           << report.aggregate.type1CandidateCount << '\n'
           << "Type-2-only body candidates: "
           << report.aggregate.type2OnlyCandidateCount << '\n'
           << "Total body-level candidates: "
           << report.aggregate.type1CandidateCount +
                  report.aggregate.type2OnlyCandidateCount << '\n';

    output << "Students involved in Type-1 candidates: ";
    printStudentList(output, type1Students);
    output << "\nStudents involved in Type-2-only candidates: ";
    printStudentList(output, type2Students);
    output << '\n';

    // Print all genuine reported pairs, not inferred all-to-all clone groups.
    // Each pair includes both assignment paths and their source line ranges.
    printCloneSummaryDetails(output, report.cloneCandidates);

    output << "\n4. STATISTICAL STYLOMETRIC ANALYSIS\n"
           << "----------------------------------------------------\n"
           << "Naming-style deviations: " << namingCount << '\n'
           << "Commenting-style deviations: " << commentingCount << '\n'
           << "Naming histories evaluable: " << namingEvaluable
           << " / " << report.studentFindings.size() << '\n'
           << "Commenting histories evaluable: " << commentingEvaluable
           << " / " << report.studentFindings.size() << '\n';

    output << "Students with naming-style deviations: ";
    printStudentList(output, namingStudents);
    output << "\nStudents with commenting-style deviations: ";
    printStudentList(output, commentingStudents);
    output << "\nNaming histories not evaluable: ";
    printStudentList(output, namingNotEvaluable);
    output << "\nCommenting histories not evaluable: ";
    printStudentList(output, commentingNotEvaluable);
    output << '\n';

    output << "\n5. HUMAN REVIEW INDICATORS\n"
           << "----------------------------------------------------\n"
           << "Students with at least one reported indicator: "
           << reviewReasons.size() << '\n';

    if (reviewReasons.empty())
    {
        output << "No clone or stable-history deviation indicators found.\n";
    }
    for (const auto &student : reviewReasons)
    {
        output << "Student: " << student.first << '\n';
        for (const std::string &reason : student.second)
        {
            output << "- " << reason << '\n';
        }
    }

    output << "\n6. FINAL REPORT\n"
           << "----------------------------------------------------\n"
           << "Detailed candidate locations: Included above\n"
           << "Statistical findings: Included above\n"
           << "Important: Similarity and coding-style changes are indicators\n"
           << "for human review, not proof of plagiarism.\n"
           << "====================================================\n"
           << "                 ANALYSIS COMPLETE\n"
           << "====================================================\n";
}
