#include "ladder.h"
#define my_assert(e) {cout << #e << ((e) ? " passed" : " failed") << endl;}

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (abs(int(str1.length()) - int(str2.length())) > d) {
        return false;
    }

    int diff_count = 0;
    int i = 0, j = 0;

    while (i < str1.length() && j < str2.length()) {
        if (str1[i] != str2[j]) {
            diff_count++;
            if (diff_count > d) return false;

            if (str1.length() > str2.length()) {
                i++;
            } else if (str1.length() < str2.length()) {
                j++;
            } else {
                i++;
                j++;
            }
        } else {
            i++;
            j++;
        }
    }

    if (i < str1.length() || j < str2.length()) {
        diff_count++;
    }

    return diff_count <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    set<string> visited;
    ladder_queue.push({begin_word});
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && !visited.count(word)) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                visited.insert(word);
                
                if (word == end_word) return new_ladder;
                ladder_queue.push(new_ladder);
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    } else {
        cout << "Word ladder found: ";  
        for (size_t i = 0; i < ladder.size(); ++i) {
            if (i > 0) cout << " ";  
            cout << ladder[i];
        }
        cout << endl;
    }
}

void verify_word_ladder() {
    set<string> word_list;
    
    // Load dictionary words from "words.txt"
    load_words(word_list, "src/words.txt");

    // Run test cases and verify the correct number of steps
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
    
    cout << "All test cases completed!" << endl;
}
