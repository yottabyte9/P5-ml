#include "csvstream.h"
#include <iostream>
#include "BinarySearchTree.h"
#include "Map.h"
#include <string>
#include <map>
#include <set>
#include <cmath>

using namespace std;

class Classifier{
    public:
        Classifier(int numInputs, char** inputs){
            //store input in private
            csvstream csvin("input.csv");

        }
        void test(int numInputs, char** inputs){
            //
        }
        //function to put private variables into maps
        void variables_in_maps(){
            map<string, string> row;
            csvstream csvin(training_name, ',', true);
            while(csvin >> row){
                string tag =  row["tag"];
                string content = row["content"];
                //number 1
                total_num_posts_in_set++;
                //number 3
                if(word_freq_in_set.find(tag) == word_freq_in_set.end())//if word is not in the set
                    word_freq_in_set.insert(make_pair(tag,1));
                else{
                    word_freq_in_set.find(tag)->second++; //if word is already in map
                }
                //number 4
                if (label_freq_in_set.find(tag) == label_freq_in_set.end())//if label is not in set
                    label_freq_in_set.insert(make_pair(tag, 1));
                else{
                    label_freq_in_set.find(tag)->second++;
                }
                //number 5
                set<string> temp_set_string = unique_words(content);
                for( string unique_string_in_post: temp_set_string ){
                    if(num_posts_label_contain_word.find(make_pair(tag,unique_string_in_post)) == num_posts_label_contain_word.end()){
                        num_posts_label_contain_word.insert(make_pair((make_pair(tag, unique_string_in_post)),1));
                    }
                    else{
                        num_posts_label_contain_word.find(make_pair(tag,unique_string_in_post))->second++;
                    }
                }
            }
        }
    private:
        string training_name;
        string testing_name;
        bool debug_in;
        map<string, int> word_freq_in_set; //#3
        int total_num_posts_in_set; //#1
        int vocab_size = word_freq_in_set.size(); //#2
        map<string, int> label_freq_in_set; //#4
        map<pair<string, string>, int> num_posts_label_contain_word; //#5 
};

set<string> unique_words(const string &str) {
  istringstream source(str);
  set<string> words;
  string word;
  while (source >> word) {
    words.insert(word);
  }
  return words;
}

int main(int argc, char **argv) {

    map<pair<string, string>, int> my_map;


    csvstream csvin("input.csv");

    map<string, string> row;

    while(csvin >> row){
        string tag =  row["tag"];
        string content = row["content"];
    }


}
