#include <iostream>
#include <string>
using namespace std; 

class leaf {
    public:
        int freq;
        string word; 
        leaf *left, *right; 
        
        leaf(const string &s) {
            word = s; 
            freq= 0; 
            left = right = nullptr; 
        } 
};
class lexicon {
    private:
        leaf *root; 
        
        
        void del_recursively (leaf *p) {
         if (p != nullptr) {
            del_recursively(p->left); 
            del_recursively(p->right);  
            delete p; 
         } else return; 
        }
        
        void insertion( leaf *&p, const string &s) { 
            if (p == nullptr) p = new leaf(s);  
            if (s < p->word) insertion(p->left, s); 
            else if (s > p->word) insertion(p->right, s);
            else if ( s== p->word) p->freq++; 
         }
        
        int looking_up(const leaf *p, const string &s) const {
            if (p == nullptr) return 0; 
            else if (s == p->word) return p->freq;
            else if (s < p->word) return looking_up(p->left, s);
            else return looking_up(p->right, s); 
        }

        int how_deep_does_it_go(const leaf *p, const string &s) {
            if (p == nullptr || looking_up(root, s) == 0) return -1; 
            else if ( s == p->word) return 0; 
            else if ( s < p->word) return 1 + how_deep_does_it_go(p->left, s);
            else return 1 + how_deep_does_it_go(p->right, s); 
        }
        
        leaf*& find (leaf *&p, const string &s) {
            if (p == nullptr || s == p->word) return p; 
            else if (s < p->word) find(p->left,s); 
            else find(p->right, s); 
        }
        
        void replacing (leaf *&p, const string &s1, const string &s2) {
            int k = looking_up(root, s1); 
            if (k == 0) return;
            else if (k > 0){
                deleting_leaf(find(root, s1), s1); 
                int j = looking_up(root, s2); 
                if (j == 0){ 
                    insertion(root, s2); 
                    leaf *&p = find(root, s2); 
                    p->freq = k; 
                } else if (j > 0) { 
                    leaf *&p = find(root, s2);
                    p->freq +=k;}
            }
        }
        void deleting_leaf (leaf *&p, const string &s) {
                if(p == nullptr) return; 
                if (p->left == nullptr && p->right == nullptr) { 
                    delete p;
                    p = nullptr;
                } else if (p->left != nullptr && p->right == nullptr) { 
                    leaf *tmp = p; 
                    p = p->left; 
                    delete tmp; 
                } else if (p->left == nullptr && p->right != nullptr) { 
                    leaf *tmp = p; 
                    p = p->right; 
                    delete tmp; 
                } else { 
                    leaf *pp = p->left; 
                    while (pp->right != nullptr)
                        pp = pp->right; 
                    p->word = pp->word;
                    p->freq = pp->freq; 
                    deleting_leaf(p->left, pp->word); 
                }
            }
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