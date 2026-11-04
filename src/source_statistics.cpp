#include "source_statistics.hpp"

#include <cctype>
#include <sstream>

SourceStatistics calculateSourceStatistics(
    const std::string &sourceCode,
    std::size_t tokenCount,
    std::size_t recognizedFunctionBodies)
{
    SourceStatistics statistics;

    statistics.tokenCount = tokenCount;
    statistics.recognizedFunctionBodies = recognizedFunctionBodies;

    std::istringstream input(sourceCode);
    std::string line;

    while (std::getline(input, line))
    {
        ++statistics.totalLines;

        bool isBlank = true;

        for (char character : line)
        {
            if (!std::isspace(static_cast<unsigned char>(character)))
            {
                isBlank = false;
                break;
            }
        }

        if (isBlank)
        {
            ++statistics.blankLines;
        }
    }

    return statistics;
}