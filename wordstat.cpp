    #include <iostream>  
    #include <string>  
    #include <map>  
    #include <vector>  
    #include <set>  
    #include <algorithm>  
    using namespace std;   
    bool longest (const string &a, const string &b) {  
      if (a.size() == b.size()) {  
        return a < b;   
      }  
      return a.size() > b.size();  
    }  
    bool shortest(const string &a, const string &b){  
      if (a.size() == b.size()) return a < b;   
      return a.size() < b.size();   
    }  
    int main () {  
      
      string s;   
      map <char, vector<string>> dic;   
      while (cin >> s) {  
        dic[s[0]].push_back(s);    
      }  
      
      set<string> x;   
      for (const auto &it : dic) {  
        x.clear();   
        cout << it.first << ": " << it.second.size() << " word(s), ";  
        x.insert(it.second.begin(), it.second.end());   
        cout << x.size() << " unique word(s), ";  
        vector<string> temp;   
        for (const string & word: it.second){  
          temp.push_back(word);  
        }   
        sort(temp.begin(), temp.end(), longest);   
        cout << "longest '"<< temp.front() << "' and shortest '";  
        sort(temp.begin(), temp.end(), shortest);  
          cout << temp.front() << "'"<<endl;  
        }  
      
      return 0;   
    }  
