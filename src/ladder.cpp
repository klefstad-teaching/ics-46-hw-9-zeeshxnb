#include "ladder.h"


void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No ladder found." << endl;
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