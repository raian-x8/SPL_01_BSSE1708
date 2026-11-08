#include "report_file_export.hpp"

#include <fstream>
#include <system_error>

#include "csv_export.hpp"
#include "json_export.hpp"

namespace fs = std::filesystem;

bool exportAnalysisReportFiles(
    const AnalysisReport &report,
    const fs::path &outputRoot,
    fs::path &createdRunDirectory,
    std::string &errorMessage)
{
    createdRunDirectory.clear();
    errorMessage.clear();

    std::error_code ec;

    // Create the parent report directory if needed.
    fs::create_directories(outputRoot, ec);

    if (ec)
    {
        errorMessage =
            "Could not create report directory: " + ec.message();

        return false;
    }

    // Create a new directory for this analysis run.
    for (unsigned int number = 1; number <= 10000; ++number)
    {
        const fs::path candidate =
            outputRoot / ("run_" + std::to_string(number));

        ec.clear();

        if (fs::create_directory(candidate, ec))
        {
            createdRunDirectory = candidate;
            break;
        }

        if (ec)
        {
            errorMessage =
                "Could not create run directory: " + ec.message();

            return false;
        }
    }

    if (createdRunDirectory.empty())
    {
        errorMessage = "No available report run directory.";
        return false;
    }

    // Open a report file, serialize its contents, and verify the write.
    auto writeFile = [&](const char *fileName, auto writer) -> bool
    {
        const fs::path filePath =
            createdRunDirectory / fileName;

        std::ofstream file(filePath);

        if (!file)
        {
            errorMessage =
                "Could not open output file: " + filePath.string();

            return false;
        }

        writer(file, report);

        file.close();

        if (!file)
        {
            errorMessage =
                "Could not write output file: " + filePath.string();

            return false;
        }

        return true;
    };

    // Generate the CSV overview.
    if (!writeFile(
            "analysis_overview.csv",
            writeAnalysisOverviewCsv))
    {
        return false;
    }

    // Generate detailed clone candidates.
    if (!writeFile(
            "clone_candidates.csv",
            writeCloneCandidatesCsv))
    {
        return false;
    }

    // Generate student stylometric findings.
    if (!writeFile(
            "student_findings.csv",
            writeStudentFindingsCsv))
    {
        return false;
    }

    // Generate the complete JSON report.
    if (!writeFile(
            "analysis_report.json",
            writeAnalysisReportJson))
    {
        return false;
    }

    return true;
}