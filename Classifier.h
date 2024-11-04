#include "DSString.h"
#include "Tokenizer.h"
#include <iostream>
#include <vector>
#include <map>
#include <codecvt>
#include <iostream>
#include <iomanip>
#include <locale>
#include <sstream>

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

class Classifier {

private:
    // two maps that are used to hold the tokens from training and the predicted sentiments
    std::map<DSString, int> classifiedWords;
    std::map<DSString, DSString> sentiments;
    

public:

    // three main functions to run the code
    void train(std::istream&);
    void predict(std::istream&, std::ostream&);
    void evaluatePredictions(std::istream&, std::ostream&);


};

#endif