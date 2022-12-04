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
                /*
                if (tag is not in map()
                    label_freq_in_set.insert(tag, 1);
                if (tag is already in map)
                    tag++
                */
               
            }
        }
        //functions for 
    private:
        string training_name;
        string testing_name;
        bool debug_in;
        map<string, int> word_freq_in_set; //#3
        int total_num_posts_in_set; //#1
        int vocab_size; //#2
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
