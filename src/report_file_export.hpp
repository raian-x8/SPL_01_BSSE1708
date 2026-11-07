#pragma once

#include <filesystem>
#include <string>

#include "analysis_report.hpp"

bool exportAnalysisReportFiles(
    const AnalysisReport &report,
    const std::filesystem::path &outputRoot,
    std::filesystem::path &createdRunDirectory,
    std::string &errorMessage);