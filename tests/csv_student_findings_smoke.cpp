#include <iostream>
#include <sstream>
#include <string>

#include "../src/csv_export.hpp"

int main()
{
    AnalysisReport report;

    report.studentFindings.push_back(
        StudentStyleFinding{"student01", true, true, true, false});

    report.studentFindings.push_back(
        StudentStyleFinding{"student15", false, false, false, false});

    report.studentFindings.push_back(
        StudentStyleFinding{"student,99", true, false, true, true});

    std::ostringstream output;

    writeStudentFindingsCsv(output, report);

    const std::string header =
        "student_id,naming_evaluated,naming_deviation,naming_status,"
        "commenting_evaluated,commenting_deviation,commenting_status\n";

    const std::string expected =
        header +
        "student01,true,true,deviation,true,false,no_deviation\n"
        "student15,false,false,not_evaluable,false,false,not_evaluable\n"
        "\"student,99\",true,false,no_deviation,true,true,deviation\n";

    const bool findingsPassed =
        output.str() == expected;

    const bool nonEvaluablePassed =
        output.str().find(
            "student15,false,false,not_evaluable,"
            "false,false,not_evaluable") != std::string::npos;

    const bool escapingPassed =
        output.str().find("\"student,99\"") != std::string::npos;

    AnalysisReport emptyReport;
    std::ostringstream emptyOutput;

    writeStudentFindingsCsv(emptyOutput, emptyReport);

    const bool emptyPassed =
        emptyOutput.str() == header;

    std::cout << "Student findings records: "
              << (findingsPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Non-evaluable history: "
              << (nonEvaluablePassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Student ID escaping: "
              << (escapingPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Empty findings list: "
              << (emptyPassed ? "PASS" : "FAIL") << '\n';

    return (findingsPassed &&
            nonEvaluablePassed &&
            escapingPassed &&
            emptyPassed)
               ? 0
               : 1;
}