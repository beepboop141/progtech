    #include <iostream>   
    #ifndef CONTEST  
    #include "fullratio.hpp"   
    #endif  
      
    using namespace std;   
      
    rational::rational (int n, int d) {  
      nom = n/ gcd(n, d);   
      den = d/ gcd(n, d);   
      if (nom ==0)   
        den =1;   
      else if (den <0) {  
        nom *= -1;   
        den *= -1;   
      }  
    }  
      
    int rational:: gcd(int x, int y){  
      y = abs(y);   
      x = abs(x);   
      while (y>0 && x>0){  
        if (x>y)  
          x %= y;   
        else  
          y %= x;   
      }  
      return x +y;   
    }  
      
    rational operator + (const rational &x, const rational &y){  
      rational res(x.nom *y.den +y.nom *x.den, x.den *y.den);  
      return res;   
    }  
      
    rational operator -(const rational &x, const rational &y){  
      rational res(x.nom *y.den - y.nom*x.den, x.den *y.den);   
      return res;   
    }  
      
    rational operator / (const rational &x, const rational &y){  
      rational res(x.nom *y.den, y.nom*x.den);  
      return res;   
    }  
      
    rational operator * (const rational &x, const rational &y){  
      rational res(x.nom *y.nom, x.den*y.den);   
      return res;   
    }  
      
    ostream &operator << (ostream &out, const rational &x){  
      out << x.nom << "/" << x.den;  
      return out;   
    }  
