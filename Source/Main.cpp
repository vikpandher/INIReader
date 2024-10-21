// =============================================================================
// @BRIEF This tests the IniReader. It reads in an ini file and then outputs a
//        copy of the ini file.
// @AUTHOR Vik Pandher
// @DATE 2024-10-20

#include "IniReader.h"

#include <cerrno>
#include <fstream>
#include <iostream>
#include <sstream>



void TestIniReader_01();
int TestIniReader_02(int argc, char** argv);
void OutputUsageText();
int CompareStrings(const char* string1, const char* string2);

int main(int argc, char** argv)
{
    TestIniReader_01();

    // return TestIniReader_02(argc, argv);

    return 0;
}

void TestIniReader_01()
{
    // Example ini string
    std::string iniContent = R"(
    # A comment
    Var0 = "abc"

    This line is ignored.

    [Section]
    Var1 = String
    Var2 = 10
    Var3 = 0.4f
    Var4 = =

    [Section2]
    Var4 = 8 # Another comment
    )";

    // Use string stream to simulate file input
    std::istringstream inputStream(iniContent);
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> sections;

    // Read the INI data
    ReadIniStream(inputStream, sections);

    // Simulate output stream (writing the ini back out)
    std::ostringstream outputStream;
    WriteIniStream(sections, outputStream);

    // Print the result
    std::cout << outputStream.str() << std::endl;
}

int TestIniReader_02(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr << "ERROR: Not enough arguments" << std::endl;
        std::cout << std::endl;
        OutputUsageText();

        return 1;
    }

    if (CompareStrings(argv[1], argv[2]))
    {
        std::cerr << "ERROR: input file and output file cannot have the same name" << std::endl;
        std::cout << std::endl;
        OutputUsageText();

        return 1;
    }

    // TODO

    return 0;
}

void OutputUsageText()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "    ./" << PROJECT_NAME << " <input_file> <output_file>" << std::endl;
    std::cout << std::endl;
    std::cout << "Description:" << std::endl;
    std::cout << "    This program tests the IniReader. It reads an ini file and then outputs a" << std::endl;
    std::cout << "    copy of the ini file." << std::endl;
}

int CompareStrings(const char* string1, const char* string2)
{
    while (*string1 != '\0' && *string2 != '\0' && *string1 == *string2)
    {
        string1++;
        string2++;
    }

    if (*string1 == '\0' && *string2 == '\0') {
        return 0; // Strings are equal
    }
    else {
        return *string1 - *string2; // Return the ASCII difference
    }
}