    #include <iostream>  
    #include <vector>  
    #include <map>  
    #include <string>  
    #include <iomanip>  
    #include <cmath>  
    #include <set>  
    using namespace std;   
      
    struct point {  
      double x;   
      double y;   
      string p;   
    };  
    struct xndy {  
      double x;   
      double y;   
    };  
      
    double distance (double x1, double y1, double x2, double y2){  
      double dx = x1-x2;   
      double dy = y2-y1;   
      return pow((dx*dx + dy*dy), 0.5);   
    }  
    int main() {  
      int N;   
      cin >> N;  
      vector<point> points(N);   
      for (int i =0; i<N; ++i)  
        cin >> points[i].x >> points[i].y >> points[i].p;   
      int k;   
      cin >> k;  
      vector<xndy> interest(k);   
      for (int i =0; i<k; ++i)  
        cin >> interest[i].x >> interest[i].y;  
      map<string, set<double>> saske;  
     map<string, set<double>> :: iterator q;    
      for (const auto& it: interest){   
        cout << int(it.x) << " "<< int(it.y) << endl;    
        for (const auto& pt: points) {  
          double d = distance(it.x, it.y, pt.x, pt.y);   
          saske[pt.p].insert(d);   
        }  
        for(const auto &j : saske) {  
          cout << "  "<< j.first <<" ";  
          cout<< fixed<< setprecision(3) <<*(j.second.begin())<< endl; 
        }  
        saske.clear();   
      }  
      return 0;   
    }  
