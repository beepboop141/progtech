    #include <iostream>  
    #include <string>  
    #include <map>  
    #include <set>  
    #include <vector>  
    using namespace std;   
      
    int main (){  
      int N, D;   
      cin >> N >> D;   
      
      int d;  
      string w;   
      map<int, multiset<string>> ktirioantoxisylikwn;  
      for (int i =0; i < N; ++i) {  
        cin >> d >> w;   
        ktirioantoxisylikwn[d].insert(w);   
      }  
      int maximum = 0;  
      for (const auto& it: ktirioantoxisylikwn) {  
        maximum = max(maximum,int( it.second.size()));  
      }  
      set<string> idrk_whatimdoing;   
     for (auto const it: ktirioantoxisylikwn) {    
       if (it.second.size() == maximum){  
         for (const auto & word: it.second) {  
           idrk_whatimdoing.insert(word);  
         }  
         cout << "largest dictionary is "<< it.first <<" with "  
         << idrk_whatimdoing.size()<< " word(s)"<< endl;  
         break;
         }  
       }  
      
     set<string> com;   
     for (const auto & word: idrk_whatimdoing) {   
      bool foundinall= true;  
     for (const auto& dict : ktirioantoxisylikwn){  
      if(dict.second.find(word) == dict.second.end()){  
       foundinall = false;   
        break;   
      }  
     }  
      if (foundinall) {  
        com.insert(word);  
      }    
     }  
       
     for (const auto& str: com) {  
       cout << str << endl;   
     }  
     cout << com.size() << " word(s) appear in all dictionaries" << endl;   
      
      return 0;   
    }  
