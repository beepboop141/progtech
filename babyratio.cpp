    #ifndef CONTEST  
    #include "babyratio.hpp"  
    #endif  
    #include <iostream>   
      
    using namespace std;  
      
    rational::rational (int n, int d){  
      nom = n/ gcd(n, d);   
      den = d/ gcd(n, d);   
      
      if (nom == 0)   
        den = 1;   
      else if (den < 0) {  
        nom *= -1;  
        den *= -1;   
      }  
      return;   
    }  
      
    rational rational::add(rational r) {  
      rational res(nom*r.den + r.nom *den, den *r.den);  
      return res;   
    }  
      
    rational rational::sub (rational r){  
      rational res(nom*r.den- r.nom*den, den*r.den);   
      return res;   
    }  
      
    rational rational::div (rational r){  
      rational res(nom*r.den, den*r.nom);   
      return res;   
    }  
      
    rational rational::mul(rational r){  
      rational res(nom*r.nom, den * r.den);  
      return res;   
    }  
      
    int rational::gcd(int x, int y){  
      x = abs(x);   
      y = abs(y);   
      while (x> 0 && y > 0){  
        if (x>y)  
          x %= y;   
        else   
          y %= x;   
      }  
      return x +y;   
    }  
      
    void rational::print(){  
      cout << nom << "/" << den;   
      return;   
    }  
