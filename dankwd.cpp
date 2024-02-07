#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <random>
#include <windows.h>
#include <cctype>

using namespace std;

char specialchars[] = "!@#$%^&*()-_=+[{]}\\|;:'\",<.>/?";

unordered_set<string> loadPasswords(const string& filename) {
    unordered_set<string> passwords;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening " << filename << endl;
        //exit function prematurely
        return passwords;
    }
    string line;
    while (getline(file, line)) {
        passwords.insert(line);
    }
    

    return passwords;
}

void help()
{
    cout << "\n \nVersion 1.0" << endl;
    cout << "Usage:     dankwd <flag> <password>" << endl;
    cout << "Options:" << endl;
    cout << "\t -t \t compares password to large wordlists of common passwords" << endl;
    cout << "\t -p \t checks strength of password" << endl;
    cout << "\t -d \t checks how long it will take to crack password assuming 1 million guesses per second" << endl;
    cout << "\t -a \t does all the flags" << endl;
    exit(0);
}

bool isInWordlists(const vector<unordered_set<string>>& wordlists, const string& password) {
    for (const auto& wordlist : wordlists) {
        if (wordlist.find(password) != wordlist.end()) {
            return true;
        }
    }
    return false;
}

void test(string usrpswd)
{
    cout << "Please wait while searching through wordlists..." << endl;
    string wordlistsFolderPath = "Wordlists";
    vector<unordered_set<string>> allWordlists;

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((wordlistsFolderPath + "\\*").c_str(), &findFileData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                continue; // Skip directories
            }

            const string filePath = wordlistsFolderPath + "\\" + findFileData.cFileName;
            cout << "Loading passwords from: " << filePath << endl;
            allWordlists.push_back(loadPasswords(filePath));

        } while (FindNextFile(hFind, &findFileData) != 0);

        FindClose(hFind);
    } else {
        cerr << "No wordlists found in the 'Wordlists' folder. Exiting..." << endl;
        return; // Exit the program with an error code
    }

    bool passwordFound = isInWordlists(allWordlists, usrpswd);

    if(passwordFound)
    {
        cout << "Your password was found in one of the wordlists" << endl;
    }
    else
    {
        cout << "Your password was not found in any of the wordlists" << endl;
    }

    //bool safe = true;

    /*if(isInWordlists(rockYou, xato, human, usrpswd))
    {
        cout << "Your password was found in one of the wordlists and is not secure" << endl;
        return;
    }
    else
    {
        cout << "Your password was not found in our wordlists" << endl;
        return;
    }*/
    return;
}

void password(string usrpswd)
{
    //check password for uppercase, lowercase, special characters
    cout << "-p" << endl;
}

bool hasNums(string usrpswd)
{
    for (char c : usrpswd) {
        if (isdigit(c)) {
            return true; // If a digit is found, return true immediately
        }
    }
    return false;
}

bool haslLetters(string usrpswd)
{
    for (char c : usrpswd) {
        if (islower(c)) {
            return true; // If a lowercase letter is found, set hasLower to true
        }
    }
    return false;
}

bool hasuLetters(string usrpswd)
{
    for (char c : usrpswd) {
        if (isupper(c)) {
            return true; // If a uppercase letter is found, set hasLower to true
        }
    }
    return false;
}

bool hasSpecials(string usrpswd)
{
    for (char c : usrpswd) {
        for (int i = 0; i < strlen(specialchars); ++i) {
            if (c == specialchars[i]) {
                return true; // If the character matches any special character, return true
            }
        }
    }
    return false;
}

void crack(string usrpswd)
{
    //calculate how long it will take to crack assuming it is a strong password
    //combinations - numbers 10 each char   -   lower letters 26 each char   -   upper letters 26 each char   -   special 32 each char
    //for total combination, we will 
    bool nums = false;
    bool lLetters = false;
    bool uLetters = false;
    bool specials = false; 

    if(hasNums(usrpswd))
    {
        nums = true;
        cout << "password has nums";
    }

    if(haslLetters(usrpswd))
    {
        lLetters = true;
        cout << "password has lower letters";
    }

    if(hasuLetters(usrpswd))
    {
        uLetters = true;
        cout << "password has upper letters";
    }

    if(hasSpecials(usrpswd))
    {
        specials = true;
        cout << "password has special characters";
    }
}

void all()
{
    //do test(), password(), and crack()
    cout << "-a" << endl;
}

int main(int argc, char *argv[])    //argc is the number of commandline arguments recieved, argv is the strings
{
    

    //random dankwd text


    if(argc == 1)   //if user only runs the executable
    {
        help();
        return 0;
    }

    if(argc > 3)    //if there are too many arguements getting passed
    {
        help();
        return 0;
    }

    string flag = argv[1];
    if(flag == "-h") //not working, everything else after working
        help();


    string usrpswd = argv[2];
   
    cout << flag << endl;

    if (flag == "-t")
        test(usrpswd);
    else if (flag == "-p")
        password(usrpswd);
    else if (flag == "-d")
        crack(usrpswd);
    else if (flag == "-a")
        all();
    else
        cout << "Unknown flag: for usage do -h" << endl;

    return 0;
}