#include <iostream>  
#include <stdexcept>  
#include <string>  
using namespace std;   
  
class Player{  
  public:  
    Player(const string &n) {  
      player_name = n;   
    }  
    virtual ~Player(){  
      player_name.clear();   
    }  
    virtual const string & getType() const =0;   
    virtual Move play(const State &s) =0;   
    friend ostream & operator << (ostream &out, const Player &player){  
      out << player.getType()<< " player "<< player.player_name;   
      return out;   
    }  
  
  protected:  
    string player_name;   
};  
  
class GreedyPlayer: public Player {   
  public:   
    GreedyPlayer(const string &n): Player(n) {  
      t = "Greedy";  
    }  
    ~GreedyPlayer(){  
      t.clear();   
    }  
    virtual const string & getType() const override{ return t;}  
    virtual Move play(const State &s) override {  
      int j = 0;   
      for (int i =0; i< s.getHeaps(); i++){  
        if(s.getCoins(i) > s.getCoins(j))  
          j = i;   
      }  
      return Move(j, s.getCoins(j), 0, 0);   
    }  
  private:  
    string t;   
};  
  
class SpartanPlayer: public Player {  
  public:   
    SpartanPlayer(const string &n): Player(n){  
      t = "Spartan";   
    }  
    ~SpartanPlayer(){  
      t.clear();   
    }  
    virtual const string & getType() const override { return t; }   
    virtual Move play (const State &s) override {  
      int j = 0;   
      for (int i =0; i< s.getHeaps(); i++){  
        if (s.getCoins(i) > s.getCoins(j))  
          j = i;   
      }  
      return Move (j, 1, 0, 0);   
    }  
  
  private:  
    string t;   
};  
  
class SneakyPlayer: public Player {  
  public:   
    SneakyPlayer(const string &n) : Player(n) {  
            t = "Sneaky";   
    }  
    ~SneakyPlayer(){  
      t.clear();   
    }  
    virtual const string & getType() const override {return t; }  
    virtual Move play(const State &s) override {  
      int least_coins = -1;   
      int least_coin_count = INT_MAX;   
      for (int i= 0; i<s.getHeaps(); i++){  
        if (s.getCoins(i) > 0 && s.getCoins(i) < least_coin_count){  
          least_coin_count = s.getCoins(i);  
          least_coins = i;   
        }  
      }  
      return Move (least_coins, least_coin_count, 0, 0);   
    }  
      
  private:  
    string t;   
};  
  
class RighteousPlayer: public Player {  
  public:  
    RighteousPlayer(const string &n): Player(n) {  
      t = "Righteous";   
    }  
    ~RighteousPlayer(){  
      t.clear();   
    }  
    virtual const string & getType() const override {return t; }  
    virtual Move play(const State &s) override {  
      int most_coins = 0, least_coins =0;   
      for (int i =1; i< s.getHeaps(); i++){  
        if (s.getCoins(i) > s.getCoins(most_coins)){  
          most_coins = i;   
        } else if (s.getCoins(i) < s.getCoins(least_coins)){  
          least_coins =i;   
        }  
      }  
      int coins = (s.getCoins(most_coins) + 1)/2;   
      return Move (most_coins, coins, least_coins, coins-1);   
    }  
  private:  
    string t;   
};  
