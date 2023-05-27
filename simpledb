    #include <iostream>  
    #include <vector>  
    #include <string>  
    #include <algorithm>  
    using namespace std;   
      
    struct worker {  
      int id;   
      string f_name;  
      string l_name;    
      int year;   
      int salary;   
    };  
      
    bool compareby_id(const worker &a, const worker&b) {  
      return a.id < b.id;  
    }  
    bool id2(const worker &a, const worker &b){  
      return a.id > b.id;   
    }   
      
    bool by_year (const worker &a, const worker &b){  
      if(a.year == b.year) return a.id < b.id;   
       return a.year < b.year;   
    }  
    bool yr2 (const worker &a, const worker &b){  
        if(a.year == b.year) return a.id < b.id;  
      return a.year> b.year;   
    }  
      
    bool by_name (const worker &a, const worker &b){  
      if (a.l_name == b.l_name) return a.f_name < b.f_name;  
      return a.l_name < b.l_name; }  
    bool name2 (const worker &a, const worker &b){  
     if (a.l_name == b.l_name) return a.f_name  >b.f_name;     
      return a.l_name > b.l_name;   
    }  
      
    bool by_salary(const worker &a, const worker &b){  
        if(a.salary == b.salary) return a.id < b.id;  
      return a.salary < b.salary; }  
     bool sal2(const worker &a, const worker &b){  
         if(a.salary == b.salary) return a.id < b.id;  
       return a.salary > b.salary;   
    }  
      
    int main(){  
      int n;   
      int m;   
      cin >> n;  
     vector<worker> w(n);    
      for (int i =0; i<n; ++i){  
        cin >> w[i].id >> w[i].f_name >>  w[i].l_name >> w[i].year>> w[i].salary;   
      }  
      cin >> m;  
     vector<string> x(m);  
     vector<string> y(m);   
      vector<int>  k(m);  
      for (int i =0; i < m; ++i){  
       cin >> x[i]>> y[i] >> k[i];  
      }   
      vector<worker>:: iterator e;   
      for (int i =0; i <m; ++i){  
        if (x[i] == "id") {  
          if (y[i] == "asc") sort(w.begin(), w.end(), compareby_id);   
           else  sort(w.begin(), w.end(), id2);   
    }  
        if (x[i] == "name"){  
          if (y[i] == "asc")  sort(w.begin(), w.end(), by_name);  
                      else  sort(w.begin(), w.end(), name2);  
        } if (x[i] == "year") {  
          if (y[i] == "asc")  sort(w.begin(), w.end(), by_year);  
                                          else sort(w.begin(), w.end(), yr2);  
                                                            
        } if (x[i] == "salary") {  
          if (y[i] == "asc")  sort(w.begin(), w.end(), by_salary);  
                                            else   sort(w.begin(), w.end(), sal2);  
        }  
      
        cout << "Query: "<< x[i] << " "<< y[i]<< " "<< k[i] << endl;  
        for (e = w.begin(); e != w.begin()+ k[i]; e++){  
        cout<< e->id << " "<< e->f_name<< " " << e->l_name << " " <<e->year << " " << e->salary<< endl;  
      }  
      
      }  
      return 0;   
    }  
