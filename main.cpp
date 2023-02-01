#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

int main() {
    std::ifstream text;
    std::ofstream data;
    std::string fileName;
    char repeat = 'Y';

    //structure for the text file with all of its attributes
    struct textfile {
        std::string title;
        std::string AuthorName;
        std::string AuthorFName;
        std::string AuthorLName;
        int wordCount = 0;
        int lineCount = 0;
        double frequency[26] = {0.0};
    };

    //open the output file
    data.open("CardCatalog.txt", std::ios::app);

    //repeat until the user says No
    while (repeat == 'Y') {
        double letterCount = 0;
        std::string contents;
        std::string word;
        std::string line;
        char response = 'a';
        char letter = 'a';
        int letterint = 0;
        int position = 0;

        //structure for the text file with all of its attributes
        struct textFile {
            std::string title;
            std::string AuthorName;
            std::string AuthorFName;
            std::string AuthorLName;
            int wordCount = 0;
            int lineCount = 0;
            double frequency[26] = {0.0};
        };

        //current file object using the textFile structure
        textFile currentFile;

        //prompt the user to give a file name
        std::cout << "What file do you want to read?: ";
        std::cin >> fileName;

        //open the text file
        text.open(fileName);

        //if the file fails to open ask again until they give a proper file
        while (text.fail()) {
            std::cout << "That file doesn't exist. Please give a different file: ";
            std::cin >> fileName;
            text.open(fileName);
        }

        std::cout << std::endl;

        //print out the title
        data << "Title: ";
        //while the title variable is empty keep getting lines until it is assigned a value
        while (currentFile.title.empty()) {
            std::getline(text, currentFile.title);
        }
        data << currentFile.title;
        data << std::endl;

        //print out the full authors name
        data << "Full Author: ";
        //while the author variable is empty keep getting lines until it is assigned a value
        while (currentFile.AuthorName.empty()) {
            std::getline(text, currentFile.AuthorName);
        }
        data << currentFile.AuthorName;
        data << std::endl;

        //print out the authors first name
        data << "Author First Name: ";
        //asign the authors name to the first name variable
        currentFile.AuthorFName = currentFile.AuthorName;
        //find the position of the space in the name
        position = currentFile.AuthorFName.find(" ");
        //erase everything after the space (including the space itself)
        currentFile.AuthorFName.erase(position, currentFile.AuthorFName.length());
        data << currentFile.AuthorFName;
        data << std::endl;

        //print out the authors last name
        data << "Author Last Name: ";
        //assign the authors name to the last name variable
        currentFile.AuthorLName = currentFile.AuthorName;
        //erase everything up to the space (including the space itself)
        currentFile.AuthorLName.erase(0, position + 1);
        data << currentFile.AuthorLName;
        data << std::endl;

        //print out the word count
        data << "Word Count: ";
        //while there is still text in the file run this loop
        while (!text.eof()) {
            //keep getting lines until the contents variable matches the keyword
            while (contents != "Contents:") {
                std::getline(text, contents);
                contents = contents.substr(0,9);
            }
            
            //take in each word and increment the word counter
            text >> word;
            currentFile.wordCount++;
        }
        data << currentFile.wordCount;
        data << std::endl;

        //print out the line count
        data << "Line Count: ";
        //clear the stream object and start at the top of the file
        text.clear();
        text.seekg(0);
        contents = "";
        //while there is still text in the file run this loop
        while (!text.eof()) {
            //keep getting lines until the contents variable matches the keyword
            while (contents != "Contents:") {
                std::getline(text, contents);
                contents = contents.substr(0,9);
            }
            //take in each line and increment the line counter
            std::getline(text, line);
            currentFile.lineCount++;
        }
        data << currentFile.lineCount;
        data << std::endl;

        //clear the stream object and start at the top of the file
        text.clear();
        text.seekg(0);
        contents = "";
        //while there is still text in the file run this loop
        while (!text.eof()) {
            //keep getting lines until the contents variable matches the keyword
            while (contents != "Contents:") {
                std::getline(text, contents);
                contents = contents.substr(0,9);
            }
            
            //set the letter variable to the current character
            text.get(letter);
            //lowercase the letter and cast it to an int
            letter = tolower(letter);
            letterint = (int)letter;
            //if it is a letter inbetween 'a' and 'z' increment the letter counter and the letters array slot
            if (letterint >= 'a' && letterint <= 'z') {
                letterCount++;
                currentFile.frequency[letterint - 'a']++;
            }
        }

        //ask the user if they want to see the letter frequency
        std::cout << "Do you want to see the letter frequency? (Y/N): ";
        std::cin >> response;
        std::cout << std::endl;
        if (response == 'Y') {
            char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
            
            //got this line of code from https://stackoverflow.com/questions/2528995/remove-r-from-a-string-in-c
            currentFile.title.erase( std::remove(currentFile.title.begin(), currentFile.title.end(), '\r'), currentFile.title.end() );
            
            data << currentFile.title + " Letter Frequency:" << std::endl;
            //print out each letter with its frequency
            for (int i = 0; i < 26; i++ ) {
                data << letters[i] << ": " << ((currentFile.frequency[i]/letterCount)*100) << "%" << std::endl;
            }
        }

        //ask the user if they want to process another book
        std::cout << "Do you want to process another book? (Y/N): ";
        std:: cin >> repeat;
        std::cout << std::endl;
        if (repeat != 'Y') {
            repeat = 'N';
        }
        data << std::endl;
        text.close();
    }
}