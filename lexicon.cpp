#include <iostream>
#include <string>
using namespace std; 

// Leaf (aka node class) --could have been a struct node but we are learning classes 
// so I thought it would be right to have a class implementation :p
class leaf {
    public:
        int freq;
        string word; 
        leaf *left, *right; 
        
        // leaf constructor
        // using const strings throughout to prevent rewriting of the string and overall taking up less space
        leaf(const string &s) {
            word = s; 
            freq= 0; 
            left = right = nullptr; 
        } 
};
// Lexicon using a binary search tree implementation
class lexicon {
    private:
        // root of bs tree 
        leaf *root; 
        
        // Below are auxilliary functions for the public functions (mostly using recursion):
        
        // Delete tree
        void del_recursively (leaf *p) {
         if (p != nullptr) {
            del_recursively(p->left); //deletes left
            del_recursively(p->right);  // deletes right 
            delete p; 
         } else return; // nothing to delete anymore 
        }
        
        // Insert new node
        void insertion( leaf *&p, const string &s) { // pass by pointer to a reference to change the tree 
            if (p == nullptr) p = new leaf(s);  
            if (s < p->word) insertion(p->left, s); 
            else if (s > p->word) insertion(p->right, s);
            else if ( s== p->word) p->freq++; // if word is found again just increase the frequency
         }
        
        // Look up the word- returns the frequency of it 
        int looking_up(const leaf *p, const string &s) const {
            if (p == nullptr) return 0; 
            else if (s == p->word) return p->freq;
            else if (s < p->word) return looking_up(p->left, s); // looks into left child 
            else return looking_up(p->right, s); // looks into right child
        }

        // Find the depth of the word
        int how_deep_does_it_go(const leaf *p, const string &s) {
            if (p == nullptr || looking_up(root, s) == 0) return -1; // word not found
           
            // the instructions mentioned that the root is at depth 1 but grader didn't agree :(
            else if ( s == p->word) return 0; 
            else if ( s < p->word) return 1 + how_deep_does_it_go(p->left, s); // includes the level it's at (so + 1)
            else return 1 + how_deep_does_it_go(p->right, s); 
        }
        
        // Finds the specific node needed and returns it in the tree (location, frequency, etc)
        leaf*& find (leaf *&p, const string &s) {
            if (p == nullptr || s == p->word) return p; 
            else if (s < p->word) find(p->left,s); 
            else find(p->right, s); 
        }
        
        // Replace the two strngs given
        void replacing (leaf *&p, const string &s1, const string &s2) {
            int k = looking_up(root, s1); // frequency of string 1
            if (k == 0) return; // string 1 not found so don't do anything
            else if (k > 0){
                deleting_leaf(find(root, s1), s1); // deletes string 1 
                int j = looking_up(root, s2); // frequency of string 2
                if (j == 0){ // Case in which s2 not found in the tree
                    insertion(root, s2); // It's inserted 
                    leaf *&p = find(root, s2); // location is found
                    p->freq = k; // frequency updated 
                } else if (j > 0) { 
                    leaf *&p = find(root, s2);
                    p->freq +=k;}
            }
        }
        // Deletes the leaf/node function 
        void deleting_leaf (leaf *&p, const string &s) {
                if(p == nullptr) return; // p is null
                if (p->left == nullptr && p->right == nullptr) { // both children are null
                    delete p;
                    p = nullptr;
                } else if (p->left != nullptr && p->right == nullptr) { // only right child is null
                    leaf *tmp = p; 
                    p = p->left; 
                    delete tmp; 
                } else if (p->left == nullptr && p->right != nullptr) { // only left child is null
                    leaf *tmp = p; 
                    p = p->right; 
                    delete tmp; 
                } else { // node has a left and a right child
                    leaf *pp = p->left; 
                    while (pp->right != nullptr) // find left child's max 
                        pp = pp->right; 
                    p->word = pp->word;
                    p->freq = pp->freq; 
                    deleting_leaf(p->left, pp->word); // delete starting from the initial node (p->left) so that the next leaf is also deleted
                }
            }

        // Prints out tree
        void print(ostream &out, const leaf *p) const {
            if (p != nullptr) {
            print(out, p->left);
            out << p->word << " " << p->freq << endl;
            print(out, p->right);
        }
    }

    public:
    lexicon(): root(nullptr){}
    ~lexicon() { del_recursively(root);}
    void insert(const string &s){ insertion(root, s); }
    int lookup(const string &s) const { return looking_up(root, s);}
    int depth(const string &s) { return how_deep_does_it_go(root, s);}
    void replace (const string &s1, const string &s2) { replacing(root, s1, s2);}
    friend ostream & operator << (ostream &out, const lexicon &l){
        l.print(out, l.root); 
        return out; 
    }
};