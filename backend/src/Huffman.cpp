#include "Huffman.h"
using namespace std;
vector<int> decode(string sequence, string binary_val_map) {
    vector<string> comma_sep;
    vector<int> result;
    std::map<string, string> binary_grp;
    stringstream s_stream(sequence);
    while (s_stream.good()) {
        string substr;
        getline(s_stream, substr, ',');
        result.push_back(substr);
    }
    for (int i = 0; i < result.size(); i++) {
        int pos = result.at(i).find(':');
        binary_grp.at(result.at(i).substr(0, pos)) = result.at(i).substr(pos, result[i].size() - pos);
    }
    string bt_;
    for (auto x : sequence) {
        bt_ += x;
        if (binary_grp.contains(bt_)) {
            result.push_back(stoi(binary_grp.at(bt_)));
            bt_ = "";
        }
    }
    return result;
}