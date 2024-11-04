#include "Tokenizer.h"

std::vector<DSString> tokenize(DSString & phrase) {
    int start = 0; // Tracks the start of each word
    int end = 0; // Tracks the end of each word
    DSString word; // Temporary storage for each token (word)
    std::vector<DSString> tokens; // Vector to store tokens

    // Remove any leading spaces from the input phrase
    while (phrase[0] == ' ') {
        phrase.remove(0);
    }

    // Clean up the phrase by removing non-alphabetic characters and redundant spaces
    for (size_t i = 0; i < phrase.length(); i++) {
        if (!isalpha(phrase[i]) && phrase[i] != ' ') { // Remove non-alphabetic characters
            phrase.remove(i); 
            if (i != 0) { // Adjust index to account for removal
                i--;
            }
        }
        // Remove any extra spaces that appear consecutively
        if (i > 0 && phrase[i] == ' ' && phrase[i-1] == ' ') {
            phrase.remove(i); 
            i--;
        }
    }

    // Tokenize the cleaned phrase
    while (start < phrase.length()) {
        // Move `end` to the next space or end of the phrase
        while (phrase[end] != ' ' && end < phrase.length()) {
            end++; 
        }

        // Extract a word if `start` and `end` are not the same
        if (end != start) { 
            word = phrase.substring(start, end - start); // Get substring from start to end
            end++; // Move `end` to the character after the space
            start = end; // Move `start` to the beginning of the next potential word
            tokens.push_back(word); // Add the word to the tokens vector
        } else {
            // Skip spaces if `start` and `end` are the same
            start++;
            end++;
        }
    }
    return tokens;
}