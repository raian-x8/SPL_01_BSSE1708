#pragma once

#include <ostream>
#include <string>

#include "analysis_report.hpp"

std::string escapeCsvField(const std::string &field);

void writeAnalysisOverviewCsv(
    std::ostream &output,
    const AnalysisReport &report);

void writeCloneCandidatesCsv(
    std::ostream &output,
    const AnalysisReport &report);

void writeStudentFindingsCsv(
    std::ostream &output,
    const AnalysisReport &report);