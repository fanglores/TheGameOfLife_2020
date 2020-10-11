#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool get_next_state(int y, int x, vector<vector<bool>> &v)
{
  bool up,down,left,right;
  int neighbors = 0;
  
  if (x == 0) up = true;
  else up = false;
  if (x == v.size()) down = true;
  else down = false;
  if (y == 0) left = up
  else left = false;
  if (y == v.size()) right = true;
  else right = false;

  if(!up)
  {
    cnt += int(v[y - 1][x]);
    if (!left) cnt += int(v[y - 1][x - 1]);
    if (!right) cnt += int(v[y - 1][x + 1]);
  }
  if(!down)
  {
    cnt += int(v[y + 1][x]);
    if (!left) cnt += int(v[y + 1][x - 1]);
    if (!right) cnt += int(v[y + 1][x + 1]);
  }
  if (!right) cnt += int(v[y][x + 1]);
  if (!left) cnt += int(v[y][x - 1]);

  if(v[y][x]) 
  {
    if(cnt >= 2 && cnt <= 3) return true;    //alive cell keeps living
    else return false;                       //alive cell dies
  }
  else 
  {
    if(cnt == 3) return true;                 //dead cell resurrected
    else return false;                        //dead cell is dead
  }
  
}

int menu(int &N, int &G)
{
  system("cls");
  cout << "Enter size of the test field:\n>>";
  cin >> N;
  cout << "\nEnter number of the generations (-1 for infinity):\n>>";
  cin >> G;
}

int main()
{
  int N, G;
  vector<vector<bool>> cells(N, vector<bool>(N, false));
  
  

}
