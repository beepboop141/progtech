#include <iostream>  
#include <vector>  
#include <iomanip>  
#include <string>  
#include <unordered_map>  
#include <cmath>  
#include <algorithm>  
using namespace std;   
  
struct point {  
  double x;   
  double y;   
  string category;   
};  
  
double distance(double x1, double y1, double x2, double y2){  
  double dx = x1-x2;   
  double dy = y1-y2;   
  return pow(dx*dx + dy*dy, 0.5);   
}  
bool alphab(const pair<string, vector<double>> &a, const pair<string, vector<double>> &b){  
  return a.first < b.first;   
}  
  
int main() {  
  int n;   
  cin >> n;   
  vector <point> pt(n);   
  unordered_map<string, vector<double>> distances;   
  
  for (int i=0; i<n; i++){  
   cin >> pt[i].x >> pt[i].y >> pt[i].category;  
  }  
  
  int k;   
  cin >> k;   
  vector<double> xtrack(k), ytrack(k);   
  for (int i =0; i < k; ++i) {  
    cin >> xtrack[i] >> ytrack[i];  
  }  
      
    for (int i =0; i< k; i++){  
     cout << int(xtrack[i])<< " " <<int( ytrack[i]) << endl;  
     distances.clear();    
     for(const auto &p: pt){  
       double d = distance(p.x, p.y, xtrack[i], ytrack[i]);  
       distances[p.category].push_back(d);   
     }  
    vector<pair<string, vector<double>>> sorted_d(distances.begin(), distances.end());   
   sort(sorted_d.begin(), sorted_d.end(), alphab);   
  
     for (const auto &t : sorted_d) {   
      vector<double> vals =t.second;   
      double minval = *min_element(vals.begin(), vals.end());   
      cout << "  "<< t.first << " " <<fixed << setprecision(3)<<  minval << endl;  
     }    
  }  
  
  return 0;  
}
