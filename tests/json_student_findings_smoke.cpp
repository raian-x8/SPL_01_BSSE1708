#include <iostream>
#include <sstream>
#include <string>

#include "../src/json_export.hpp"

int main()
{
    AnalysisReport report;

    report.studentFindings.push_back(
        StudentStyleFinding{"student01", true, true, true, false});

    report.studentFindings.push_back(
        StudentStyleFinding{"student15", false, false, false, false});

    report.studentFindings.push_back(
        StudentStyleFinding{"student\"99", true, false, true, true});

    std::ostringstream output;

    writeJsonStudentFindings(output, report);

    const std::string text = output.str();

    const bool studentsPassed =
        text.find("\"student_id\": \"student01\"") !=
            std::string::npos &&
        text.find("\"student_id\": \"student15\"") !=
            std::string::npos;

    const bool booleansPassed =
        text.find("\"evaluated\": true") != std::string::npos &&
        text.find("\"deviation\": false") != std::string::npos;

    const bool nonEvaluablePassed =
        text.find("\"status\": \"not_evaluable\"") !=
        std::string::npos;

    const bool separatorPassed =
        text.find("  },\n  {") != std::string::npos;

    const bool escapingPassed =
        text.find("student\\\"99") != std::string::npos;

    AnalysisReport emptyReport;
    std::ostringstream emptyOutput;

    writeJsonStudentFindings(emptyOutput, emptyReport);

    const bool emptyPassed =
        emptyOutput.str() == "[]";

    std::cout << "Student JSON records: "
              << (studentsPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "JSON Boolean values: "
              << (booleansPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Non-evaluable histories: "
              << (nonEvaluablePassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Array separators: "
              << (separatorPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Student ID escaping: "
              << (escapingPassed ? "PASS" : "FAIL") << '\n';

    std::cout << "Empty findings array: "
              << (emptyPassed ? "PASS" : "FAIL") << '\n';

    return (studentsPassed &&
            booleansPassed &&
            nonEvaluablePassed &&
            separatorPassed &&
            escapingPassed &&
            emptyPassed)
               ? 0
               : 1;
}