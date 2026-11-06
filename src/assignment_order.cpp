#include "assignment_order.hpp"

#include <cctype>
#include <limits>
#include <map>

namespace
{
    bool parseAssignmentNumber(
        const std::string &filename,
        std::size_t &number)
    {
        const std::size_t dot = filename.find_last_of('.');

        if (dot == std::string::npos)
        {
            return false;
        }

        const std::string extension = filename.substr(dot);

        if (extension != ".c" && extension != ".cpp")
        {
            return false;
        }

        const std::string stem = filename.substr(0, dot);
        const std::string prefix = "assignment";

        if (stem.size() <= prefix.size())
        {
            return false;
        }

        // Match "assignment" without case sensitivity.
        for (std::size_t i = 0; i < prefix.size(); ++i)
        {
            const unsigned char character =
                static_cast<unsigned char>(stem[i]);

            if (std::tolower(character) != prefix[i])
            {
                return false;
            }
        }

        std::size_t position = prefix.size();

        // Allow assignment_3 and assignment-3.
        if (stem[position] == '_' || stem[position] == '-')
        {
            ++position;
        }

        if (position == stem.size())
        {
            return false;
        }

        std::size_t value = 0;

        // Read the number while checking for integer overflow.
        for (; position < stem.size(); ++position)
        {
            const unsigned char character =
                static_cast<unsigned char>(stem[position]);

            if (!std::isdigit(character))
            {
                return false;
            }

            const std::size_t digit =
                static_cast<std::size_t>(stem[position] - '0');

            const std::size_t maximum =
                std::numeric_limits<std::size_t>::max();

            if (value > (maximum - digit) / 10)
            {
                return false;
            }

            value = value * 10 + digit;
        }

        number = value;
        return true;
    }
}

AssignmentOrderResult determineAssignmentOrder(
    const std::vector<std::string> &filenames)
{
    AssignmentOrderResult result;

    if (filenames.empty())
    {
        result.reason = "No assignment files provided.";
        return result;
    }

    // A map automatically orders numeric assignment keys.
    std::map<std::size_t, std::size_t> numberedFiles;

    for (std::size_t i = 0; i < filenames.size(); ++i)
    {
        std::size_t assignmentNumber = 0;

        if (!parseAssignmentNumber(
                filenames[i], assignmentNumber))
        {
            result.reason =
                "Unsupported assignment filename: " + filenames[i];
            return result;
        }

        const bool inserted =
            numberedFiles.emplace(assignmentNumber, i).second;

        if (!inserted)
        {
            result.reason =
                "Duplicate assignment number: " +
                std::to_string(assignmentNumber);

            return result;
        }
    }

    for (const auto &entry : numberedFiles)
    {
        result.orderedPositions.push_back(entry.second);
    }

    result.valid = true;
    return result;
}