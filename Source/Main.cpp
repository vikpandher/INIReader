// =============================================================================
// @BRIEF 
// @AUTHOR Vik Pandher
// @DATE 

#include <cerrno>
#include <fstream>
#include <iostream>



int CompareStrings(const char* string1, const char* string2);

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr << "ERROR: Not enough arguments" << std::endl;

        return 1;
    }

    // TODO: process arguments

    return 0;
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