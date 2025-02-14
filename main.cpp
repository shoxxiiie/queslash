#include <iostream>
#include <fstream>

using namespace std;

struct WordNode {
    string word;
    int count;
    WordNode* next;
};

string normalizeWord(const string& word) {
    string result;
    for (char c : word) {
        if (isalnum(c)) { 
            result += tolower(c);
        }
    }
    return result;
}

void addWord(WordNode*& head, const string& word) {
    WordNode* current = head;
    WordNode* prev = nullptr;
    
    while (current) {
        if (current->word == word) {
            current->count++;
            return;
        }
        prev = current;
        current = current->next;
    }
    
    WordNode* newNode = new WordNode{word, 1, nullptr};
    if (prev) {
        prev->next = newNode;
    } else {
        head = newNode;
    }
}

void printWords(WordNode* head, ofstream& outputFile) {
    WordNode* mostFrequent = nullptr;
    
    cout << "слово - количество" << endl;
    outputFile << "слово - количество" << endl;
    
    for (WordNode* current = head; current; current = current->next) {
        cout << current->word << " - " << current->count << endl;
        outputFile << current->word << " - " << current->count << endl;
        
        if (!mostFrequent || current->count > mostFrequent->count) {
            mostFrequent = current;
        }
    }
    
    if (mostFrequent) {
        cout << "\nсамое частое слово: " << mostFrequent->word << " (" << mostFrequent->count << ")" << endl;
        outputFile << "\nсамое частое слово: " << mostFrequent->word << " (" << mostFrequent->count << ")" << endl;
    }
}

void deleteList(WordNode* head) {
    while (head) {
        WordNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    WordNode* wordList = nullptr;
    string line, word;
    
    if (!inputFile) {
        cerr << "ошибка открытия файла input.txt" << endl;
        return 1;
    }
    
    while (getline(inputFile, line)) {
        string currentWord;
        for (char c : line) {
            if (isalnum(c)) {
                currentWord += tolower(c);
            } else if (!currentWord.empty()) {
                addWord(wordList, currentWord);
                currentWord.clear();
            }
        }
        if (!currentWord.empty()) {
            addWord(wordList, currentWord);
        }
    }
    inputFile.close();
    
    printWords(wordList, outputFile);
    outputFile.close();
    
    deleteList(wordList);
    return 0;
}
