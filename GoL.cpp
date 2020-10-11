#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

bool get_next_state(int y, int x)
{
  bool up,down,left,right;
  int neighbors = 0;
  
  if (x == 0) up = true;
  else up = false;
  if (x == N - 1) down = true;
  else down = false;
  if (y == 0) left = up
  else left = false;
  if (y == N - 1) right = true;
  else right = false;

  if(!up)
  {
    cnt += int(cells[y - 1][x]);
    if (!left) cnt += int(cells[y - 1][x - 1]);
    if (!right) cnt += int(cells[y - 1][x + 1]);
  }
  if(!down)
  {
    cnt += int(cells[y + 1][x]);
    if (!left) cnt += int(cells[y + 1][x - 1]);
    if (!right) cnt += int(cells[y + 1][x + 1]);
  }
  if (!right) cnt += int(cells[y][x + 1]);
  if (!left) cnt += int(cells[y][x - 1]);

  if(cells[y][x]) 
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

bool auto_init()
{
  int n, i, x, y;
  system("cls");
  srand(time(0));
  cout << "********************AUTO_INIT"********************"\n\n;
  
  cout << "Enter number of cells to init (-1 for automatical generation):\n>>";
  cin >> n;
  
  if (n == -1) n = N / 3 + N % 3;
  cout << "\n$Initializing " << n << " cells...\n\n";
  
  while (i < n)
  {
    x = rand() % N;
    y = rand() % N;
    
    if (cells[y][x]) continue;
    else
    {
      cells[y][x] = true;
      i++;
    }
  }
  
  cout << "Initialization successful!\n";
  return true;
}

bool manual_init()
{
  system("cls");
  int x, y;
  cout << "********************MANUAL_INIT"********************"\n\n;
    
  cout << "Enter line and column numbers (-1 -1 as end of input):\n>>";
  cin >> y >> x;
  
  while(x != -1)
  {
    cells[y][x] = true;
    cout << "\n>>";
    cin >> y >> x;
  }
  
  cout << "\n\nInitialization successful!\n";
  return true;
}

bool menu()
{
  system("cls");
  string ans;
  cout << "Enter size of the test field:\n>>";
  cin >> N;
  cout << "\nEnter number of the generations (-1 for infinity):\n>>";
  cin >> G;
  cout << "\nSelect type of initialization:\n\trand: automatic initialization\n\tman: manual initialization\n\n>>";
  cin >> ans;
  
  if(ans == "rand") return auto_init();
  else if(ans == "man") return manual_init();
  else 
  { 
    cout << "Fatal error: Command was not recognized" << endl; 
    return false;
  }
}

void print()
{
  for (vector<bool> v : cells) 
    {
      for (bool a : v)
        if(a) cout << "|*";
        else cout << "| ";
      cout << "|\n";
    }
}


int N, G;
vector<vector<bool>> cells(N, vector<bool>(N, false));

int main()
{
  
  if(menu())          //init
  {
    system("pause");
    system("cls");
    
    cout << "0 generation state:\n\n";
    print();

    for(int i = 0; i < G; i++) evolve();

    cout << "\n\n" << N << " generation state:\n\n";
    print();
    return 1;
  }
  else 
  { 
    system("pause"); 
    return 0; 
  }
  
}
