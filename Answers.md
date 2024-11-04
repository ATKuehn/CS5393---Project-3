# Assignment 2: Answers

**Complete this document, commit your changes to Github and submit the repository URL to Canvas.** Keep your answers short and precise.

Your Name:

Used free extension: [ ] 24 hrs or [ ] 48 hrs

[ ] Early submission (48 hrs)

[ ] Bonus work. Describe: ...

Place [x] for what applies.


## UML Diagram

Add your UML class diagram here.

Replace the following image with your diagram. You can draw it by hand and take a photo.
![UML Class Diagram](UML_class.png)

## Answers

1. How do you train the model and how do you classify a new tweet? Give a short description of the main steps.

    > To train the model, I began by creating a dictionary with keys as tokens (DSStrings) and values as integers. I processed each tweet, tokenizing it into individual words. For each token, I checked if it already existed in the dictionary; if not, I added it with an initial value based on the tweet’s sentiment (positive or negative). If it was already present, I adjusted its value according to the tweet’s sentiment, either increasing or decreasing by one. To classify a new tweet, I tokenized it and looked up each token in the dictionary. If the token existed, I updated the tweet’s sentiment score based on the dictionary’s value for that token (adding for positive, subtracting for negative). After processing all tokens, if the score was zero or higher, I classified the tweet as positive; otherwise, it was negative.

2. How long did your code take for training and what is the time complexity of your training implementation (Big-Oh notation)? Remember that training includes reading the tweets, breaking it into words, counting, ... Explain why you get this complexity (e.g., what does `N` stand for and how do your data structures/algorithms affect the complexity).

   > The training complexity is O(N*log(N)), where N represents the total number of tokens in the training data. This complexity arises because we loop through all tokens and use a map to count occurrences, which has an O(log(N)) complexity due to search operations. Since the counting operation occurs within the loop, the complexities are multiplied.

3. How long did your code take for classification and what is the time complexity of your classification implementation (Big-Oh notation)? Explain why.

   > The classification complexity is also O(Nlog(N)), with N representing the total number of tokens in the test data. Similar to training, this complexity arises from looping through tokens and using map lookups, which are O(log(N)) operations. This lookup is nested within the loop, resulting in O(Nlog(N)).

4. What accuracy did your algorithm achieve on the provides training and test data? 

   > My accuracy: 67.6%.

   The TA will run your code on Linux and that accuracy value will be used to determine your grade.

5. What were the changes that you made that improved the accuracy the most?
   
   > The most impactful change for accuracy was ensuring tokens contained only alphabetic characters, preventing issues where punctuation affected token values. For example, "want" and "want." were counted separately, reducing accuracy. By filtering out punctuation, tokens were accurately counted, increasing reliability.

6. How do you know that you use proper memory management? I.e., how do you know that you do not have
   a memory leak?

   > I ensured proper memory management by deleting any objects created with the "new" keyword and verified that no memory leaks occurred using Valgrind, which reported no memory issues.

6. What was the most challenging part of the assignment?

   > Utilzing AI to assist in programing can be quite difficult when working with multiple files, as the AI offten makes more mistakes that require lots of debugging to get working. This is the first Time I experimented in working with AI on multiple files, and found the process difficult in sevral instances. I found including as much detail and information in one message often yeilds the greatest results with fewest mistakes, which is somthing to consider for the future.
