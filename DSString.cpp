#include "DSString.h" // Include the header file for DSString class definition

/* 
 * Implement the functions defined in DSString.h. You may add more functions as needed
 * for the project. 
 *
 * Note that c-strings don's store an explicit length but use `\0` as the terminator symbol
 * but your class should store its length in a member variable. 
 * DDO NOT USE C-STRING FUNCTIONS <string.h> or <cstring>.
 */  

// Default constructor: initializes an empty DSString
DSString::DSString() {
    len = 0;                 // Set the length to 0
    data = new char[1];      // Allocate space for one character (for the null terminator)
    data[0] = '\0';          // Set the null terminator
}

// Constructor: initializes DSString from a C-string
DSString::DSString(const char *cString) {
    len = 0;                 // Initialize length to 0
    while (cString[len] != '\0') { // Calculate length of cString
        len += 1;
    }
    data = new char[len + 1];  // Allocate memory for string plus null terminator
    for (int i = 0; i < len; i++) {  // Copy characters from cString
        data[i] = cString[i];
    }
    data[len] = '\0';         // Add null terminator
}

// Copy constructor: initializes DSString by copying another DSString
DSString::DSString(const DSString & cString) {
    len = cString.length();   // Set length equal to the length of cString
    data = new char[len + 1]; // Allocate memory for data
    for (int i = 0; i < len; i++) { // Copy characters from cString
        data[i] = cString.data[i];
    }
    data[len] = '\0';         // Add null terminator
}

// Assignment operator: assigns one DSString to another
DSString &DSString::operator=(const DSString &rhs) {
    if (rhs == *this) {       // Check for self-assignment
        return *this;
    }
    delete[] data;            // Delete existing data
    len = rhs.len;            // Copy length
    data = new char[len + 1]; // Allocate memory for new data

    for (size_t i = 0; i < len; i++) { // Copy characters from rhs
        data[i] = rhs.data[i];
    }
    data[len] = '\0';         // Add null terminator
    return *this;
}

// Destructor: deallocates memory used by DSString
DSString::~DSString() {
    delete[] data;
}

// Method to return the length of the string
size_t DSString::length() const {
    return len;
}

// Overloaded subscript operator: allows access to characters by index
char& DSString::operator[](size_t index) {
    return data[index];
}

// Overloaded addition operator: concatenates two DSStrings
DSString DSString::operator+(const DSString &rhs) const {
    size_t combinedLen = len + rhs.length() + 1; // Calculate combined length
    char* newData = new char[combinedLen];       // Allocate memory for new data
    newData[len] = '\0';                         // Initialize null terminator

    for (size_t i = 0; i < len; i++) {           // Copy characters from current string
        newData[i] = data[i];
    }
    for (size_t i = 0; i < rhs.length(); i++) {  // Append characters from rhs
        newData[len + i] = rhs.data[i];
    }
    return DSString(newData);                    // Return concatenated string
}

// Overloaded equality operator: compares two DSStrings for equality
bool DSString::operator==(const DSString & cString) const {
    if (len != cString.length()) {               // Check if lengths differ
        return false;
    }
    for (size_t i = 0; i < cString.length(); i++) { // Compare characters
        if (data[i] != cString.data[i]) {
            return false;
        }
    }
    return true;                                 // Return true if all characters match
}

// Overloaded less-than operator: compares two DSStrings lexicographically
bool DSString::operator<(const DSString& rhs) const {
    for (size_t i = 0; i < len && i < rhs.len; i++) { // Compare characters until end of shorter string
        if (data[i] < rhs.data[i]) {
            return true;
        } else if (data[i] > rhs.data[i]) {
            return false;
        }
    }

    if (len == rhs.len) {    // If lengths are equal, strings are equal
        return false;
    }
    return len < rhs.len;    // Otherwise, shorter string is "less than" longer string
}

// Method to create a substring starting at `start` with length `numChars`
DSString DSString::substring(size_t start, size_t numChars) const {
    char *subString = new char[numChars + 1];  // Allocate memory for substring
    for (size_t i = 0; i < numChars; i++) {    // Copy characters from start position
        subString[i] = data[start + i];
    }
    subString[numChars] = '\0';                // Add null terminator
    DSString subStr = DSString(subString);     // Create DSString from substring
    delete[] subString;                        // Free temporary memory
    return subStr;
}

// Method to convert all characters to lowercase
DSString DSString::toLower() const {
    for (int i = 0; i < len; i++) {
        if (int(data[i]) < 91) {               // Check if uppercase (ASCII < 91)
            data[i] = char(int(data[i]) + 32); // Convert to lowercase
        }
    }
}

// Method to return a C-string representation of DSString
const char* DSString::c_str() const {
    return data;
}

// Overloaded output operator to print DSString
std::ostream &operator<<(std::ostream & out, const DSString & dss) {
    for (size_t i = 0; i < dss.length(); i++) { // Output each character
        out.put(dss.data[i]);
    }
    return out;
}

// Overloaded input function to read line into DSString
std::istream& getline(std::istream& in, DSString& dsstr) {
    delete[] dsstr.data;             // Clear existing data
    dsstr.len = 0;                   // Reset length

    size_t tmpLen = 5;               // Initial buffer size
    char* newData = new char[tmpLen]; // Allocate initial buffer

    char tmpchar;
    while (in.get(tmpchar) && tmpchar != '\n') { // Read until newline
        dsstr.len++;                // Increase length

        if (dsstr.len > tmpLen) {   // Expand buffer if needed
            tmpLen *= 2;
            char* tmpData = new char[tmpLen];  // Allocate new buffer

            for (size_t i = 0; i < dsstr.len - 1; i++) { // Copy old data to new buffer
                tmpData[i] = newData[i];
            }
            delete[] newData;       // Delete old buffer
            newData = tmpData;      // Set new buffer as data
        }
        newData[dsstr.len - 1] = tmpchar; // Add new character to buffer
    }
    dsstr.data = new char[dsstr.len + 1]; // Allocate exact-sized data array
    for (size_t i = 0; i < dsstr.len; i++) {
        dsstr.data[i] = newData[i];
    }
    dsstr.data[dsstr.len] = '\0';  // Add null terminator
    delete[] newData;              // Free temporary buffer

    return in;
}

// Overloaded input function to read line into DSString with custom delimiter
std::istream& getline(std::istream& in, DSString& dsstr, char delim) {
    delete[] dsstr.data;
    dsstr.len = 0;
    size_t tmpLen = 5;
    char* newData = new char[tmpLen];
    char tmpchar;
    while (in.get(tmpchar) && tmpchar != delim) {
        dsstr.len++;
        if (dsstr.len > tmpLen) {
            tmpLen *= 2;
            char* tmpData = new char[tmpLen];
            for (size_t i = 0; i < dsstr.len - 1; i++) {
                tmpData[i] = newData[i];
            }
            delete[] newData;
            newData = tmpData;
        }
        newData[dsstr.len - 1] = tmpchar;
    }
    // create new corect sized array
    dsstr.data = new char[dsstr.len + 1];
    for (size_t i = 0; i < dsstr.len; i++) {
        dsstr.data[i] = newData[i];
    }
    dsstr.data[dsstr.len] = '\0';
    delete[] newData;
    return in;
}

// Overloaded inequality operator: checks if two DSStrings are not equal
bool DSString::operator!=(const DSString& rhs) const {
    if (len != rhs.len) {
        return true;
    }
    for (size_t i = 0; i < len; i++) {
        if (data[i] != rhs.data[i]) {
            return true;
        }
    }
    return false;
}

// Method to remove character at specified index
void DSString::remove(size_t index) {
    if (index >= len) {            // Check if index
       throw std::out_of_range("Index out of range");
    }
    if (len == 1) {
        return;
    }
    char* newcString = new char[len];
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (i != index) {
            newcString[j] = data[i];
            j++;
        }
    }

    // clean out old data
    delete[] data;
    data = newcString;
    len = len - 1;

    // add null terminator
    data[len] = '\0';
}
