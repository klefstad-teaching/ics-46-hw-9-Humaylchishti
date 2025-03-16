#include "ladder.h"

void test_ladder_path(){
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    string start_word, end_word;
    cout << "Enter start word: ";
    cin >> start_word;
    cout << "Enter end word: ";
    cin >> end_word;
    
    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
    print_word_ladder(ladder);
}

int main() {
    verify_word_ladder();
    test_ladder_path();
    return 0;
}

