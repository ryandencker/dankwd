#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <random>
#include <windows.h>
#include <cctype>
#include <cstdlib>
#include <ctime>

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
    cout << "Usage:     dankwd.exe <flag> <password>" << endl;
    cout << "Options:" << endl;
    cout << "\t -t \t compares password to large wordlists of common passwords" << endl;
    cout << "\t -p \t checks strength of password" << endl;
    cout << "\t -c \t checks how long it will take to crack password assuming 1 billion guesses per second" << endl;
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

void password(string usrpswd) //in progress
{
    bool nums = false;
    bool lLetters = false;
    bool uLetters = false;
    bool specials = false;
    int totalCharacters = 0;
    int combinations;

    string recommend = "We recommend passwords having lowercase letters, uppercase letters, numbers and special characters";
    string weak = "This is a weak password";
    string good = "this is a good password, but could be stronger";
    string strong = "This is a strong password";

    if(usrpswd.length() < 10)
    {
        cout << " We would recommend a longer password. Passwords shorter than 10 characters will take hours to days to crack.";
        exit(0);
    }

    if(hasNums(usrpswd))
    {
        nums = true;
    }

    if(haslLetters(usrpswd))
    {
        lLetters = true;
    }

    if(hasuLetters(usrpswd))
    {
        uLetters = true;
    }

    if(hasSpecials(usrpswd))
    {
        specials = true;
    }

    




/*
    if(nums == false && lLetters == true && uLetters == false && specials == false)
    {
        cout << "Your password only contains lowercase letters." << weak << recommend;
        exit(0);
    }

    if(nums == false && lLetters == false && uLetters == true && specials == false)
    {
        cout << "Your password only contains uppercase letters." << weak << recommend;
    }

    if(nums == false && lLetters == false && uLetters == false && specials == true)
    {
        cout << "Your password only contains special characters." << weak << recommend;
    }
*/
    

    


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
    int combinations;
    int totalCharacters = 0;
    string response;

    if(hasNums(usrpswd))
    {
        nums = true;
    }

    if(haslLetters(usrpswd))
    {
        lLetters = true;
    }

    if(hasuLetters(usrpswd))
    {
        uLetters = true;
    }

    if(hasSpecials(usrpswd))
    {
        specials = true;
    }

    if (nums) totalCharacters += 10;        // 10 numbers (0-9)
    if (lLetters) totalCharacters += 26;    // 26 lowercase letters (a-z)
    if (uLetters) totalCharacters += 26;    // 26 uppercase letters (A-Z)
    if (specials) totalCharacters += 32;    // 32 special characters 

    combinations = pow(totalCharacters, usrpswd.length());

    cout << "\nTotal Combinations: " << combinations << endl;

    

    while(true)
    {
        cout << endl << "How many attempts per second would you like to attempt to crack the password?\n\n";

        cout << "a: 1 million attempts per second\n";
        cout << "b: 10 million attempts per second\n";
        cout << "c: 100 million attempts per second\n";
        cout << "d: 1 billion attempts per second\n";
        cout << "e: enter custom attempts per second\n";
        cin >> response;

        if(response == "a")
        {

        }
        else if(response == "b")
        {

        }
        else if(response == "c")
        {

        }
        else if(response == "d")
        {

        }
        else if(response == "e")
        {

        }
        else
        {
            cout << "choose from the selected options"; //finish this
        }
    }

}

void all()
{
    //do test(), password(), and crack()
    cout << "-a" << endl;
}

void danktext()
{
    srand((unsigned) time(NULL));
    int random = (rand() % 9);
    
    switch(random)
    {
        case 0:
        {
            cout << R"(
    ,---,                                  ,-.                           
  .'  .' `\                            ,--/ /|                     ,---, 
,---.'     \                   ,---, ,--. :/ |          .---.    ,---.'| 
|   |  .`\  |              ,-+-. /  |:  : ' /          /. ./|    |   | : 
:   : |  '  |  ,--.--.    ,--.'|'   ||  '  /        .-'-. ' |    |   | | 
|   ' '  ;  : /       \  |   |  ,"' |'  |  :       /___/ \: |  ,--.__| | 
'   | ;  .  |.--.  .-. | |   | /  | ||  |   \   .-'.. '   ' . /   ,'   | 
|   | :  |  ' \__\/: . . |   | |  | |'  : |. \ /___/ \:     '.   '  /  | 
'   : | /  ;  ," .--.; | |   | |  |/ |  | ' \ \.   \  ' .\   '   ; |:  | 
|   | '` ,/  /  /  ,.  | |   | |--'  '  : |--'  \   \   ' \ ||   | '/  ' 
;   :  .'   ;  :   .'   \|   |/      ;  |,'      \   \  |--" |   :    :| 
|   ,.'     |  ,     .-./'---'       '--'         \   \ |     \   \  /   
'---'        `--`---'                              '---"       `----'    
                                                                        
            )";
            break;
        }
        
        case 1:
        {
            cout << R"(
 ______        ____    ,---.   .--..--.   .--.  .--.      .--. ______      
|    _ `''.  .'  __ `. |    \  |  ||  | _/  /   |  |_     |  ||    _ `''.  
| _ | ) _  \/   '  \  \|  ,  \ |  || (`' ) /    | _( )_   |  || _ | ) _  \ 
|( ''_'  ) ||___|  /  ||  |\_ \|  ||(_ ()_)     |(_ o _)  |  ||( ''_'  ) | 
| . (_) `. |   _.-`   ||  _( )_\  || (_,_)   __ | (_,_) \ |  || . (_) `. | 
|(_    ._) '.'   _    || (_ o _)  ||  |\ \  |  ||  |/    \|  ||(_    ._) ' 
|  (_.\.' / |  _( )_  ||  (_,_)\  ||  | \ `'   /|  '  /\  `  ||  (_.\.' /  
|       .'  \ (_ o _) /|  |    |  ||  |  \    / |    /  \    ||       .'   
'-----'`     '.(_,_).' '--'    '--'`--'   `'-'  `---'    `---`'-----'`    
            )";
            break;
        }

        case 2:
        {
            cout << R"(
      :::::::::      :::     ::::    ::: :::    ::: :::       ::: ::::::::: 
     :+:    :+:   :+: :+:   :+:+:   :+: :+:   :+:  :+:       :+: :+:    :+: 
    +:+    +:+  +:+   +:+  :+:+:+  +:+ +:+  +:+   +:+       +:+ +:+    +:+  
   +#+    +:+ +#++:++#++: +#+ +:+ +#+ +#++:++    +#+  +:+  +#+ +#+    +:+   
  +#+    +#+ +#+     +#+ +#+  +#+#+# +#+  +#+   +#+ +#+#+ +#+ +#+    +#+    
 #+#    #+# #+#     #+# #+#   #+#+# #+#   #+#   #+#+# #+#+#  #+#    #+#     
#########  ###     ### ###    #### ###    ###   ###   ###   #########       
            )";
            break;
        }

        case 3:
        {
            cout << R"(
__/\\\\\\\\\\\\_________________________________________________________________________/\\\__        
 _\/\\\////////\\\________________________________/\\\__________________________________\/\\\__       
  _\/\\\______\//\\\______________________________\/\\\__________________________________\/\\\__      
   _\/\\\_______\/\\\__/\\\\\\\\\_____/\\/\\\\\\___\/\\\\\\\\_____/\\____/\\___/\\________\/\\\__     
    _\/\\\_______\/\\\_\////////\\\___\/\\\////\\\__\/\\\////\\\__\/\\\__/\\\\_/\\\___/\\\\\\\\\__    
     _\/\\\_______\/\\\___/\\\\\\\\\\__\/\\\__\//\\\_\/\\\\\\\\/___\//\\\/\\\\\/\\\___/\\\////\\\__   
      _\/\\\_______/\\\___/\\\/////\\\__\/\\\___\/\\\_\/\\\///\\\____\//\\\\\/\\\\\___\/\\\__\/\\\__  
       _\/\\\\\\\\\\\\/___\//\\\\\\\\/\\_\/\\\___\/\\\_\/\\\_\///\\\___\//\\\\//\\\____\//\\\\\\\/\\_ 
        _\////////////______\////////\//__\///____\///__\///____\///_____\///__\///______\///////\//__
            )";
            break;
        }

        case 4:
        {
            cout << R"(
 /$$$$$$$                      /$$                           /$$
| $$__  $$                    | $$                          | $$
| $$  \ $$  /$$$$$$  /$$$$$$$ | $$   /$$ /$$  /$$  /$$  /$$$$$$$
| $$  | $$ |____  $$| $$__  $$| $$  /$$/| $$ | $$ | $$ /$$__  $$
| $$  | $$  /$$$$$$$| $$  \ $$| $$$$$$/ | $$ | $$ | $$| $$  | $$
| $$  | $$ /$$__  $$| $$  | $$| $$_  $$ | $$ | $$ | $$| $$  | $$
| $$$$$$$/|  $$$$$$$| $$  | $$| $$ \  $$|  $$$$$/$$$$/|  $$$$$$$
|_______/  \_______/|__/  |__/|__/  \__/ \_____/\___/  \_______/
            )";
            break;
        }
        
        case 5:
        {
            cout << R"(
    ____              __                __
   / __ \____ _____  / /___      ______/ /
  / / / / __ `/ __ \/ //_/ | /| / / __  / 
 / /_/ / /_/ / / / / ,<  | |/ |/ / /_/ /  
/_____/\__,_/_/ /_/_/|_| |__/|__/\__,_/  
            )";
            break;
        }

        case 6:
        {
            cout << R"(
 (                                        
 )\ )                   )           (     
(()/(      )         ( /(  (  (     )\ )  
 /(_))  ( /(   (     )\()) )\))(   (()/(  
(_))_   )(_))  )\ ) ((_)\ ((_)()\   ((_)) 
 |   \ ((_)_  _(_/( | |(_)_(()((_)  _| |  
 | |) |/ _` || ' \))| / / \ V  V // _` |  
 |___/ \__,_||_||_| |_\_\  \_/\_/ \__,_| 
            )";
            break;
        }

        case 7:
        {
            cout << R"(
  ;                                                                  ;           
  ED.                                                                ED.         
  E#Wi                     L.             G:                         E#Wi        
  E###G.                   EW:        ,ft E#,    :                   E###G.      
  E#fD#W;               .. E##;       t#E E#t  .GE          ;        E#fD#W;     
  E#t t##L             ;W, E###t      t#E E#t j#K;        .DL        E#t t##L    
  E#t  .E#K,          j##, E#fE#f     t#E E#GK#f  f.     :K#L     LWLE#t  .E#K,  
  E#t    j##f        G###, E#t D#G    t#E E##D.   EW:   ;W##L   .E#f E#t    j##f 
  E#t    :E#K:     :E####, E#t  f#E.  t#E E##Wi   E#t  t#KE#L  ,W#;  E#t    :E#K:
  E#t   t##L      ;W#DG##, E#t   t#K: t#E E#jL#D: E#t f#D.L#L t#K:   E#t   t##L  
  E#t .D#W;      j###DW##, E#t    ;#W,t#E E#t ,K#jE#jG#f  L#LL#G     E#t .D#W;   
  E#tiW#G.      G##i,,G##, E#t     :K#D#E E#t   jDE###;   L###j      E#tiW#G.    
  E#K##i      :K#K:   L##, E#t      .E##E j#t     E#K:    L#W;       E#K##i      
  E##D.      ;##D.    L##, ..         G#E  ,;     EG      LE.        E##D.       
  E#t        ,,,      .,,              fE         ;       ;@         E#t         
  L:                                    ,                            L:         
            )";
            break;
        }

        case 8:
        {
            cout << R"(
 ____ ____ ____ ____ ____ ____ 
||D |||a |||n |||k |||w |||d ||
||__|||__|||__|||__|||__|||__||
|/__\|/__\|/__\|/__\|/__\|/__\|
            )";
            break;
        }

        case 9:
        {
            cout << R"(
________              ______           _________
___  __ \_____ __________  /____      _______  /
__  / / /  __ `/_  __ \_  //_/_ | /| / /  __  / 
_  /_/ // /_/ /_  / / /  ,<  __ |/ |/ // /_/ /  
/_____/ \__,_/ /_/ /_//_/|_| ____/|__/ \__,_/   
            )";
            break;
        }
    }


}

int main(int argc, char *argv[])    //argc is the number of commandline arguments recieved, argv is the strings
{
    

    danktext();


    if(argc == 1 || argc == 2)   //if user only runs the executable or doesnt provide a password
    {
        help();
    }

    if(argc > 3)    //if there are too many arguements getting passed
    {
        help();
    }

    string flag = argv[1];

    string usrpswd = argv[2];
   
    cout << flag << endl;

    if (flag == "-t")
        test(usrpswd);
    else if (flag == "-p")
        password(usrpswd);  //in progress
    else if (flag == "-c")
        crack(usrpswd);     //in progress first
    else if (flag == "-a")
        all();
    else
        cout << "Unknown flag: for usage do:  dankwd.exe -h" << endl;

    return 0;
}