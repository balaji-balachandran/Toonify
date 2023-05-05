#include "Huffman.h"
using namespace std;
vector<unsigned char> decode(string sequence, string binary_val_map) {
    vector<string> comma_sep;
    map<string, unsigned char> binary_grp;
    stringstream s_stream(binary_val_map);
    while (s_stream.good()) {
        string substr;
        getline(s_stream, substr, ',');
        comma_sep.push_back(substr);
    }
    for (auto elem : comma_sep) {
        vector<string> row_content;
        stringstream s_stream(elem);
        while (s_stream.good()) {
            string substr;
            getline(s_stream, substr, ':');
            row_content.push_back(substr);
        }
        binary_grp.insert(pair<string, unsigned char>(row_content[0], row_content[1].at(0)));
    }
    string bt_;
    for (auto x : sequence) {
        bt_ += x;
        if (binary_grp.count(bt_)) {
            result.push_back(binary_grp.at(bt_));
            bt_ = "";
        }
    }
    return result;
}