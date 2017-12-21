# 745 Design a class WordFilter that supports one function, WordFilter.f(String prefix, String suffix). It will return the word with given prefix and suffix with maximum weight. If no word exists, return -1.
#include <vector>
using namespace std;

struct Trie {
	vector<int> words;
	vector<Trie *> children;
	Trie() {
		children = vector<Trie *>(26, nullptr);
	}

	~Trie() {
		for (int i = 0; i < 26; i++) {
			if (children[i]) delete children[i];
		}
	}

	
