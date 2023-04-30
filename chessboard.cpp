#include <iostream>
#include <stdexcept>
#include <iomanip>
using namespace std; 

class ChessBoardArray {
 protected:
    class Row {
        public:
            // Constructor 
            Row(ChessBoardArray &a, int i) : chessBA(a), row(i) {}
            // Overloading operator []
            int & operator [] (int i) const { return chessBA.select(row, i); }
        private:
            // Chess board array 
            ChessBoardArray &chessBA; 
            int row; // row index 
    };

    class ConstRow { // Implementation is almost the same as above
     public:
        ConstRow(const ChessBoardArray &a, int i) : chessBA(a), row(i) {}
        int operator [] (int i) const { return chessBA.select(row, i); }
     private:
        // Changed to const 
        const ChessBoardArray &chessBA; 
        int row; 
    };
    
    // used for the public class:
    int *data; //data of the chessboard array
    int Size, Base; //size and base
 
 public:
    ChessBoardArray(unsigned size = 0, unsigned base = 0) {
        Size = size; 
        Base = base; 
        int k = (size * size /2) + (size % 2);
        data = new int[k];
        for (unsigned i =0; i <k; ++i) data[i] = 0; //initializing array
    }
    ChessBoardArray(const ChessBoardArray &a) {
        Size = a.Size; 
        Base = a.Base; 
        int k = (a.Size * a.Size /2) + (a.Size % 2); 
        data = new int[k]; 
        for (int i=0; i<k; ++i) data[i] = a.data[i]; 
    }
    ~ChessBoardArray() { delete [] data; } //destructor

    ChessBoardArray & operator = (const ChessBoardArray &a) {
        delete [] data; 
        Base = a.Base; 
        Size= a.Size; 
        // Same as expression above just simpler
        data = new int[(Size*Size+1)/2]; 
        for (unsigned i = 0; i <((Size*Size+1)/2); ++i) data[i] = a.data[i]; 
        return *this; 
    } 

    int & select(int i, int j) { return data[loc(i,j)]; }
    int select(int i, int j) const { return data[loc(i,j)]; }

    const Row operator [] (int i) { return Row(*this, i);} // return reference to the current object and its index
    const ConstRow operator [] (int i) const { return ConstRow(*this, i);}
    friend ostream & operator << (ostream &out, const ChessBoardArray &a) {
        for (int i =0; i <a.Size; ++i) {
            for (int j =0; j<a.Size; ++j) {
                out << setw(4);
                if ((i+j)%2 ==0)
                    out << a.select(i+a.Base, j+a.Base);
                else out << 0; 
            } 
            out << endl;
        }
        return out; 
    }
    protected:
        unsigned int loc(int i, int j) const throw(out_of_range) {
            int k = i-Base, l = j-Base; 
            if (k <0|| l <0 || k >= Size || l >= Size || (i+j)%2 == 1)
                throw out_of_range("invalid index"); 
            return (k*Size + l)/2; 
        }
 };
