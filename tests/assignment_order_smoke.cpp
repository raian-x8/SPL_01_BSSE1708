#include <iostream>
#include <string>
#include <vector>

#include "../src/assignment_order.hpp"

bool reportTest(const std::string &name, bool passed)
{
    std::cout << name << ": "
              << (passed ? "PASS" : "FAIL") << '\n';

    return passed;
}

int main()
{
    bool allPassed = true;

    // Test 1: Numeric ordering rather than alphabetical ordering.
    const AssignmentOrderResult numeric =
        determineAssignmentOrder({"assignment10.cpp",
                                  "assignment2.cpp",
                                  "assignment1.cpp"});

    allPassed = reportTest(
                    "Numeric assignment ordering",
                    numeric.valid &&
                        numeric.orderedPositions ==
                            std::vector<std::size_t>{2, 1, 0}) &&
                allPassed;

    // Test 2: Accept supported separators and C source files.
    const AssignmentOrderResult variants =
        determineAssignmentOrder({"assignment_3.c",
                                  "Assignment-1.cpp",
                                  "assignment2.cpp"});

    allPassed = reportTest(
                    "Supported filename variants",
                    variants.valid &&
                        variants.orderedPositions ==
                            std::vector<std::size_t>{1, 2, 0}) &&
                allPassed;

    // Test 3: Reject filenames with no assignment number.
    const AssignmentOrderResult missingNumber =
        determineAssignmentOrder({"assignment1.cpp",
                                  "assignment.cpp"});

    allPassed = reportTest(
                    "Missing assignment number",
                    !missingNumber.valid) &&
                allPassed;

    // Test 4: Reject duplicate assignment numbers.
    const AssignmentOrderResult duplicates =
        determineAssignmentOrder({"assignment01.cpp",
                                  "assignment1.c"});

    allPassed = reportTest(
                    "Duplicate assignment numbers",
                    !duplicates.valid) &&
                allPassed;

    // Test 5: Reject unsupported naming schemes.
    const AssignmentOrderResult unknown =
        determineAssignmentOrder({"assignment1.cpp",
                                  "solution.cpp"});

    allPassed = reportTest(
                    "Unsupported filenames",
                    !unknown.valid) &&
                allPassed;

    // Test 6: Reject unexpected text after the number.
    const AssignmentOrderResult invalidSuffix =
        determineAssignmentOrder({"assignment1.cpp",
                                  "assignment2final.cpp"});

    allPassed = reportTest(
                    "Invalid assignment suffix",
                    !invalidSuffix.valid) &&
                allPassed;

    // Test 7: Reject unsupported extensions.
    const AssignmentOrderResult invalidExtension =
        determineAssignmentOrder({"assignment1.cpp",
                                  "assignment2.txt"});

    allPassed = reportTest(
                    "Unsupported extension",
                    !invalidExtension.valid) &&
                allPassed;

    // Test 8: Reject excessively large numbers.
    const AssignmentOrderResult overflow =
        determineAssignmentOrder({"assignment1.cpp",
                                  "assignment99999999999999999999999999999999.cpp"});

    allPassed = reportTest(
                    "Assignment number overflow",
                    !overflow.valid) &&
                allPassed;

    // Test 9: Handle an empty list safely.
    const AssignmentOrderResult empty =
        determineAssignmentOrder({});

    allPassed = reportTest(
                    "Empty assignment list",
                    !empty.valid) &&
                allPassed;

    return allPassed ? 0 : 1;
}