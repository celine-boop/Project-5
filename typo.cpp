#include <iostream>
#include <string>
#include <cassert>
using namespace std;

string vocab;
int i = 0;
int j = 0;
int k = 0;
int counter = 0;
string newword;

int addOneChar(string vocab, string word);
int removeOneChar(string vocab, string word);
int oneReplacement(string vocab, string word);
int swapLetters(string vocab, string word);

int scoreTypo(const string dictionary[], int n, string word)
{
    if (n <= 0) {           //if n is less than 0, then return -1
        return -1;
    }

    for (i = 0; i < n; i++) {   //loops through all items in the dictionary up till n
        if (dictionary[i] == word) {    //if the words are the same, return 0
            return 0;
        }

        if (addOneChar(dictionary[i], word) == 1)   //if the function addOneChar returns 1, then return 1
        {
            return 1;
        }

        if (removeOneChar(dictionary[i], word) == 1)    ////if the function removeOneChar returns 1, then return 1
        {
            return 1;
        }

        if (oneReplacement(dictionary[i], word) == 1)   //if the function oneReplacement returns 1, then return 1
        {
            return 1;
        }

        if (swapLetters(dictionary[i], word) == 1)  //if the function swapLetters returns 1, then return 1
        {
            return 1;
        }


    }
    return 2;       //if none of the conditions are met, return 2
}


//vocab(k)  f o r t y
//word(j)   f o u r t y  
int addOneChar(string vocab, string word) {
    j = 0; //initialize j, k, counter, and newword.
    k = 0;
    counter = 0;
    newword = "";
    if (vocab.size() == word.size() - 1) {      //if vocab is one char less than word
        while (j < word.size() && k < vocab.size()) { 
            if (vocab.at(k) == word.at(j)) {    //if the characters at vocab and word are the same
                newword += word.at(j);          //append the char to newword
                j++;                            //move on to next char
                k++;
            }
            else {                             //if char is different
                j++;                           //move on to next char only in word
                counter++;                     //increment counter
            }
        }

        if (counter <= 1 && newword == vocab)  //if counter is 0/1 and newword is the same as vocab
            return 1;
    }
}

//vocab k - f e b r u a r y 
//word j -  f e b r u a r 
int removeOneChar(string vocab, string word) {
    j = 0;
    k = 0;
    counter = 0;
    newword = "";
    if (vocab.size() == word.size() + 1) {              //if vocab has one less char than word
        while (j < word.size() && k < vocab.size()) {
            if (vocab.at(k) == word.at(j)) {            
                newword += word.at(j);
                j++;
                k++;
            }
            else {                                      //if the characters are different
                newword += vocab.at(k);                 //append the char in vocab to newword
                k++;                                    //move along to next char in vocab
                counter++;
            }
        }
        if (counter == 0 && newword + vocab.at(vocab.size() - 1) == vocab) { return 1; } //if counter is 0, and newword + last char of vocab is vocab
        if (counter == 1 && newword == vocab) //if counter is 1 and newword is vocab, return one
            return 1;
    }
}

int oneReplacement(string vocab, string word) {
    //c o n s e r v a t i o n
    //c o n v e r s a t i o n  
    //doesn't return 1 for this case
    j = 0;
    k = 0;
    counter = 0;
    if (vocab.size() == word.size()) { //if the size of word and vocab are the same
        while (j < word.size() && k < vocab.size()) {
            if (vocab.at(k) == word.at(j)) { 
                j++;
                k++;
            }
            else {                          //if the characters are different
                if (counter > 0) { break; } //if counter is more than one break out of the loop
                word.at(j) = vocab.at(k);   //change the char in word to the char in vocab
                j++;
                k++;
                counter++;
            }
        }
        if (counter == 1 && word == vocab) //if counter is 1, and word is vocab
            return 1;
    }
}

int swapLetters(string vocab, string word) {
    j = 0;
    k = 0;
    counter = 0;
    if (vocab.size() == word.size()) { 
        while (j < word.size() && k < vocab.size()) {
            if (vocab.at(k) == word.at(j)) { 
                j++;
                k++;
            }
            else {
                if (counter > 0) { break; }         //if counter is more than 0 than exit the loop
                int temp = word.at(j);              //set temp value for first char
                word.at(j) = word.at(j + 1);        //set first char to the second char
                word.at(j + 1) = temp;              //set second char to temp value which contains the first char
                j + 2;                              //jump to two characters after
                k + 2;
                counter++;
            }
        }
        if (counter == 1 && vocab == word) //if counter is one and vocab is word
            return 1;
    }
}


int main()
{
    // Here are some tests.  You may add more if you wish.
    string dict1[6] = { "february", "pointer", "country", "forty", "conversation", "minuscule" };
    assert(scoreTypo(dict1, 0, "forty") == -1);
    assert(scoreTypo(dict1, 6, "forty") == 0);
    cout << scoreTypo(dict1, 6, "Forty") << endl;
    assert(scoreTypo(dict1, 6, "fourty") == 1);
    assert(scoreTypo(dict1, 6, "fortyy") == 1);
    assert(scoreTypo(dict1, 6, "februar") == 1);
    assert(scoreTypo(dict1, 6, "febuary") == 1);
    assert(scoreTypo(dict1, 6, "miniscule") == 1);
    assert(scoreTypo(dict1, 3, "pointre") == 1);
    assert(scoreTypo(dict1, 6, "pointre") == 1);
    assert(scoreTypo(dict1, 6, "conservation") == 2); 
    cout << "All tests succeeded" << endl;
}