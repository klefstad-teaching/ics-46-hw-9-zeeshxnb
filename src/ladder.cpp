#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "error with the following words: \"" << word1 << "\" and \"" << word2 
         << "\": " << msg << endl;
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in.is_open()) {
        throw runtime_error("couldn't open file: " + file_name);
    }
    string word;
    while (in >> word) {
        for (char &c : word) {
            c = tolower(c);
        }
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "no ladder found" << endl;
        return;
    }
    
    for (size_t i = 0; i < ladder.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << ladder[i];
    }
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed" : " failed") << endl;}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    {
        auto ladder = generate_word_ladder("cat", "dog", word_list);
        my_assert(ladder.size() == 4);
    }
    {
        auto ladder = generate_word_ladder("marty", "curls", word_list);
        my_assert(ladder.size() == 6);
    }
    {
        auto ladder = generate_word_ladder("code", "data", word_list);
        my_assert(ladder.size() == 6);
    }
    {
        auto ladder = generate_word_ladder("work", "play", word_list);
        my_assert(ladder.size() == 6);
    }
    {
        auto ladder = generate_word_ladder("sleep", "awake", word_list);
        my_assert(ladder.size() == 8);
    }
    {
        auto ladder = generate_word_ladder("car", "cheat", word_list);
        my_assert(ladder.size() == 4);
    }
}