/*
 * Challenge questions and program design by Anna Zeng, Winter 2020.
 * Stylometry example taken from Ali Malik.
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cmath>

using std::cout;    using std::endl;
using std::vector;  using std::string;
using std::ifstream;

const vector<string> FEATURE_VEC{"a", "about", "above", "after", "again", "against", "all", "am", "an", "and",
                                 "any", "are", "aren't", "as", "at", "be", "because", "been", "before", "being",
                                 "below", "between", "both", "but", "by", "can't", "cannot", "could", "couldn't",
                                 "did", "didn't", "do", "does", "doesn't", "doing", "don't", "down", "during",
                                 "each", "few", "for", "from", "further", "had", "hadn't", "has", "hasn't", "have",
                                 "haven't", "having", "he", "he'd", "he'll", "he's", "her","here", "here's", "hers",
                                 "herself", "him", "himself", "his", "how", "how's", "i", "i'd", "i'll", "i'm",
                                 "i've", "if", "in", "into", "is", "isn't", "it", "it's", "its", "itself", "let's",
                                 "me", "more", "most", "mustn't", "my", "myself", "no", "nor", "not", "of", "off",
                                 "on", "once", "only", "or", "other", "ought", "our", "ours", "ourselves", "out",
                                 "over", "own", "same", "shan't", "she", "she'd", "she'll", "she's", "should",
                                 "shouldn't", "so", "some", "such", "than", "that", "that's", "the", "their",
                                 "theirs", "them", "themselves", "then", "there", "there's", "these", "they",
                                 "they'd", "they'll", "they're", "they've", "this", "those", "through", "to", "too",
                                 "under", "until", "up", "very", "was", "wasn't", "we", "we'd", "we'll", "we're",
                                 "we've", "were", "weren't", "what", "what's", "when", "when's", "where", "where's",
                                 "which", "while", "who", "who's", "whom", "why", "why's", "with", "won't", "would",
                                 "wouldn't", "you", "you'd", "you'll", "you're", "you've", "your", "yours",
                                 "yourself", "yourselves", "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+",
                                 ",", "-", ".", "/", ":", ";", "<", "=", ">", "?", "@", "[", "\\", "]", "^", "_",
                                 "`", "{", "|", "}", "~"};


string fileToString(ifstream& file) {
    string ret = "";
	string line;
	while (getline(file, line)) {
		std::transform(line.begin(), line.end(), line.begin(), tolower);	
		ret += line + " ";
	}
    return ret;
}

int countOccurrences(const string& text, const string& feature) {
    int count = 0;
	string toFind = " " + feature + " ";
	
	auto curr = text.begin();
	auto end = text.end();
	while (curr != end) {
		auto found = std::search(curr, end, toFind.begin(), toFind.end());
		if (found == end) break;
		
		++count;
		curr = found + 1;
	}

    return count;
}

vector<int> createCountVec(const string& text) {
    vector<int> result;	
	for (const string& feature : FEATURE_VEC) {
		result.push_back(countOccurrences(text, feature));
	}
    return result;
}

int dotProduct(const vector<int>& v1, const vector<int>& v2) {
	return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0);
}

double mag(const vector<int>& v) {
	return std::sqrt(dotProduct(v, v));
}

// To clarify, this actually represents cos(theta), so a higher return value
// corresponds to a closer match.
double angle(const vector<int>& v1, const vector<int>& v2) {
	return dotProduct(v1, v2) / (mag(v1) * mag(v2));
}

int main() {
    // Read in the files and convert file to a single string
	ifstream hamilton_fs("res/hamilton.txt");
	ifstream jj_fs("res/jj.txt");
	ifstream madison_fs("res/madison.txt");
	ifstream unknown_fs("res/unknown.txt");

	string hamilton_txt = fileToString(hamilton_fs);
	string jj_txt = fileToString(jj_fs);
	string madison_txt = fileToString(madison_fs);
	string unknown_txt = fileToString(unknown_fs);
	
	// Create our feature vector
	vector<int> hamilton_vec = createCountVec(hamilton_txt);
	vector<int> jj_vec = createCountVec(jj_txt);
	vector<int> madison_vec = createCountVec(madison_txt);
	vector<int> unknown_vec = createCountVec(unknown_txt);

	// Compute the "angle" between feature vector of unknown and each of the three authors
 	cout << "Similarity - hamilton <-> unknown: " << angle(hamilton_vec, unknown_vec) << endl;
	cout << "Similarity - jj <-> unknown: " << angle(jj_vec, unknown_vec) << endl;
	cout << "Similarity - madison <-> unknown: " << angle(madison_vec, unknown_vec) << endl;

	return 0;
}
