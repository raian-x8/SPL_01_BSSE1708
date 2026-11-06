#include <iostream>
#include <sstream>
#include <string>

#include "../src/csv_export.hpp"

int main()
{
    AnalysisReport report;

    report.cloneCandidates.push_back(CloneSummaryEntry{
        CloneCandidateKind::Type1,
        "student01/assignment3.cpp", 4, 29,
        "student17/assignment3.cpp", 4, 29});

    report.cloneCandidates.push_back(CloneSummaryEntry{
        CloneCandidateKind::Type2Only,
        "student05/assignment3.cpp", 34, 64,
        "student12/assignment3.cpp", 32, 62});

    std::ostringstream output;

    writeCloneCandidatesCsv(output, report);

    const std::string expected =
        "type,student_a,assignment_a,path_a,start_line_a,end_line_a,"
        "student_b,assignment_b,path_b,start_line_b,end_line_b\n"
        "Type-1,student01,assignment3.cpp,student01/assignment3.cpp,4,29,"
        "student17,assignment3.cpp,student17/assignment3.cpp,4,29\n"
        "Type-2-only,student05,assignment3.cpp,student05/assignment3.cpp,34,64,"
        "student12,assignment3.cpp,student12/assignment3.cpp,32,62\n";

    const bool candidatesPassed =
        output.str() == expected;

    AnalysisReport emptyReport;
    std::ostringstream emptyOutput;

    writeCloneCandidatesCsv(emptyOutput, emptyReport);

    const std::string header =
        "type,student_a,assignment_a,path_a,start_line_a,end_line_a,"
        "student_b,assignment_b,path_b,start_line_b,end_line_b\n";

    const bool emptyPassed =
        emptyOutput.str() == header;

    AnalysisReport commaReport;

    commaReport.cloneCandidates.push_back(CloneSummaryEntry{
        CloneCandidateKind::Type1,
        "student,01/assignment3.cpp", 4, 29,
        "student17/assignment3.cpp", 4, 29});

    std::ostringstream commaOutput;

    writeCloneCandidatesCsv(commaOutput, commaReport);

    const bool commaPassed =
        commaOutput.str().find(
            "\"student,01\",assignment3.cpp,"
            "\"student,01/assignment3.cpp\"") !=
        std::string::npos;

    std::cout << "Clone candidate records: "
              << (candidatesPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Empty candidate list: "
              << (emptyPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Special character escaping: "
              << (commaPassed ? "PASS" : "FAIL") << '\n';

    return (candidatesPassed && emptyPassed && commaPassed)
               ? 0
               : 1;
}