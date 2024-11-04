#include "Classifier.h" // Include Classifier class definition

// Train function: Reads and processes each line in the training data to build a sentiment model
void Classifier::train(std::istream& trainingData) {
    size_t trainingTokens = 0; // Track the number of tokens in training data
    std::vector<DSString> uniqueTokens; // Vector to store unique words (tokens)
    DSString line;
    getline(trainingData, line); // Read first line (usually headers)
    
    while (!trainingData.eof()) { // Process until end of file
        DSString tweet, sentiment, id, date, query, user;
        
        // Parse each column of the CSV (sentiment, ID, date, query, user, tweet)
        getline(trainingData, sentiment, ',');
        getline(trainingData, id, ',');
        getline(trainingData, date, ',');
        getline(trainingData, query, ',');
        getline(trainingData, user, ',');
        getline(trainingData, tweet); // Last column: tweet text

        std::vector<DSString> tokens = tokenize(tweet); // Tokenize tweet into individual words

        for (int i = 0; i < tokens.size(); i++) {
            // Check if token already in classifiedWords map
            if (classifiedWords.count(tokens[i]) < 1) {
                if (sentiment == "4") { // Positive sentiment
                    classifiedWords.insert(std::pair(tokens[i], 1));
                } else if (sentiment == "0") { // Negative sentiment
                    classifiedWords.insert(std::pair(tokens[i], -1));
                }
                uniqueTokens.push_back(tokens[i]); // Add token to unique tokens list
                trainingTokens++;
            } else {
                // Adjust sentiment score if token already classified
                if (sentiment == "4") {
                    classifiedWords[tokens[i]]++;
                } else if (sentiment == "0") {
                    classifiedWords[tokens[i]]--;
                }
            }
        }
    }
    // Display summary of training data processed
    std::cout << "Total Number of Training tokens: " << trainingTokens 
              << " (" << classifiedWords.size() << " unique values)" << std::endl;
}

// Predict function: Classifies each tweet in the test data and outputs results
void Classifier::predict(std::istream& testData, std::ostream& result) {
    DSString line;
    getline(testData, line); // Read header line
    DSString sentiment, id, date, query, user;
    int sentimentValue = 0;

    while (!testData.eof()) { // Process each test tweet until end of file
        sentimentValue = 0; // Reset sentiment value
        DSString tweet;
        getline(testData, id, ',');
        getline(testData, date, ',');
        getline(testData, query, ',');
        getline(testData, user, ',');
        getline(testData, tweet);

        std::vector<DSString> tokens = tokenize(tweet); // Tokenize tweet

        for (int i = 0; i < tokens.size(); i++) {
            // Update sentimentValue based on token classification
            if (classifiedWords.count(tokens[i]) == 1) {
                if (classifiedWords[tokens[i]] > 0) {
                    sentimentValue++;
                } else if (classifiedWords[tokens[i]] < 0) {
                    sentimentValue--;
                }
            }
        }
        // Set sentiment to positive or negative based on sentimentValue
        if (sentimentValue >= 0) {
            sentiment = "4";
            sentiments.insert(std::pair(id, "4"));
        } else {
            sentiment = "0";
            sentiments.insert(std::pair(id, "0"));
        }
        result << sentiment << ", " << id << '\n'; // Write prediction to output
    }
    result << std::flush; // Ensure all output is written
    std::cout << "Total Predictions Made: " << sentiments.size() << std::endl;
}

// evaluatePredictions function: Compares predictions to actual results for accuracy
void Classifier::evaluatePredictions(std::istream& realData, std::ostream& accuracyResults) {
    DSString line;
    getline(realData, line); // Read header line
    DSString sentiment, id;
    double accuracy;
    double correct = 0; // Track correct predictions
    double count = 0;   // Track total predictions
    std::vector<DSString> ids;
    std::vector<DSString> actualSentiments;

    while (!realData.eof()) { // Process each actual result entry
        getline(realData, sentiment, ',');
        getline(realData, id);
        ids.push_back(id);
        actualSentiments.push_back(sentiment);

        // Check if prediction matches actual sentiment
        if (sentiments.count(id) == 1 && sentiments[id] == sentiment) {
            correct++;
        }
        count++;
    }
    accuracy = correct / count; // Calculate accuracy
    std::cout << "Number of correct predictions: " << correct << std::endl;
    std::cout << "Number of predictions made: " << count << std::endl;
    std::cout << "Total accuracy: " << accuracy << std::endl;

    accuracyResults << std::fixed << std::setprecision(3) << accuracy << std::endl; // Output accuracy

    // Output each prediction with actual result and ID for detailed comparison
    for (int i = 0; i < ids.size(); i++) {
        accuracyResults << sentiments[ids[i]] << "," << actualSentiments[i] << "," << ids[i] << '\n';
    }
    accuracyResults << std::flush;
}