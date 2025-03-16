#include "ladder.h"

#include <algorithm>
#include <stack>
#include <unordered_set>

//using a queue to store partial ladders that represent possibilities to explore. 
//Each partial ladder is a stack, which means that your overall collection must be a queue of stacks.
void error(string word1, string word2, string msg){
    cerr << "Whoops the problem is" << msg << " for words - " <<word1 << " and " <<word2;
}

// bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
//     int diffCount = 0;
//     for (size_t i = 0; i < str1.size(); i++){
//         if (str1[i] != str2[i]) {
//             diffCount++;
//             if (diffCount > d) return false;
//         }
//     }
//     return diffCount == d;
// }
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if (str1 == str2) return true;
    int len_word1 = str1.size();
    int len_word2 = str2.size();
    
    if (abs(len_word2 - len_word1) > 1) return false;
    
    // if (len_word1 == len_word2){ //ok since eq
    //     return edit_distance_within(str1,str2,1);
    // }

    int i = 0;
    int j = 0;
    int diffCount = 0;
    const std::string& longer = (len_word1 > len_word2) ? str1 : str2;
    const std::string& shorter = (len_word1 > len_word2) ? str2 : str1;
    int len_of_longer = longer.size();
    int len_of_shorter = shorter.size();
    
    while (i < len_of_shorter && j < len_of_longer){
        if (shorter[i] != longer[j]) {
            diffCount++;
            if (diffCount > d) return false;
            if (len_word1 == len_word2) { // If they are the same length, move both indices (substitution case)
                i++;
            }
            j++; //move index oflonger word
        } else {
            i++; //move index for both if the chr are the same
            j++;
        }
    }
    // return diff == 1 || (diff == 0 && j == longer.size() - 1); //in case the last letter of the longer word is the letter change
    //return diffCount == d;
    return diffCount + (len_of_longer - j) == d;
    // return true;

}
//Start by examining ladders that are one step away from the original word, where only one letter is changed
bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1,word2,1);
}

//Another subtle issue is that you must not reuse words that have been included in a previous shorter ladder.
//you should not enqueue the longer ladder in your algorithm
//To implement this strategy, keep track of the set of words that have already been used in any ladder, and ignore those words if they come up again.
//Use our file words.txt for your dictionary of words, and ignore letter cases.

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue< stack<string> > ladder_queue; //queue of stacks
    set<string> visited;

    stack<string> first_ladder;
    first_ladder.push(begin_word);
    ladder_queue.push(first_ladder);
    visited.insert(begin_word);

    while (!ladder_queue.empty()){
        stack<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word_of_curr_path = ladder.top();

        for (const string& word : word_list){
            if (is_adjacent(last_word_of_curr_path, word) && visited.find(word) == visited.end()){ //word not in set yet and adj
                stack<string> new_ladder = ladder;
                new_ladder.push(word);
                //visited.insert(word);

                if (word == end_word){
                    vector<string> result;
                    while (!new_ladder.empty()) {
                        result.push_back(new_ladder.top());
                        new_ladder.pop();
                    }
                    reverse(result.begin(), result.end());
                    return result;
                }

                ladder_queue.push(new_ladder);
                visited.insert(word); //moved here for redundant paths i think fix
            }
        }
    }

    return {}; //no valid ladder
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
    if (!file){
        error(file_name, "word_list", "Error: Cannot open file" );
        return;
    }
    string word;
    while (file >> word){
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder){
    if (ladder.empty()){
        error("printing", "ladder", "the ladder is empty" );
        return;
    }
    
    for (size_t i = 0; i < ladder.size(); i++){
        cout << "Word ladder found:" << ladder[i] << " ";
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}

//AYEEEEEEE!!!!! FINALLLLYYYY
// generate_word_ladder("cat", "dog", word_list).size() == 4 passed
// generate_word_ladder("marty", "curls", word_list).size() == 6 passed
// generate_word_ladder("code", "data", word_list).size() == 6 passed
// generate_word_ladder("work", "play", word_list).size() == 6 passed
// generate_word_ladder("sleep", "awake", word_list).size() == 8 passed
// generate_word_ladder("car", "cheat", word_list).size() == 4 passed