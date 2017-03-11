#include <iostream> 
#include <vector>
#include <ctime>
#include <cstdlib>
#define SIDE 5
#define EXT_SIDE 9

using namespace std;

int success;
int fail;

struct sPos {
  int x;
  int y;
  friend ostream& operator<<(ostream& os, const sPos& pos);
};

ostream& operator<<(ostream& os, const sPos& pos) {
  os << pos.x-2 << ',' << pos.y-2;
  return os;
}

struct sMov {
  sPos src;
  sPos des;
  friend ostream& operator<<(ostream& os, const sMov& mov);
};

ostream& operator<<(ostream& os, const sMov& mov) {
  os << "(" << mov.src << "|" << mov.des.x << "," << mov.des.y << ")";
  return os;
}

//vector<sMov> gm;

int isSolved(int b[])
{
  int num = 0;
  for(int i=2; i<SIDE+2; i++)
  {
    for(int j=2; j<SIDE+2-(i-2); j++)
    {
      if(b[i*EXT_SIDE+j]==1) num++;
    }
  }
  if(num==1) 
    return 1;
  else 
    return 0;
}

void init_board(int b[])
{
  for(int i=0; i<EXT_SIDE; i++)
  {
    for(int j=0; j<EXT_SIDE; j++)
      b[i*EXT_SIDE+j]=0;

  }

  for(int i=2; i<SIDE+2; i++)
  {
    for(int j=2; j<SIDE+2-(i-2); j++)
    {
      if((i==2)&&(j==4)) continue;
      b[i*EXT_SIDE+j]=1;
      //else
      //continue;
    }
  }
}

void print_board(int b[])
{
  for(int i=2; i<SIDE+2; i++)
  {
    for(int j=2; j<SIDE+2-(i-2); j++)
    {
      cout << b[i*EXT_SIDE+j] << " ";
    }
    cout << endl;
  }

}

void possible_move(int b[], vector<sMov> & moves)
{
  sMov move;
  moves.clear();
  for(int i=2; i<SIDE+2; i++)
  {
    for(int j=2; j<SIDE+2-(i-2); j++)
    {
      if(b[i*EXT_SIDE+j]==0)
      {
        if((b[(i+1)*EXT_SIDE+j]==1) && (b[(i+2)*EXT_SIDE+j]==1)) {
          //register i+2,j to i,j
	  move.src.x = i+2;
	  move.src.y = j;
	  move.des.x = -1;
	  move.des.y = 0;
	  moves.push_back(move);
	}
        
        if((b[(i-1)*EXT_SIDE+j]==1) && (b[(i-2)*EXT_SIDE+j]==1)) {
          //register i-2,j to i,j
          move.src.x = i-2;
	  move.src.y = j;
	  move.des.x = +1;
	  move.des.y = 0;
	  moves.push_back(move);
	}
 

	if((b[(i+1)*EXT_SIDE+(j-1)]==1) && (b[(i+2)*EXT_SIDE+(j-2)]==1)) {
          //register i+2,j-2 to i,j
          move.src.x = i+2;
	  move.src.y = j-2;
	  move.des.x = -1;
	  move.des.y = +1;
	  moves.push_back(move);
	}

        if((b[(i-1)*EXT_SIDE+(j+1)]==1) && (b[(i-2)*EXT_SIDE+(j+2)]==1)) {
          //register i-2,j+2 to i,j
          move.src.x = i-2;
	  move.src.y = j+2;
	  move.des.x = +1;
	  move.des.y = -1;
	  moves.push_back(move);
	}

        if((b[i*EXT_SIDE+(j+1)]==1) && (b[i*EXT_SIDE+(j+2)]==1)) {
          //register i,j+2 to i,j
          move.src.x = i;
	  move.src.y = j+2;
	  move.des.x = 0;
	  move.des.y = -1;
	  moves.push_back(move);
	}

        if((b[i*EXT_SIDE+(j-1)]==1) && (b[i*EXT_SIDE+(j-2)]==1)) {
          //register i,j-2 to i,j
          move.src.x = i;
	  move.src.y = j-2;
	  move.des.x = 0;
	  move.des.y = +1;
	  moves.push_back(move);
	}
      }
    }
  }
}

void play(int nb[], int b[], sMov m) {
  for(int i=0; i<EXT_SIDE; i++) {
    for(int j=0; j<EXT_SIDE; j++) {
      nb[i*EXT_SIDE+j]=b[i*EXT_SIDE+j];
    }
  }
 
  nb[m.src.x*EXT_SIDE+m.src.y]=0;
  nb[(m.src.x+m.des.x)*EXT_SIDE+(m.src.y+m.des.y)]=0;
  nb[(m.src.x+2*m.des.x)*EXT_SIDE+(m.src.y+2*m.des.y)]=1;
}

void printgm(vector<sMov> & gm) {
  int newboard[EXT_SIDE*EXT_SIDE];
  init_board(newboard);
  print_board(newboard);
  for(int i=0;i<gm.size();++i){
    cout << "S" << i << " " << gm[i] << endl;
    play(newboard,newboard,gm[i]);
    print_board(newboard);
  }
}

int solve(int b[], vector<sMov> & gm) {
  if(isSolved(b)) {
    success++;
    //cout << "Success" << endl;
    //cout << "Succees #" << success << " size "<< gm.size() << endl;
    //printgm(gm);
    //gm.pop_back();
    return 1;
  }

  vector<sMov> moves;
  possible_move(b,moves);
  if(moves.size()==0) {
    fail++;
    //cout << "Failed" << endl;
    //gm.pop_back();
    return 0;
  }
  
  //for(int i=0; i<moves.size();i++)
  //{
    int i = rand() % moves.size();
    int newboard[EXT_SIDE*EXT_SIDE];
    //cout << moves[i] <<  endl;
    //gm.push_back(moves[i]);
    play(newboard,b,moves[i]);
    //print_board(newboard);

    //print_board(newboard);
    //cout << endl;
    return solve(newboard,gm);
  //}
  //if(gm.size()!=0) gm.pop_back();
  //return 0;
}

int main () 
{
  srand(time(NULL));
  success = 0;
  fail = 0;
  
  int good;
  for (int idx=0;idx<1000000;idx++){
    int board[EXT_SIDE*EXT_SIDE];
    init_board(board);
    //print_board(board);
    //cout << isSolved(board) << "pin";
    vector<sMov> GoodMoves;
    good = solve(board, GoodMoves);
    //cout << "Success = " << success << "; Fail = " << fail << endl;
  };
  cout << "Success = " << success << "; Fail = " << fail << " ";
  cout << "Probability = " << ((float) success/(success+fail));
  return 0;
  
}
