    #include <iostream>  
    #include <stack>  
    #include <list>  
    #include <vector>  
    using namespace std;   
      
    int main() {  
      int n;   
      cin >> n;   
      stack<int> s;   
      list<int> l;  
      for (int i =0; i<n; ++i){  
        int num;  
        cin >> num;   
        l.push_back(num);  
      }  
      
     list<int>:: iterator it;   
      string x;   
      cin >> x;   
      for (char c: x){  
        if (c == 'Q') {  
          if (l.empty()) {  
            cout<< "error" << endl;   
            break;  
          }   
          s.push(l.front());   
          l.pop_front();   
        }  
        if (c == 'S') {  
         if (s.empty()) {  
          cout << "error" << endl;  
         break;   
         }  
         l.push_back(s.top());  
         s.pop(); }   
        if (c == 'P') {  
          for (it = l.begin(); it != l.end(); ++it)  
          {   
            if (next(it) != l.end())  
            cout << *it<< " ";  
            else cout << *it;   
          }  
          cout << endl;  
      
      }  
      }  
      
      return 0;   
    }  
