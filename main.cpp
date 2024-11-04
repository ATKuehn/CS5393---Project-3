#include "Classifier.h"     // Include Classifier class for sentiment analysis functions
#include "DSString.h"       // Include custom DSString class for string handling
#include <fstream>          // Include file stream library for file I/O
#include <iostream>         // Include iostream for console output

// Function declarations for opening input and output files
std::ifstream openFile(DSString filename);
std::ofstream openOutputFile(DSString filename);

int main(int argc, char** argv) // Main function entry point
{
    std::cout << "I will be a sentiment analyzer!" << std::endl; // Initial message output

    // Initialize dataset file paths for training, testing, and results
    DSString trainingDataset = "data/train_dataset_20k.csv";
    DSString testDataset = "data/test_dataset_10k.csv";
    DSString actualDataResults = "data/test_dataset_sentiment_10k.csv";
    DSString predictionOutput = "results.csv";
    DSString predictionResults = "accuracy.csv";

    Classifier sentimentClassifier; // Create a Classifier object

    // Open training dataset file and train the classifier
    std::ifstream trainDataStream = openFile(trainingDataset);
    sentimentClassifier.train(trainDataStream);
    trainDataStream.close(); // Close training data file

    // Open test data file and output file for prediction results
    std::ifstream testData = openFile(testDataset);
    std::ofstream resultData = openOutputFile(predictionOutput);
    sentimentClassifier.predict(testData, resultData);
    testData.close();         // Close test data file
    resultData.close();       // Close prediction output file

    // Open actual data results file and output file for accuracy results
    std::ifstream truthDataStream = openFile(actualDataResults);
    std::ofstream accuracyStream = openOutputFile(predictionResults);
    sentimentClassifier.evaluatePredictions(truthDataStream, accuracyStream);
    truthDataStream.close();   // Close actual results file
    accuracyStream.close();    // Close accuracy output file

    return 0; // Return success status
}

// Function to open a file for reading, throws error if file fails to open
std::ifstream openFile(DSString filename) {
    std::ifstream file;
    file.open(filename.c_str()); // Open file using filename's C-string representation
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open File"); // Error handling if file doesn't open
    }
    return file; // Return opened file stream
}

// Function to open a file for writing, throws error if file fails to open
std::ofstream openOutputFile(DSString filename) {
    std::ofstream file;
    file.open(filename.c_str()); // Open file using filename's C-string representation
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open File"); // Error handling if file doesn't open
    }
    return file; // Return opened file stream
}
