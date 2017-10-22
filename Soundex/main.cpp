//
//  main.cpp
//  Soundex
//
//  Created by Brad Killeen on 10/5/17.
//  Copyright © 2017 Brad Killeen. All rights reserved.
//

#include <iostream>
#include <string>
#include <set>

using namespace std;

class Soundex{
public:
    Soundex(string);
    void convertToSoundexIntermediate(string& unconverted);
    void convertToSoundexConverted(string& intermediate);
    string getSoundexIntermediate();
    string getSoundexConverted();
private:
    char storedLetter;
    string unconverted;
    string intermediate;
    string converted;
};

Soundex::Soundex(string userName){
    unconverted = userName;
    storedLetter = unconverted[0];
    convertToSoundexIntermediate(unconverted);
    intermediate = unconverted;
    convertToSoundexConverted(unconverted);
    converted = unconverted;
    unconverted[0] = storedLetter;
}

int main() {
    string userName;
    string intermediateSoundex;
    
    while(1==1){
        cout << "Please enter your name to convert to Soundex, Q to quit" << endl;
        cin >> userName;
        if(userName == "Q"){
            break;
        }
        cout << "You entered : " << userName << endl;
        Soundex soundex(userName);
        cout << "Your name in Soundex (intermediate) is: " << soundex.getSoundexIntermediate() << endl;
        cout << "Your name in Soundex (final) is: " << soundex.getSoundexConverted() << endl;
    }
    return 0;
}

void Soundex::convertToSoundexIntermediate(string& unconverted){
    
    //Strings for alphabet and replacement characters (cyphers) according to Soundex rules
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string alphabetCypher = "_123_12&_22455_12623_1&2_2";
    
    //Iterators for the user provided "name", the comparison string, and the cypher string
    string::iterator unconvertedIt;
    string::iterator alphabetIt = alphabet.begin();
    string::iterator cypherIt = alphabetCypher.begin(); //initialize at the beginning of cypher string
    
    //Convert first letter to lower case for later reduction method. Store original letter for replacement
    char firstLetterLower = tolower(storedLetter);
    unconverted[0] = firstLetterLower;
    
    //Begin iterating through the user name, starting at second letter
    for(unconvertedIt = unconverted.begin(); unconvertedIt != unconverted.end(); unconvertedIt++){
        
        //Iterate through alphabet string
        for(alphabetIt = alphabet.begin(); alphabetIt != alphabet.end(); alphabetIt++){
            
            //Compare username iterator and alphabet iterator, if matched, replace with cypher iterator value
            if(*alphabetIt == *unconvertedIt){
                *unconvertedIt = *cypherIt;
            }
            //Advance cypher position forward to match position of alphabet iterator
            advance(cypherIt,1);
            
            //Once we reach the end of the alphabet string, we reset the cypher iterator to the start of the cypher string (this is clunky)
            if(cypherIt == alphabetCypher.end()){
                cypherIt = alphabetCypher.begin();
            }
        }
    }
}

void Soundex::convertToSoundexConverted(string& intermediate){
    //Remove all underscore chars and
    for(int i = 1; i < intermediate.length(); i++){
        if(intermediate[i] == '_'){
            intermediate.erase(i,1);
            --i;
        }
    }

    //Remove double chars
    for(int i = 0; i < intermediate.length(); i++){
        if(intermediate[i] == intermediate[i + 1]){
            intermediate.erase(i + 1, 1);
        }
    }
    //Remove same chars separtated by & (representing 'h; and 'w')
    for(int i = 0; i < intermediate.length(); i++){
        if(intermediate[i + 1] == '&' && intermediate[i + 2] == intermediate[i]){
            intermediate.erase(i + 1, 2);
        }
    }
    //Remove & once previous condition is evaluated
    for(int i = 1; i < intermediate.length(); i++){
        if(intermediate[i] == '&'){
            intermediate.erase(i,1);
        }
    }
    //Erase string if longer than 4
    if(intermediate.length() > 4){
        intermediate.erase(4);
    }
    //Pad with trailing zeros if shorter than 4
    while(intermediate.length() < 4){
        string filler = "0";
        intermediate.append(filler);
    }
    //Replace first letter converted to intermediate with original letter
    unconverted[0] = storedLetter;
}

string Soundex::getSoundexIntermediate(){
    return intermediate;
}

string Soundex::getSoundexConverted(){
    return converted;
}
