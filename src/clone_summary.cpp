#include "clone_summary.hpp"

#include <algorithm>
#include <filesystem>
#include <tuple>
#include <utility>

namespace
{
    bool validRegion(const std::vector<Token> &tokens,
                     const CodeRegion &region)
    {
        return region.beginTokenIndex < region.endTokenIndex &&
               region.endTokenIndex <= tokens.size();
    }

    std::string studentFolderFromPath(const std::string &relativePath)
    {
        const std::filesystem::path path(relativePath);

        if (!path.has_parent_path())
        {
            return "";
        }

        return (*path.begin()).string();
    }

    void printLocation(std::ostream &output,
                       const std::string &relativePath,
                       std::size_t startLine,
                       std::size_t endLine)
    {
        const std::string student = studentFolderFromPath(relativePath);
        const std::string filename =
            std::filesystem::path(relativePath).filename().string();

        output << "    ";

        if (!student.empty())
        {
            output << "Student: " << student << " | ";

            if (filename.rfind("assignment", 0) == 0)
            {
                output << "Assignment: " << filename;
            }
            else
            {
                output << "File: " << filename;
            }
        }
        else
        {
            output << "File: " << relativePath;
        }

        output << " | lines " << startLine
               << " to " << endLine << '\n';
    }
}

bool appendCloneSummaryEntry(
    std::vector<CloneSummaryEntry> &entries,
    CloneCandidateKind kind,
    const std::string &firstRelativePath,
    const std::vector<Token> &firstTokens,
    const CodeRegion &firstRegion,
    const std::string &secondRelativePath,
    const std::vector<Token> &secondTokens,
    const CodeRegion &secondRegion)
{
    if (!validRegion(firstTokens, firstRegion) ||
        !validRegion(secondTokens, secondRegion))
    {
        return false;
    }

    CloneSummaryEntry entry{
        kind,
        firstRelativePath,
        firstTokens[firstRegion.beginTokenIndex].line,
        firstTokens[firstRegion.endTokenIndex - 1].line,
        secondRelativePath,
        secondTokens[secondRegion.beginTokenIndex].line,
        secondTokens[secondRegion.endTokenIndex - 1].line};

    // Canonicalize file order so a pair has one predictable presentation.
    if (entry.secondPath < entry.firstPath)
    {
        std::swap(entry.firstPath, entry.secondPath);
        std::swap(entry.firstStartLine, entry.secondStartLine);
        std::swap(entry.firstEndLine, entry.secondEndLine);
    }

    entries.push_back(entry);

    return true;
}

void printCloneSummaryDetails(
    std::ostream &output,
    const std::vector<CloneSummaryEntry> &entries)
{
    output << "\nDetailed clone candidate summary:\n";

    if (entries.empty())
    {
        output << "No body-level clone candidates found.\n";
        return;
    }

    std::vector<CloneSummaryEntry> sorted = entries;

    std::sort(sorted.begin(), sorted.end(),
              [](const CloneSummaryEntry &left,
                 const CloneSummaryEntry &right)
              {
                  return std::tie(left.kind, left.firstPath,
                                  left.secondPath, left.firstStartLine,
                                  left.secondStartLine) <
                         std::tie(right.kind, right.firstPath,
                                  right.secondPath, right.firstStartLine,
                                  right.secondStartLine);
              });

    for (const CloneCandidateKind kind :
         {CloneCandidateKind::Type1, CloneCandidateKind::Type2Only})
    {
        output << '\n'
               << (kind == CloneCandidateKind::Type1
                       ? "Type-1 candidate pairs:\n"
                       : "Type-2-only candidate pairs:\n");

        std::size_t groupCount = 0;

        for (const CloneSummaryEntry &entry : sorted)
        {
            if (entry.kind != kind)
            {
                continue;
            }

            output << "  Candidate #" << ++groupCount << ":\n";
            printLocation(output, entry.firstPath,
                          entry.firstStartLine, entry.firstEndLine);
            printLocation(output, entry.secondPath,
                          entry.secondStartLine, entry.secondEndLine);
        }

        if (groupCount == 0)
        {
            output << "  None.\n";
        }
    }
}
