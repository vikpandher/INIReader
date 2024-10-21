// =============================================================================
// @BRIEF These functions read an ".ini" and store its contents into a map.
//        The "#" character is treated as the start of a comment.
// @AUTHOR Vik Pandher
// @DATE 2024-10-20

#include <istream>
#include <ostream>
#include <string>
#include <unordered_map>


// This function reads an input stream and populates a map. The input is
// expected to be in the ".ini" format. The map's keys are section names and
// the values are a second level of maps. The second level maps' keys are
// variable names and the values are the associated variable values.
void ReadIniStream(std::istream& inputStream,
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& sections);

// This function writes to an output stream from a map. The output is in the
// ".ini" format. The map's keys are section names and the values are a second
// level of maps. The second level maps' keys are variable names and the values
// are the associated variable values.
void WriteIniStream(const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& sections,
    std::ostream& outputStream);

// This function takes a string and returns a verions of it with the whitespace
// infront and at the end removed.
std::string TrimWhiteSpace(const std::string& str);

// -----------------------------------------------------------------------------

inline void ReadIniStream(std::istream& inputStream,
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& sections)
{
    std::string line, currentSection;

    while (std::getline(inputStream, line))
    {
        // Remove comments (everything after '#')
        line = line.substr(0, line.find('#'));
        line = TrimWhiteSpace(line);

        // Ignore empty lines
        if (line.empty())
        {
            continue;
        }

        // Check if it's a section (lines that look like: [Section])
        if (line.front() == '[' && line.back() == ']')
        {
            currentSection = line.substr(1, line.size() - 2);
            currentSection = TrimWhiteSpace(currentSection);
            continue;
        }

        // Parse key-value pairs (lines that look like: Var0 = "abc")
        size_t equalPos = line.find('=');
        if (equalPos != std::string::npos)
        {
            std::string key = TrimWhiteSpace(line.substr(0, equalPos));
            std::string value = TrimWhiteSpace(line.substr(equalPos + 1));

            // // Remove quotes around string values if present
            // if (!value.empty() && value.front() == '"' && value.back() == '"')
            // {
            //     value = value.substr(1, value.size() - 2);
            // }

            sections[currentSection][key] = value;
        }
    }
}

inline void WriteIniStream(const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& sections,
    std::ostream& outputStream)
{
    for (const auto& section : sections)
    {
        if (!section.first.empty())
        {
            outputStream << "[" << section.first << "]" << std::endl;
        }

        for (const auto& kv : section.second)
        {
            // outputStream << kv.first << " = \"" << kv.second << "\"" << std::endl;

            outputStream << kv.first << " = " << kv.second << std::endl;
        }

        outputStream << std::endl;  // Blank line after each section
    }
}

inline std::string TrimWhiteSpace(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
}