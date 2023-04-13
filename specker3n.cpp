#include <iostream>  
#include <stdexcept>  
using namespace std;   
  
class Game {  
  public:  
    Game(int heaps, int players){  
      max_heaps = heaps;   
      max_players = players;   
      heap_arr = new int[max_heaps];  
      player_arr = new Player*[max_players];   
      heap_i = player_i = 0;   
    }  
    ~Game(){  
      delete[] heap_arr;   
      delete[] player_arr;   
    }  
  
    void addHeap(int coins) throw(logic_error){  
      if (heap_i == max_heaps)  
        throw logic_error("You've reached the limit of heaps uh oh :o");   
      else {  
        heap_arr[heap_i] = coins;   
        heap_i++;   
      }  
    }  
  
    void addPlayer(Player *player) throw (logic_error){  
      if (player_i == max_players)  
        throw logic_error("Suspicious behavior- don't think you can add more players");   
      else {  
        player_arr[player_i] = player;   
        player_i++;   
      }  
    }  
    void play(ostream &out) throw(logic_error) {   
      if(heap_i != max_heaps)  
        throw logic_error("Must add eaps or else...");   
      else if (player_i != max_players)  
        throw logic_error("More players are needed!! Or else the program will self destruct in 5, 4, 3..");   
      else {  
        State s(max_heaps, heap_arr, max_players);   
        while(!s.winning()) {  
          out << "State: "<< s << endl;  
          int current_i = s.getPlaying();   
          Player* current_p = player_arr[current_i];   
          Move player_move = current_p->play(s);   
          out << *current_p << " "<< player_move << endl;  
          s.next(player_move);   
        }  
        out << "State: " << s << endl;  
        int winner_i = (s.getPlaying() == 0) ? (max_players-1): (s.getPlaying() -1);   
        Player* winner = player_arr[winner_i];   
        out<< *winner << " wins" << endl;  
      }  
    }  
      
    int getPlayers() const { return max_players;}  
    const Player *getPlayer(int p) const throw(logic_error) {  
      if (p <0 || p > max_players)  
        throw logic_error("The player never existed and has gone into the void.");  
      else return player_arr[p];   
    }  
  
  private:  
    int max_heaps, max_players, heap_i, player_i;   
    int *heap_arr;   
    Player **player_arr;   
};  
