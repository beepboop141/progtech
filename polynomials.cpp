#include <iostream>
#include <math.h>
using namespace std; 
// linked list implementation 
// head with decreasing order of the exponent 

class Polynomial {
 protected:
    class Term {
      public:
            int exponent;
            int coefficient;
        Term *next;
        Term(int exp, int coeff, Term *n) {
            exponent = exp; 
            coefficient = coeff; 
            next = n; 
        }
        friend class Polynomial;
    };

    Term *head; 

 public:
    Polynomial() { head = nullptr;}
    Polynomial(const Polynomial &p) {
        Term *p_term = p.head; 
        while (p_term != nullptr) {
            addTerm(p_term->exponent, p_term->coefficient); 
            p_term = p_term->next;
        }
    }

    ~Polynomial() {
        while (head != nullptr) {
            Term* temp = head; 
            head = head->next; 
            delete temp; 
        }
    }

    Polynomial & operator = (const Polynomial &p) {
        if (this != &p)  {
            Term* p_term = p.head; 
            while(p_term != nullptr) {
                addTerm(p_term->exponent, p_term->coefficient);
                p_term = p_term->next; 
            }
        }
        return *this; 
    }

    void addTerm(int expon, int coeff) {
        if (coeff != 0) {
            if (head == nullptr || expon > head->exponent)
                head = new Term(expon, coeff, head);
            else if (expon == head->exponent) {
                head->coefficient += coeff; 
                if (head->coefficient == 0) {
                    Term *p = head; 
                    head = head->next; 
                    delete p; 
                }
            } else {
                Term *curr = head; 
                while (curr->next != nullptr && expon < curr->next->exponent)
                    curr = curr->next;
                if (curr->next != nullptr && expon == curr->next->exponent) {
                    curr->next->coefficient += coeff; 
                    if (curr->next->coefficient== 0) {
                        Term *p = curr->next; 
                        curr->next = curr->next->next; 
                        delete p; 
                    }
                } else {
                    curr->next = new Term(expon, coeff, curr->next);
                }

            }
        } 
    }

    double evaluate(double x) {
        double sum =0; 
        Term *p = head; 
        while(p != nullptr) {
            sum += p->coefficient * pow(x, p->exponent); 
            p = p->next; 
        }
        return sum; 
    }

    friend Polynomial operator+ (const Polynomial &p, const Polynomial &q) {
        Polynomial res; 
        Term *pp, *qq; 
        pp = p.head; 
        qq = q.head; 
        while (pp != nullptr && qq != nullptr) {
            if(pp->exponent == qq->exponent) {
                res.addTerm(pp->exponent, pp->coefficient + qq->coefficient);
                pp = pp->next; 
                qq= qq->next; 
            } else if (pp->exponent > qq->exponent) {
                res.addTerm(pp->exponent, pp->coefficient); 
                pp = pp->next; 
            } else {
                res.addTerm(qq->exponent, qq->coefficient);
                qq = qq->next; 
            }
        }
        while (pp != nullptr){
            res.addTerm(pp->exponent, pp->coefficient);
            pp = pp->next; 
        } while (qq != nullptr) {
            res.addTerm(qq->exponent, qq->coefficient); 
            qq = qq->next; 
        }
        return res; 
    }
    friend Polynomial operator* (const Polynomial &p, const Polynomial &q) {
        Polynomial res; 
        for (Term *pp = p.head; pp!= nullptr; pp = pp->next) {
            for (Term *qq = q.head; qq!= nullptr; qq = qq->next)
                res.addTerm(pp->exponent + qq->exponent, qq->coefficient * pp->coefficient ); 
        }
        return res; 
    }
    
    friend ostream & operator << (ostream &out, const Polynomial &p) {  
        if (p.head == nullptr) out << "0";  
        else {
            for(Term *pp = p.head; pp!= nullptr; pp = pp->next){  
                if (p.head->coefficient < 0)
                     out << "- ";
                else if (pp->coefficient < 0)
                    out << " - ";
                else if (pp != p.head) out << " + ";
                if (abs(pp->coefficient) == 1 && pp->exponent == 0)
                    out << '1'; 
                if (abs(pp->coefficient) != 1)
                    out << abs(pp->coefficient);
                if (pp->exponent >= 1)
                    out << "x";
                if (pp->exponent > 1)
                    out << "^" << pp->exponent; 
            }  
        }  
        return out;   
      
    }
};
