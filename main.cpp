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
            //csvstream csvin("input.csv");
            training_name = inputs[1];
            testing_name = inputs[2];
            if(inputs[3] != nullptr){ //if --debug is there
                debug_in = true;
            }
            else{
                debug_in = false;
            }
        }
        void test(){
            cout << "trained on " << total_num_posts_in_set << " examples" << endl;
            if(debug_in){
                vocab_size = word_freq_in_set.size();
                cout << "vocabulary size = " << vocab_size << endl << endl;
                cout << "classes:" << endl;
                for(pair<string,int> pair_l: label_freq_in_set){
                    cout << "  " << pair_l.first << ", " << pair_l.second << " examples, log-prior = " << log_prior(pair_l.first) << endl;
                }
                cout << "classifier parameters:" << endl;
                for(pair<pair<string, string>, int> pair_l: num_posts_label_contain_word){
                    cout << pair_l.first.first << ":" << pair_l.first.second << ", count = " << pair_l.second << ", log-likelihood = "<< log_likelihood(pair_l.first.first, pair_l.first.second) << endl << endl;
                }
                
            }
            map<string, string> row;
            csvstream csvin(testing_name, ',', true);
            while(csvin >> row){
                n = stoi(row["n"]);
                unique_views = stoi(row["unique_views"]);
                tag =  row["tag"];
                content = row["content"];
                cout << prediction(unique_words(content)).first << " " << prediction(unique_words(content)).second << endl;
            }
        }
        pair<string, double> prediction(set<string> string_in){
            //log_prior, log_likelihood
            //return pair
            pair<string, double> rpair;
            pair<string, double> tpair;
            set<string> tags = unique_words(tag);
            for (string label: tags){
                rpair.first = label;
                rpair.second += log_prior(label);
                for (string w: string_in){
                    rpair.second += log_likelihood(label, w);
                }
                if(tpair.second > rpair.second){
                    tpair = rpair;
                }
            }
            return rpair;
        }
        double log_prior(string c){
            double numerator = label_freq_in_set.find(c)->second;
            double denominator = total_num_posts_in_set;
            double logp = log(numerator/denominator);
            return logp;
        }
        double log_likelihood(string c, string w){
            pair<string, string> p = make_pair(c, w);
            if(word_freq_in_set.find(w) == word_freq_in_set.end()){// word does not exist in set
                return log( 1/total_num_posts_in_set );
            }
            if(num_posts_label_contain_word.find(p) == num_posts_label_contain_word.end()){
                //word does exist in set but not under label C
                return log( word_freq_in_set.find(w)->second/total_num_posts_in_set );
            }
            double num = num_posts_label_contain_word.find(p)->second;
            double denom = label_freq_in_set.find(c)->second;
            double logl = log(num/denom);
            return logl;
        }

        //function to put private variables into maps
        void variables_in_maps(){
            map<string, string> row;
            csvstream csvin(training_name, ',', true);
            while(csvin >> row){
                string tag =  row["tag"];
                string content = row["content"];
                if(debug_in){
                    cout << "label = " << tag << ", content = " << content << endl;
                }
                //number 1
                total_num_posts_in_set++;
                //number 3
                set<string> content_strings = unique_words(content);
                for( string s: content_strings ){
                    if(word_freq_in_set.find(s) == word_freq_in_set.end()){//if word is not in the set
                        word_freq_in_set.insert(make_pair(s,1));
                    }
                    else{
                        (word_freq_in_set.find(s)->second)++; //if word is already in map
                    }
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
        
        set<string> unique_words(const string &str) {
            istringstream source(str);
            set<string> words;
            string word;
            while (source >> word) {
                words.insert(word);
            }
            return words;
        }
    private:
        string training_name;
        string testing_name;
        bool debug_in;
        map<string, int> word_freq_in_set; //#3
        int total_num_posts_in_set = 0; //#1
        int vocab_size = word_freq_in_set.size(); //#2
        map<string, int> label_freq_in_set; //#4
        map<pair<string, string>, int> num_posts_label_contain_word; //#5 
        string tag;
        string content;
        int n;
        int unique_views;
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
    if(argc != 3 || argc != 4){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    }
    cout.precision(3);
    Classifier my_class = Classifier(argc, argv);
    my_class.variables_in_maps();
    my_class.test();

}
