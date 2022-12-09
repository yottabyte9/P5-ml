// Project UID db1f506d06d84ab787baf250c265e24e

#include "csvstream.h"
#include <iostream>
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
                    cout << "  " << pair_l.first << ", " << pair_l.second 
                    << " examples, log-prior = " << log_prior(pair_l.first) << endl;
                }
                cout << "classifier parameters:" << endl;
                for(pair<pair<string, string>, int> pair_l: num_posts_label_contain_word){
                    cout << "  " << pair_l.first.first << ":" 
                    << pair_l.first.second << ", count = " 
                    << pair_l.second << ", log-likelihood = "
                    << log_likelihood(pair_l.first.first, pair_l.first.second) << endl;
                }
                cout << endl;
                
            }
            map<string, string> row;
            csvstream csvin(testing_name, ',', true);
            cout << "test data:" << endl;
            int numcorrect = 0;
            int numtotal = 0;
            while(csvin >> row){
                //n = stoi(row["n"]);
                //unique_views = stoi(row["unique_views"]);
                tag =  row["tag"];
                content = row["content"];
                pair<string, double> pred_temp = prediction(content);
                //cout << pred_temp.first << pred_temp.second << endl;
                cout << "  correct = " << tag << ", predicted = " << 
                pred_temp.first << ", log-probability score = " 
                << pred_temp.second << endl;
                cout << "  content = " << content << endl << endl;
                if( tag == pred_temp.first ){
                    numcorrect ++;
                }
                numtotal ++;
            }
            cout << "performance: " << numcorrect << " / " << numtotal 
            << " posts predicted correctly" << endl;
        }
        pair<string, double> prediction(string string_in){
            //log_prior, log_likelihood
            //return pair
            pair<string, double> rpair; //return pair (label predicted, score)
            double temp_score;
            set<string> string_unique = unique_words(string_in);
            rpair.first = *labels_unique.begin();
            rpair.second = log_prior(*labels_unique.begin()); //initializing rpair.first
            for (string w: string_unique){ //initializing rpair.second
                    rpair.second += log_likelihood(rpair.first, w);
            }
            for (string label: labels_unique){
                temp_score = log_prior(label);
                //cout << label << " " << temp_score;
                for (string w: string_unique){
                    temp_score += log_likelihood(label, w);
                    //cout << temp_score;
                }
                if(temp_score > rpair.second){
                    //cout << "condition hit";
                    rpair.first = label;
                    rpair.second = temp_score;
                }
                //cout << endl;
                //cout << " current label tested in prediction " << label << endl;
                //cout << " current score " << temp_score; 
            }
            //cout << rpair.first << " " << rpair.second << " ";
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
            if(word_freq_in_set.find(w) == word_freq_in_set.end()){
                // word does not exist in set
                //cout << " C1 ";
                return log( 1.0/total_num_posts_in_set );
            }
            if(num_posts_label_contain_word.find(p) 
            == num_posts_label_contain_word.end()){
                //word does exist in set but not under label C
                //cout << " C2 ";
                return log(double(word_freq_in_set.find(w)->second)
                /total_num_posts_in_set);
            }
            double num = num_posts_label_contain_word.find(p)->second;
            double denom = label_freq_in_set.find(c)->second;
            double logl = log(double(num)/denom);
            //cout << " C3 ";
            return logl;
        }

        //function to put private variables into maps
        void variables_in_maps(){
            map<string, string> row;
            csvstream csvin(training_name, ',', true);
            if(debug_in){
                cout << "training data:" << endl;
            }
            while(csvin >> row){
                string tag =  row["tag"];
                string content = row["content"];
                if(debug_in){
                    cout << "  label = " << tag << ", content = " << content << endl;
                }
                //number 1
                total_num_posts_in_set++;
                //number 3
                set<string> content_strings = unique_words(content);
                for( string s: content_strings ){
                    if(words_unique.find(s) == words_unique.end()){
                        //if word is not in the set
                        word_freq_in_set.insert(make_pair(s,1));
                        words_unique.insert(words_unique.begin(), s);
                    }
                    else{
                        (word_freq_in_set.find(s)->second)++; //if word is already in map
                    }
                }
                //number 4
                if (label_freq_in_set.find(tag) == label_freq_in_set.end()){//if label is not in set
                    label_freq_in_set.insert(make_pair(tag, 1));
                    labels_unique.insert(labels_unique.begin(), tag);
                }
                else{
                    label_freq_in_set.find(tag)->second++;
                }
                //number 5
                set<string> temp_set_string = unique_words(content);
                for( string unique_string_in_post: temp_set_string ){
                    if(num_posts_label_contain_word.find
                    (make_pair(tag,unique_string_in_post)) 
                    == num_posts_label_contain_word.end()){
                        num_posts_label_contain_word.insert
                        (make_pair((make_pair(tag, unique_string_in_post)),1));
                    }
                    else{
                        num_posts_label_contain_word.find
                        (make_pair(tag,unique_string_in_post))->second++;
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
        set<string> labels_unique;
        set<string> words_unique;
        map<string, int> word_freq_in_set; //#3
        int total_num_posts_in_set = 0; //#1
        int vocab_size = word_freq_in_set.size(); //#2
        map<string, int> label_freq_in_set; //#4
        map<pair<string, string>, int> num_posts_label_contain_word; //#5 
        string tag;
        string content;
        //int n;
        //int unique_views;
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
    if(argc != 3 && argc != 4){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    }

    ifstream if_stream1(argv[1]);
    ifstream if_stream2(argv[2]);
    if(!if_stream1.is_open()){
        cout << "Error opening file: " << argv[1] << endl;
        if_stream1.close();
        return 0;
    }
    if(!if_stream2.is_open()){
        cout << "Error opening file: " << argv[2] << endl;
        if_stream1.close();
        return 0;
    }
    if_stream1.close();
    if_stream2.close();

    cout.precision(3);
    Classifier my_class = Classifier(argc, argv);
    my_class.variables_in_maps();
    my_class.test();

}
