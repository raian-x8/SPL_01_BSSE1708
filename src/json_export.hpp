#pragma once

#include <ostream>
#include <string>

#include "analysis_report.hpp"

void writeJsonString(
    std::ostream &output,
    const std::string &value);

void writeJsonSummary(
    std::ostream &output,
    const AnalysisReport &report);

void writeJsonCloneCandidates(
    std::ostream &output,
    const AnalysisReport &report);

void writeJsonStudentFindings(
    std::ostream &output,
    const AnalysisReport &report);

void writeAnalysisReportJson(
    std::ostream &output,
    const AnalysisReport &report);

void writeJsonHumanReviewIndicators(
    std::ostream &output,
    const AnalysisReport &report);