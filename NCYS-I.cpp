#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <fstream>
#include <windows.h>
#include <math.h>

using namespace std;

void displaynames()
{
	system("color 03");
    cout << endl << endl << endl << endl << endl << endl;
    cout << "                                            WELCOME" << endl << endl;
    Sleep(1000);
	cout << "                                               TO " << endl << endl; 
    Sleep(1000);
    cout << "                       PASSWORD STRENGTH TESTER & PASSWORD GENERATOR" << endl << endl;
    Sleep(1000);
    cout << "                                               BY" << endl << endl;
    Sleep(1000);
    cout << "                                  JAHANZEB KHAIRI (22K-4746)" << endl << endl;
    Sleep(1000);
    cout << "                                     YAHYA KHAN   (22K-4690)" << endl << endl;
    Sleep(1000);
    cout << "                                 JAHANZAIB SHAIKH (22K-4789)" << endl << endl << endl << endl << endl;
    Sleep(1000);
    cout << "                                  Press 'Enter' to continue..... ";
    cin.ignore();
    system("CLS");
}

enum PasswordStrength
{
    Strong,
    Weak,
    Average
};

class StrengthTest
{
public:
    bool isLowerCase(char ch)
    {
        return ch >= 'a' && ch <= 'z';
    }
    bool isUpperCase(char ch)
    {
        return ch >= 'A' && ch <= 'Z';
    }

    bool isDigit(char ch)
    {
        return ch >= '0' && ch <= '9';
    }

    bool isSpecialSymbol(char ch)
    {
        return ch == '!' || ch == '@' || ch == '#' || ch == '$' || ch == '%' || ch == '&' || ch == '*';
    }
    
    void estimateTimeToCrack(const string password, PasswordStrength strength)
    {
        const double attemptsPerSecond = 1000.0;
        double crackTime;
        double totalAttempts;
        switch (strength)
        {
        case Weak:
            totalAttempts = pow(10, password.length());
            break;
        case Average:
            totalAttempts = pow(62, password.length());
            break;
        case Strong:
            totalAttempts = pow(72, password.length());
            break;
        }
        crackTime = totalAttempts / attemptsPerSecond;
        for (int b = 0; b < 120; b++)
            cout << "-";
            Sleep(1000);
        cout << endl << endl << "Estimated time to crack the password: " << round(crackTime) << " seconds." << endl << endl;
    }

    string* File1()
    {
        int arraySize = 9259;
        ifstream file("TEXT.txt");
        if (!file.is_open())
        {
            cerr << "Error opening file: TEXT.txt" << endl;
            return NULL;
        }
        file.clear();
        file.seekg(0, ios::beg);
        string* wordsArray = new string[arraySize];
        for (int b = 0; b < arraySize; ++b)
        {
            getline(file, wordsArray[b]);
        }
        file.close();
        return wordsArray;
    }

    string* File2()
    {
        int arraySize = 9259;
        ifstream file("words.txt");
        if (!file.is_open())
        {
            cerr << "Error opening file: words.txt" << endl;
            return NULL;
        }
        file.clear();
        file.seekg(0, ios::beg);
        string* wordsArray = new string[arraySize];
        for (int b = 0; b < arraySize; ++b)
        {
            getline(file, wordsArray[b]);
        }
        file.close();
        return wordsArray;
    }

    int isWord(const string password)
    {
        int wordcount = 0;
        string* Uword = File1();
        string* Lword = File2();
        for (int b = 0; b < 9259; b++)
        {
            for (int m = 0; m <= static_cast<int>(password.size()) - static_cast<int>(Uword[b].size()); m++)
            {
                int w = 0;
                for (int n = 0; n < Uword[b].size(); n++)
                {
                    if (password[m + n] == Uword[b][n])
                        w++;
                }
                if (w == Uword[b].size())
                {
                    wordcount++;
                    break;
                }
            }

            for (int m = 0; m <= static_cast<int>(password.size()) - static_cast<int>(Lword[b].size()); m++)
            {
                int w = 0;
                for (int n = 0; n < Lword[b].size(); n++)
                {
                    if (password[m + n] == Lword[b][n])
                        w++;
                }
                if (w == Lword[b].size())
                {
                    wordcount++;
                    break;
                }
            }

            for (int m = 0; m <= static_cast<int>(password.size()) - static_cast<int>(Uword[b].size()); m++)
            {
                int w = 0;
                for (int n = 0; n < Lword[b].size(); n++)
                {
                    if ((password[m + n] == Lword[b][n]) || (password[m + n] == Uword[b][n]))
                        w++;
                }
                if ((w == Lword[b].size() )|| (w == Uword[b].size()))
                {
                    wordcount++;
                    break;
                }
            }
        }
        delete[] Uword;
        delete[] Lword;
        return wordcount;
    }

    PasswordStrength isStrongPassword(const string password)
    {
        bool repeatedCharacters = false;
        int LowercaseCount = 0;
        int UppercaseCount = 0;
        int DigitCount = 0;
        int SpecialSymbolCount = 0;
        int Wordcount = 0;
        Wordcount = isWord(password);
        for (int box = 0; box < password.length(); box++)
        {
            char ch = password[box];
            if (isLowerCase(ch))
            {
                LowercaseCount++;
            }
            else if (isUpperCase(ch))
            {
                UppercaseCount++;
            }
            else if (isDigit(ch))
            {
                DigitCount++;
            }
            else if (isSpecialSymbol(ch))
            {
                SpecialSymbolCount++;
            }
            int repeated = 0;
            for (int j = 0; j < password.length(); j++)
                if (j != box)
                    if (password[box] == password[j])
                    {
                        repeated++;
                        if (repeated >= 2)
                        {
                            repeatedCharacters = true;
                            repeated = 0;
                            break;
                        }
                    }
        }
        if ((Wordcount >= 10 || repeatedCharacters) && ((LowercaseCount > 6 || UppercaseCount > 6) && (DigitCount > 6 || SpecialSymbolCount > 6)))
            return Weak;
        else if ((Wordcount >= 10 || repeatedCharacters) && LowercaseCount > 0 && UppercaseCount == 0 && DigitCount == 0 && SpecialSymbolCount == 0)
            return Weak;
        else if ((Wordcount >= 10 || repeatedCharacters) && LowercaseCount == 0 && UppercaseCount > 0 && DigitCount == 0 && SpecialSymbolCount == 0)
            return Weak;
        else if ((Wordcount >= 10 || repeatedCharacters) && LowercaseCount == 0 && UppercaseCount == 0 && DigitCount > 0 && SpecialSymbolCount == 0)
            return Weak;
        else if ((Wordcount >= 10 || repeatedCharacters) && LowercaseCount == 0 && UppercaseCount == 0 && DigitCount == 0 && SpecialSymbolCount > 0)
            return Weak;
        else if ((Wordcount >= 10 || repeatedCharacters) && LowercaseCount > 0 && UppercaseCount > 0 && DigitCount == 0 && SpecialSymbolCount == 0)
            return Weak;
        else if ((Wordcount >= 10 || repeatedCharacters) && LowercaseCount > 0 && UppercaseCount == 0 && DigitCount > 0 && SpecialSymbolCount == 0)
            return Weak;
        else if ((Wordcount >= 10 || repeatedCharacters) && LowercaseCount > 0 && UppercaseCount == 0 && DigitCount == 0 && SpecialSymbolCount > 0)
            return Weak;
        else if ((Wordcount >= 10 || repeatedCharacters) && LowercaseCount == 0 && UppercaseCount > 0 && DigitCount > 0 && SpecialSymbolCount == 0)
            return Weak;
        else if ((Wordcount >= 10 || repeatedCharacters) && LowercaseCount == 0 && UppercaseCount > 0 && DigitCount == 0 && SpecialSymbolCount > 0)
            return Weak;
        else if ((Wordcount >= 10 || repeatedCharacters) && LowercaseCount == 0 && UppercaseCount == 0 && DigitCount > 0 && SpecialSymbolCount > 0)
            return Weak;
        else if ((!repeatedCharacters || (Wordcount >= 4 && Wordcount < 10)) && ((LowercaseCount >= 3 && LowercaseCount <= 6) && (UppercaseCount >= 3 && UppercaseCount <= 6) && (SpecialSymbolCount >= 3 && SpecialSymbolCount <= 6) && (DigitCount >= 3 && DigitCount <= 6)))
            return Average;
        else if ((!repeatedCharacters || (Wordcount >= 4 && Wordcount < 10)) && (((LowercaseCount >= 3 && LowercaseCount <= 6) || (UppercaseCount >= 3 && UppercaseCount <= 6)) && ((SpecialSymbolCount >= 3 && SpecialSymbolCount <= 6) || (DigitCount >= 3 && DigitCount <= 6))))
            return Average;
        else if ((!repeatedCharacters || (Wordcount >= 4 && Wordcount < 10)) && (((LowercaseCount >= 3 && LowercaseCount <= 6) || (DigitCount >= 3 && DigitCount <= 6)) && ((SpecialSymbolCount >= 3 && SpecialSymbolCount <= 6) || (UppercaseCount >= 3 && UppercaseCount <= 6))))
            return Average;
        else if ((!repeatedCharacters || (Wordcount >= 4 && Wordcount < 10)) && (((LowercaseCount >= 3 && LowercaseCount <= 6) || (SpecialSymbolCount >= 3 && SpecialSymbolCount <= 6)) && ((UppercaseCount >= 3 && UppercaseCount <= 6) || (DigitCount >= 3 && DigitCount <= 6))))
            return Average;
        else
            return Strong;
    }
    
   
    void ProblemFinder()
    {
        retry:
        string password;
        cout << "Enter Password: ";
        cin >> password;
        system("CLS");
        Sleep(300);
       
        bool repeatedCharacters = false;
        int LowercaseCount = 0;
        int UppercaseCount = 0;
        int DigitCount = 0;
        int SpecialSymbolCount = 0;
        int Wordcount = 0;
        if (password.length() < 8)
        {
            Sleep(1000);
            cout << endl << "Password length limited! password must contain atleast 8 characters.";
            cout << " Enter a new password." << endl;
            Sleep(1000);
            system("CLS");
            goto retry;
        }
        Wordcount = isWord(password);
        for (int box = 0; box < password.length(); box++)
        {
            char ch = password[box];
            if (isLowerCase(ch))
            {
                LowercaseCount++;
            }
            else if (isUpperCase(ch))
            {
                UppercaseCount++;
            }
            else if (isDigit(ch))
            {
                DigitCount++;
            }
            else if (isSpecialSymbol(ch))
            {
                SpecialSymbolCount++;
            }
            int repeated = 0;
            for (int j = 0; j < password.length(); j++)
                if (j != box)
                    if (password[box] == password[j])
                    {
                        repeated++;
                        if (repeated >= 2)
                        {
                            repeatedCharacters = true;
                            repeated = 0;
                            break;
                        }
                    }
        }
        for (int b = 0; b < 120; b++)
            cout << "-";
        int num = 0;
        PasswordStrength strength = isStrongPassword(password);
        if (strength == Weak)
        {
            cout << endl << endl << "PASSWORD STRENGTH : Weak password" << endl << endl;
            Sleep(1000);
            estimateTimeToCrack(password, strength) ;
            for (int b = 0; b < 120; b++)
                cout << "-";
        }
        else if (strength == Average)
        {
            cout << endl << endl << "PASSWORD STRENGTH : Average Password" << endl << endl;
            Sleep(1000);
            estimateTimeToCrack(password, strength) ;
            for (int b = 0; b < 120; b++)
                cout << "-";
        }
        else if (strength == Strong)
        {
            cout << endl << endl << "PASSWORD STRENGTH : Strong Password" << endl << endl;
            Sleep(1000);
            estimateTimeToCrack(password, strength) ;
            for (int b = 0; b < 120; b++)
                cout << "-";
                goto P;
        }
        if (LowercaseCount > 0 && UppercaseCount == 0 && DigitCount == 0 && SpecialSymbolCount == 0)
        {
            num++;
            Sleep(1000);
            cout << endl << endl << num << ") password contains only lowercase characters." << endl << endl;
            for (int b = 0; b < 120; b++)
                cout << "-";
        }
        if (LowercaseCount == 0 && UppercaseCount > 0 && DigitCount == 0 && SpecialSymbolCount == 0)
        {
            num++;
            Sleep(1000);
            cout << endl << endl << num << ") password contains only uppercase characters." << endl << endl;
            for (int b = 0; b < 120; b++)
                cout << "-";
        }
        if (LowercaseCount == 0 && UppercaseCount == 0 && DigitCount > 0 && SpecialSymbolCount == 0)
        {
            num++;
            Sleep(1000);
            cout << endl << endl << num << ") password contains only digits." << endl << endl;
            for (int b = 0; b < 120; b++)
                cout << "-";
        }
        if (LowercaseCount == 0 && UppercaseCount == 0 && DigitCount == 0 && SpecialSymbolCount > 0)
        {
            num++;
            Sleep(1000);
            cout << endl << endl << num << ") password contains only special symbols." << endl << endl;
            for (int b = 0; b < 120; b++)
                cout << "-";
        }
        if (LowercaseCount > 0 && UppercaseCount > 0 && DigitCount == 0 && SpecialSymbolCount == 0)
        {
            num++;
            Sleep(1000);
            cout << endl << endl << num << ") password contains only characters." << endl << endl;
            for (int b = 0; b < 120; b++)
                cout << "-";
        }
        if (Wordcount > 5)
        {
            num++;
            Sleep(1000);
            cout << endl << endl << num << ") Password contains too many understandable english words." << endl << endl;
            for (int b = 0; b < 120; b++)
                cout << "-";
        }
        if (repeatedCharacters == true)
        {
            num++;
            Sleep(1000);
            cout << endl << endl << num << ") Password contains characters that are repeating." << endl << endl;
            for (int b = 0; b < 120; b++)
                cout << "-";
        }
        if (LowercaseCount > 0 && UppercaseCount == 0 && DigitCount > 0 && SpecialSymbolCount == 0)
        {
            num++;
            Sleep(1000);
            cout << endl << endl << num << ") Password contains only lowercase characters and digits." << endl << endl;
            for (int b = 0; b < 120; b++)
                cout << "-";
        }
        if (LowercaseCount > 0 && UppercaseCount == 0 && DigitCount == 0 && SpecialSymbolCount > 0)
        {
            num++;
            Sleep(1000);
            cout << endl << endl << num << ") Password contains only lowercase characters and special symbols." << endl << endl;
            for (int b = 0; b < 120; b++)
                cout << "-";
        }
        if (LowercaseCount == 0 && UppercaseCount > 0 && DigitCount > 0 && SpecialSymbolCount == 0)
        {
            num++;
            Sleep(1000);
            cout << endl << endl << num << ") Password contains only uppercase characters and digits." << endl << endl;
            for (int b = 0; b < 120; b++)
                cout << "-";
        }
        if (LowercaseCount == 0 && UppercaseCount > 0 && DigitCount == 0 && SpecialSymbolCount > 0)
        {
            num++;
            Sleep(1000);
            cout << endl << endl << num << ") Password contains only uppercase characters and special symbols." << endl << endl;
            for (int b = 0; b < 120; b++)
                cout << "-";
        }
        if (LowercaseCount == 0 && UppercaseCount == 0 && DigitCount > 0 && SpecialSymbolCount > 0)
        {
            num++;
            Sleep(1000);
            cout << endl << endl << num << ") Password contains only digits and special symbols." << endl << endl;
            for (int b = 0; b < 120; b++)
                cout << "-";
        }
        Sleep(1000);
        cout << endl << endl << "Due to the following reasons, the password can be decrypted or can be guessed." << endl << endl;
        for (int b = 0; b < 120; b++)
            cout << "-";
            P:
        Sleep(1000);
        
     
    }
    
    
};
class generate
{
    int length;
public:
    generate()
    {
        length = 0;
    }
    void numeral(string& password, int cursor)
    {
        char box[10] = { '0','1','2','3','4','5','6','7','8','9' };
        int low = 0, high = 9;
        int x = (rand() % (high - low + 1)) + low;
        password += box[x];
    }
    void lowercase(string& password, int cursor)
    {
        char box[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
        int low = 0, high = 25;
        int x = (rand() % (high - low + 1)) + low;
        password += box[x];
    }
    void uppercase(string& password, int cursor)
    {
        char box[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
        int low = 0, high = 25;
        int x = (rand() % (high - low + 1)) + low;
        password += box[x];
    }
    void specialchar(string& password, int cursor)
    {
        char box[7] = { '!','@','#','$','%','&','*' };
        int low = 0, high = 6;
        int x = (rand() % (high - low + 1)) + low;
        password += box[x];
    }
    string generatepassword()
    {
        again:
        srand((unsigned)time(NULL));
        Sleep(1000);
        cout << endl << endl << "Enter desired length of password (minimum length must be 8) : ";
        cin >> length;
        cout << endl;
        if (length < 8)
        {
            Sleep(1000);
            cout << endl << endl << "Password length limited! password must contain atleast 8 characters.";
            cout << " Enter a new size." << endl;
            Sleep(1500);
            system("CLS");
            goto again;
        }
        string password;
        Sleep(1000);
        int cursor = 0;
        int cont1 = 0, cont2 = 0, cont3 = 0, cont4 = 0, R = 1;
            while (cursor < length )
            {
                int low = 1, high = 4;
                int x = (rand() % (high - low + 1)) + low;
                switch (x)
                {
                case 1:
                    if (cont1 == 2)
                        break;
                    numeral(password, cursor);
                    cont1++;
                    R++;
                    cursor++;
                    break;
                case 2:
                    if (cont2 == 2)
                        break;
                    lowercase(password, cursor);
                    cont2++;
                    R++;
                    cursor++;
                    break;
                case 3:
                    if (cont3 == 2)
                        break;
                    uppercase(password, cursor);
                    cont3++;
                    R++;
                    cursor++;
                    break;
                case 4:
                    if (cont4 == 2)
                        break;
                    specialchar(password, cursor);
                    cont4++;
                    R++;
                    cursor++;
                    break;
                }
                if (R == 8)
                {
                    cont1 = cont2 = cont3 = cont4 = 0;
                    R = 1;
                }
            }
            password += '\0';
        return password;
    }
};

void choosingoption()
{
	 K:
    char option;
    cout << endl << endl << endl << endl << endl << endl;
    cout << "                                            OPTIONS " << endl << endl << endl;
    Sleep(1000);
    cout << "                    1) Enter 'A' for Testing a password for it's strength. " << endl << endl;
    Sleep(1000);
    cout << "                    2) Enter 'B' for Generating a random password." << endl << endl;
    Sleep(1000);
    cout << "                    3) Enter 'X' to end the program." << endl << endl << endl << endl << endl;
    Sleep(1000);
    cout << "                                  Enter any option to continue  :  ";
    cin >> option;
    Sleep(1000);
    system("CLS");
    if ((option == 'a') || (option == 'A'))
    {
        StrengthTest y;
        Sleep(1000);
        y.ProblemFinder();
        N:
        cout << endl << endl << "Would you like to select another option ('Y' for yes / 'N for no')  :  ";
        cin >> option;
        system("CLS");
        if ((option == 'y') || (option == 'Y'))
            goto K;
        else if ((option == 'n') || (option == 'N'))
            goto ending;
        else
        {
            system("CLS");
            Sleep(1000);
            cout << "INVALID INPUT!" << endl;
            Sleep(1000);
            system("CLS");
            goto N;
        }
    }
    else if ((option == 'b') || (option == 'B'))
    {
        system("CLS");
        generate x;
        for (int b = 0; b < 120; b++)
            cout << "-";
        cout << endl << endl << "Generated password:  " << x.generatepassword() << endl << endl;
        for (int b = 0; b < 120; b++)
            cout << "-";
        Sleep(1000);
    M:
        cout << endl << endl << "Would you like to select another option ('Y' for yes / 'N for no')  :  ";
        cin >> option;
        system("CLS");
        if ((option == 'y') || (option == 'Y'))
            goto K;
        else if ((option == 'n') || (option == 'N'))
            goto ending;
        else
        {
            system("CLS");
            Sleep(1000);
            cout << "INVALID INPUT!" << endl;
            Sleep(1000);
            system("CLS");
            goto M;
        }
    }
    else if ((option == 'x') || (option == 'X'))
        goto ending;
    else
    {
        system("CLS");
        Sleep(1000);
        cout << "INVALID INPUT!" << endl;
        Sleep(1000);
        system("CLS");
        goto K;
    }
ending:
    system("CLS");
    Sleep(1000);
    cout << "Thank you for choosing us" << endl;
}

int main()
{
   displaynames();
   choosingoption();
}
