#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;

    void autocompleteUtil(TrieNode* node, string prefix, vector<string>& results) {
        if (node->isEndOfWord) results.push_back(prefix);

        for (auto& child : node->children) {
            autocompleteUtil(child.second, prefix + child.first, results);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }

    bool search(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return current->isEndOfWord;
    }

    vector<string> autocomplete(const string& prefix) {
        TrieNode* current = root;
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return {};
            }
            current = current->children[c];
        }
        vector<string> results;
        autocompleteUtil(current, prefix, results);
        return results;
    }
};

int main() {
    Trie trie;
    trie.insert("hello");
    trie.insert("hell");
    trie.insert("heaven");
    trie.insert("heavy");

    cout << "Search results:\n";
    cout << "hello: " << (trie.search("hello") ? "found" : "not found") << endl;
    cout << "heaven: " << (trie.search("heaven") ? "found" : "not found") << endl;
    cout << "hell: " << (trie.search("hell") ? "found" : "not found") << endl;
    cout << "heavy: " << (trie.search("heavy") ? "found" : "not found") << endl;
    cout << "he: " << (trie.search("he") ? "found" : "not found") << endl;

    cout << "\nAutocomplete results for 'he':\n";
    vector<string> results = trie.autocomplete("he");
    for (string& result : results) {
        cout << result << endl;
    }

    return 0;
}
