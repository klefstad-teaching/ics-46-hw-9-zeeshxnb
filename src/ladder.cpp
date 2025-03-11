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

bool is_adjacent(const string& word1, const string& word2) {
    //edge case
    if (word1 == word2) return false;
    //setting variables
    int length1 = (int)word1.size();
    int length2 = (int)word2.size();
    int diff = length1 - length2;

    //if the length is the same
    if (diff == 0) {
        int countDiff = 0;
        for (int i = 0; i < length1; i++) {
            if (word1[i] != word2[i]) {
                countDiff++;
                if (countDiff > 1) return false;
            }
        }
        return (countDiff == 1);
    } else if (diff == 1 || diff == -1) {

        const string& wA = (length1 < length2) ? word1 : word2;
        const string& wB = (length1 < length2) ? word2 : word1;
        int indexA = 0, indexB = 0;
        bool difference = false;

        while (indexA < (int)wA.size() && indexB < (int)wB.size()) {
            if (wA[indexA] != wB[indexB]) {
                if (difference) {
                    return false;
                }
                difference = true;
                indexB++;
            } else {
                indexA++;
                indexB++;
            }
        }
        return true;
    }
    return false;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    //edge cases
    if (begin_word == end_word) {
        return {};
    }

    if (word_list.find(end_word) == word_list.end()) {
        return {};
    }
    
    //setting stuff up
    queue<vector<string>> lq;
    lq.push({ begin_word });
    set<string> visited;
    visited.insert(begin_word);

    //main function
    while (!lq.empty()) {
        vector<string> ladder = lq.front();
        lq.pop();
        const string& last_word = ladder.back();

        for (auto const &dict_word : word_list) {
            if (is_adjacent(last_word, dict_word) && !visited.count(dict_word)) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(dict_word);
                visited.insert(dict_word);

                if (dict_word == end_word) {
                    return new_ladder;
                }

                lq.push(new_ladder);
            }
        }
    }
    return {};
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

//copied from instructions
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