#pragma once

#include <cstddef>
#include <string>
#include <vector>

struct AssignmentOrderResult
{
    bool valid = false;
    std::vector<std::size_t> orderedPositions;
    std::string reason;
};

AssignmentOrderResult determineAssignmentOrder(
    const std::vector<std::string> &filenames);