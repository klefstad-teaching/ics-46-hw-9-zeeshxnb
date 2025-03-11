#include "ladder.h"

int main(int argc, char* argv[]) {
    cout << "Enter start word: ";
    string start_word;
    cin >> start_word;
    cout << "Enter end word: ";
    string end_word;
    cin >> end_word;
    for (char &c : start_word) c = tolower(c);
    for (char &c : end_word)   c = tolower(c);
    if (start_word == end_word) {
        error(start_word, end_word, "Start and end words must differ.");
        return 1;
    }
    set<string> word_list;
    try {
        load_words(word_list, "words.txt");
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
    if (ladder.empty()) {
        cout << "No ladder found from \"" << start_word << "\" to \"" << end_word << "\"." << endl;
    } else {
        cout << "Found ladder (" << ladder.size() << " words):" << endl;
        print_word_ladder(ladder);
    }
    return 0;
}
