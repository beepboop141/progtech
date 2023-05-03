#include <iostream>
#include <math.h>
using namespace std; 
// linked list implementation 

class Polynomial {
 protected:
    class Term {
        // Creates linked list node for term and points to the next node
      public:
            int exponent;
            int coefficient;
        Term *next;
        // Initializing variables 
        Term(int exp, int coeff, Term *n) {
            exponent = exp; 
            coefficient = coeff; 
            next = n; 
        }
        friend class Polynomial;
    };

    Term *head; 

 public:
  // Initializes linked list/ constructor
    Polynomial() { head = nullptr;}
    // Starts linked list and adds terms 
    Polynomial(const Polynomial &p) {
        Term *p_term = p.head; 
        while (p_term != nullptr) {
            addTerm(p_term->exponent, p_term->coefficient); 
            p_term = p_term->next;
        }
    }
// Destructor 
    ~Polynomial() {
        while (head != nullptr) {
            Term* temp = head; 
            head = head->next; 
            delete temp; 
        }
    }
// Overloads = operator for the polynomials 
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
// Adds the new polynomial terms 
    void addTerm(int expon, int coeff) {
        if (coeff != 0) {
            if (head == nullptr || expon > head->exponent) 
            // adds to the front if the exponent is bigger than the head node 
                head = new Term(expon, coeff, head);
            else if (expon == head->exponent) {
                // if it's the same as the head node adding coefficient
                head->coefficient += coeff; 
                if (head->coefficient == 0) {
                    // deleting node if coefficient is 0 
                    Term *p = head; 
                    head = head->next; 
                    delete p; 
                }
            } else {
                Term *curr = head; 
                // transversing through the list to put the term in the right place
                while (curr->next != nullptr && expon < curr->next->exponent)
                    curr = curr->next;
                if (curr->next != nullptr && expon == curr->next->exponent) {
                    // same case as above- adding coefficient and deleting list node if 0 
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
        // evaluates the polynomial 
        double sum =0; 
        Term *p = head; 
        while(p != nullptr) {
            sum += p->coefficient * pow(x, p->exponent); 
            p = p->next; 
        }
        return sum; 
    }

    friend Polynomial operator+ (const Polynomial &p, const Polynomial &q) {
        // overloads operator + for addition, taking input two polynomials
        Polynomial res; 
        Term *pp, *qq; 
        pp = p.head; 
        qq = q.head; 
        while (pp != nullptr && qq != nullptr) {
            if(pp->exponent == qq->exponent) {
                // adding same terms 
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
        // multiplying two polynomials 
        Polynomial res; 
        for (Term *pp = p.head; pp!= nullptr; pp = pp->next) {
            for (Term *qq = q.head; qq!= nullptr; qq = qq->next)
                res.addTerm(pp->exponent + qq->exponent, qq->coefficient * pp->coefficient ); 
        }
        return res; 
    }
    
    friend ostream & operator << (ostream &out, const Polynomial &p) { 
        // prints polynomial 
        if (p.head == nullptr) out << "0";  
        else {
            for(Term *pp = p.head; pp!= nullptr; pp = pp->next){  
                // some attributes are different for the head variable 
                if (pp->coefficient < 0 && pp != p.head)
                    out << " - ";
                else if (pp->coefficient > 0 && pp != p.head) out << " + ";
                else if (p.head->coefficient < 0)
                    out << "- ";
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
