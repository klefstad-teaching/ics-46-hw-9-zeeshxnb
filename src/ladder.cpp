#include "ladder.h"

void error(string word1, string word2, string msg) {
    std::cout << "error with the following words: \"" << word1 << "\" and \"" << word2 
         << "\": " << msg << endl;
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in.is_open()) {
        //error function works for words and not a general one so throw a runtime
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

//im stupid this is so much easier 
bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();

    if (abs(len1 - len2) > d){
        return false;      
    }
    //index strings
    int i = 0, j = 0;  
    int diff = 0;      // track differences

    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            diff++;
            if (diff > d) { return false; }

            if (len1 > len2) { i++; }

            else if (len1 < len2) { j++; }

            else {i++, j++; }  

        } else {
            i++, j++;  
        }
    }

    diff += (len1 - i);
    diff += (len2 - j);

    return diff <= d;
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
        cout << "No word ladder found." << endl;
    } else {
        cout << "Word ladder found: ";
        for (const auto& word : ladder) {
            cout << word << " ";
        }
        cout << endl;
    }
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