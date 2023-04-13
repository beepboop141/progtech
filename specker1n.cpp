#include <stdexcept>  
#include <iostream>  
using namespace std;  
  
class Move {  
  public:  
    // Take sc coins from heap sh and put tc coins to heap th.   
    Move (int sh, int sc, int th, int tc) {  
      source_heap = sh;  
      source_coins =sc;  
      target_heap = th;  
      target_coins = tc;  
    }  
  
    int getSource() const {  
      return source_heap;  
    }  
    int getSourceCoins() const {  
      return source_coins;  
    }  
    int getTarget() const {  
      return target_heap;  
    }  
    int getTargetCoins() const{  
      return target_coins;  
    }  
  
    friend ostream & operator << (ostream &out, const Move &move) {  
      out <<"takes " << move.getSourceCoins() << " coins from heap "<< move.getSource()<<" and puts ";  
      // In the case there are no target coins  
      if (move.getTargetCoins() == 0)  
        out << "nothing";  
      // All other cases  
      else  
        out << move.getTargetCoins() << " coins to heap " << move.getTarget();  
      return out;  
    }  
  
  private:  
   int source_heap, source_coins, target_heap, target_coins;  
};  
  
class State {  
  public:  
   // Constructor  
    State(int h, const int c[], int n){  
      max_heaps= h;  
      coins = new int[max_heaps];  
      for (int i =0; i < max_heaps; ++i)  
        coins[i] = c[i];  
      players =n;  
      playing =0;  
    }  
  
    //Destructor  
    ~State(){  
      if (coins!= nullptr)  
        delete[] coins;  
    }  
  
    void next(const Move &move) throw(logic_error) {  
      // Invalid heap logic errors  
      if (move.getSource() < 0 || move.getSource() >= max_heaps || move.getTarget()<0 || move.getTarget() >= max_heaps)  
        throw logic_error("invalid heap");  
      // Not enough coins logic error  
      else if (move.getSourceCoins() > coins[move.getSource()])  
        throw logic_error("not enough coins");  
        
      // Wrong number of coins logic error  
      else if (move.getSourceCoins() <= 0 || move.getTargetCoins() < 0 || move.getSourceCoins() <= move.getTargetCoins())  
        throw logic_error("invalid number of coins");  
      else {  
    //Updating next move parameters  
        coins[move.getSource()] -= move.getSourceCoins();  
        coins[move.getTarget()] += move.getTargetCoins();  
        playing = (playing + 1) % players;  
      }  
    }  
  
    // Winning function- if the total coins are 0 player wins  
    bool winning() const{  
      int sum;  
      for (int i =0; i <max_heaps; ++i)  
        sum += coins[i];  
      if (sum != 0) return false;  
      else return true;  
    }  
  
    int getHeaps() const { return max_heaps; }  
      
    int getCoins(int h) const throw(logic_error){  
      if (h <0 || h >= max_heaps)  
        throw logic_error("invalid heap");  
      else return coins[h];  
    }  
  
    int getPlayers() const { return players; }  
    int getPlaying() const { return playing; }  
      
    friend ostream & operator << (ostream &out, const State &state) {  
      int i;  
      for (i =0; i<state.getHeaps()-1; ++i)  
        out <<  state.getCoins(i) << ", ";  
      out << state.getCoins(i);  
      out << " with " << state.getPlaying() << "/" << state.getPlayers() << " playing next";  
      return out;  
    }  
  private:  
    int max_heaps, players, playing;  
    int *coins;  
  
};  
