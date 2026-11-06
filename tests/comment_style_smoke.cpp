#include <iostream>
#include <string>

#include "../src/comment_style.hpp"
#include "../src/preprocessor.hpp"

bool checkCommentStatistics(
    const std::string &testName,
    const std::string &source,
    std::size_t expectedLines,
    std::size_t expectedCommentOnly,
    std::size_t expectedInline)
{
    const std::string cleaned = removeComments(source);

    const CommentStyleStatistics result =
        calculateCommentStyleStatistics(source, cleaned);

    const bool passed =
        result.commentLines == expectedLines &&
        result.commentOnlyLines == expectedCommentOnly &&
        result.inlineCommentLines == expectedInline;

    std::cout << testName << ": "
              << (passed ? "PASS" : "FAIL")
              << '\n';

    return passed;
}

int main()
{
    bool allPassed = true;

    allPassed =
        checkCommentStatistics(
            "No comments",
            "int value = 2;\n",
            0, 0, 0) &&
        allPassed;

    allPassed =
        checkCommentStatistics(
            "Line and inline comments",
            "// header\nint value = 2; // note\n",
            2, 1, 1) &&
        allPassed;

    allPassed =
        checkCommentStatistics(
            "Block comments",
            "int value = /* note */ 2;\n/* alone */\n",
            2, 1, 1) &&
        allPassed;

    allPassed =
        checkCommentStatistics(
            "Multiline block comments",
            "int a = 1; /* begin\nmiddle\nend */ int b = 2;\n",
            3, 1, 2) &&
        allPassed;

    allPassed =
        checkCommentStatistics(
            "Comment symbols inside literals",
            "const char *url = \"https://example.com/*text*/\";\n",
            0, 0, 0) &&
        allPassed;

    allPassed =
        checkCommentStatistics(
            "Empty source",
            "",
            0, 0, 0) &&
        allPassed;

    return allPassed ? 0 : 1;
}