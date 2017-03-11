#include <iostream> 
#include <vector>
#include <cmath>

#define SIDE 5
#define EXT_SIDE 9

using namespace std;

int success;
int fail;
int hasilcmb[10];
double prob_suc;
double sum_ps;
int isPrint;
// data structure for position
struct sPos {
  int x;
  int y;
  friend ostream& operator<<(ostream& os, const sPos& pos);
};

ostream& operator<<(ostream& os, const sPos& pos) {
  os << pos.x-2 << ',' << pos.y-2;
  return os;
}

//data structure for a move (src = source, des = direction
struct sMov {
  sPos src;
  sPos des;
  friend ostream& operator<<(ostream& os, const sMov& mov);
};

ostream& operator<<(ostream& os, const sMov& mov) {
  os << "(" << mov.src << "|" << mov.des.x << "," << mov.des.y << ")";
  return os;
}

// isSolved return 1 if solved else 0
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

void init_board(sPos pos, int b[]) {
  for(int i=0; i<EXT_SIDE; i++)
  {
    for(int j=0; j<EXT_SIDE; j++)
      b[i*EXT_SIDE+j]=0;

  }

  for(int i=2; i<SIDE+2; i++)
  {
    for(int j=2; j<SIDE+2-(i-2); j++)
    {
      if((i==pos.x)&&(j==pos.y)) continue;
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

sPos play(int nb[], int b[], sMov m) {
  for(int i=0; i<EXT_SIDE; i++) {
    for(int j=0; j<EXT_SIDE; j++) {
      nb[i*EXT_SIDE+j]=b[i*EXT_SIDE+j];
    }
  }
 
  nb[m.src.x*EXT_SIDE+m.src.y]=0;
  nb[(m.src.x+m.des.x)*EXT_SIDE+(m.src.y+m.des.y)]=0;
  nb[(m.src.x+2*m.des.x)*EXT_SIDE+(m.src.y+2*m.des.y)]=1;
  sPos lastPos;
  lastPos.x = m.src.x+2*m.des.x;
  lastPos.y = m.src.y+2*m.des.y;
  return lastPos;
}

int printgm(sPos ipos, vector<sMov> & gm) {
  sPos prev,now;
  int combo;
  combo =0;
  int newboard[EXT_SIDE*EXT_SIDE];
  init_board(ipos,newboard);
  cout << "Succees #" << success << endl;
  print_board(newboard);
  int i=0;
  cout << "S" << i << " " << gm[i] << endl;
  prev = play(newboard,newboard,gm[i]);
  print_board(newboard);
  for(i=1;i<gm.size();++i){
    cout << "S" << i << " " << gm[i] << endl;
    now = play(newboard,newboard,gm[i]);
    if((prev.x==gm[i].src.x)&&(prev.y==gm[i].src.y)) combo++;
    prev.x = now.x;
    prev.y = now.y;
    print_board(newboard);
  }
  return combo;
}

void solve(sPos iPos, int b[], vector<sMov> & gm) {
  if(isSolved(b)) {
    success++;
    //cout << "Succees #" << success << " size "<< gm.size() << endl;
    if (isPrint) hasilcmb[printgm(iPos, gm)]++;
    gm.pop_back();
    sum_ps+=prob_suc;
    //cout << "Succees #" << success << " Ps "<<prob_suc << " sum " << sum_ps << endl;
    return;
  }

  vector<sMov> moves;
  possible_move(b,moves);
  if(moves.size()==0) {
    fail++;
    gm.pop_back();
    return;
  }
  
  for(int i=0; i<moves.size();i++)
  {
    if(gm.size()==0){
      prob_suc=(double) 1.0 * (double)1/(double)moves.size();
    }else{
     prob_suc = prob_suc * (double)1/(double)moves.size();
    }
    //cout << gm.size() << " " << moves.size() << " " << prob_suc << endl;
    int newboard[EXT_SIDE*EXT_SIDE];
    //cout << moves[i] <<  endl;
    gm.push_back(moves[i]);
    play(newboard,b,moves[i]);
    //print_board(newboard);
    //cout << endl;
    solve(iPos, newboard,gm);
    prob_suc = prob_suc * (double)moves.size();
  }
  if(gm.size()!=0) gm.pop_back();
  return;
}

void CreateVectorInitPos(vector<sPos> & vp) {
  sPos PosInit;
  PosInit.x = 2; 
  PosInit.y = 2;
  vp.push_back(PosInit); //#0
  PosInit.x = 2; 
  PosInit.y = 3;
  vp.push_back(PosInit); //#1
  PosInit.x = 3; 
  PosInit.y = 2;
  vp.push_back(PosInit); //#2
  PosInit.x = 2; 
  PosInit.y = 4;
  vp.push_back(PosInit); //#3
  PosInit.x = 3; 
  PosInit.y = 3;
  vp.push_back(PosInit); //#4
  PosInit.x = 4; 
  PosInit.y = 2;
  vp.push_back(PosInit); //#5
  PosInit.x = 2; 
  PosInit.y = 5;
  vp.push_back(PosInit); //#6
  PosInit.x = 3; 
  PosInit.y = 4;
  vp.push_back(PosInit); //#7
  PosInit.x = 4; 
  PosInit.y = 3;
  vp.push_back(PosInit); //#8
  PosInit.x = 5; 
  PosInit.y = 2;
  vp.push_back(PosInit); //#9
  
  PosInit.x = 2; 
  PosInit.y = 6;
  vp.push_back(PosInit); //#10
  PosInit.x = 3; 
  PosInit.y = 5;
  vp.push_back(PosInit); //#11
  PosInit.x = 4; 
  PosInit.y = 4;
  vp.push_back(PosInit); //#12
  PosInit.x = 5; 
  PosInit.y = 3;
  vp.push_back(PosInit); //#13
  PosInit.x = 6; 
  PosInit.y = 2;
  vp.push_back(PosInit); //#14

}
int main (int argc, char *argv[]) 
{
  isPrint = 0;
  int idxPos = 0;
  if ((argc>=2) &&(strcmp(argv[1],"-p")==0)) isPrint = 1;
  if ((argc>=2) &&(atoi(argv[1])!=0)) idxPos = atoi(argv[1]);
  if ((argc>2) &&(atoi(argv[2])!=0)) idxPos = atoi(argv[2]);
  if ((argc>2) &&(strcmp(argv[2],"-p")==0)) isPrint = 1;
  vector<sPos> PosInits;
  
  CreateVectorInitPos(PosInits);
  //for (int a=0;a<10;a++) hasilcmb[a] = 0;
  sum_ps=(double) 0.0;
  success = 0;
  fail = 0;
  
  int board[EXT_SIDE*EXT_SIDE];
  if((idxPos>0)&&(idxPos<=15)){
  //for(idxPos =0; idxPos<15; idxPos++){
   init_board(PosInits[idxPos-1], board);
   //print_board(board);
   //cout << isSolved(board) << "pin";
   vector<sMov> GoodMoves;
   solve(PosInits[idxPos], board, GoodMoves);
   //cout << "Success = " << success << "; Fail = " << fail << endl;
  //} 
  } else {
    for(idxPos =0; idxPos<15; idxPos++){
     init_board(PosInits[idxPos], board);
      //print_board(board);
      //cout << isSolved(board) << "pin";
      vector<sMov> GoodMoves;
      solve(PosInits[idxPos], board, GoodMoves);
      //cout << "Success = " << success << "; Fail = " << fail << endl;
      } 
    sum_ps = sum_ps/15;
  }
  cout << "Success = " << success << "; Fail = " << fail << " ";
  //cout << "Probability = " << ((float) success/(success+fail));
  cout << "Probability = " << sum_ps << " Is = " << (-log(sum_ps)/log(2));  
  //for (int a=0;a<10;a++) cout << hasilcmb[a] <<endl;
  
  return 0;
}
