#include <iostream>
#include <vector>

using namespace std;

struct sPos {
  int x;
  int y;
  friend ostream& operator<<(ostream& os, const sPos& pos);
};

ostream& operator<<(ostream& os, const sPos& pos) {
  os << pos.x << ',' << pos.y;
  return os;
}

struct sMov {
  sPos src;
  sPos des;
  friend ostream& operator<<(ostream& os, const sMov& mov);
};

ostream& operator<<(ostream& os, const sMov& mov) {
  os << "(" << mov.src << "|" << mov.des << ")";
  return os;
}

int main(){
  sPos pos1, pos2;
  sMov mov1;
  vector<sMov> vm;
  mov1.src.x=0;
  mov1.src.y=0;
  mov1.des.x=1;
  mov1.des.y=2;
  vm.push_back(mov1);
  pos1.x=10;
  pos1.y=10;
  pos2.x=11;
  pos2.y=12;
  mov1.src = pos1;
  mov1.des = pos2;
  vm.push_back(mov1);



  for(int i=0; i< vm.size(); ++i)
  {
    cout << vm[i] << ' ';
  }

}
