#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <Windows.h>
using namespace std;

const bool DEBUG = true;    //set true if in dev

int N, G;
bool stagnation = false;
vector<vector<bool>> cells;
vector<vector<bool>> water;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//add genes mechanics
//add water generation
//how about of the cells movement?
//rules for each generator

const double mutation_chance = 0.4;
class cell
{
private:
    bool reduced_water_need, strong, swimmer;
public:
    cell() {};

};


//c - proceeding cells
//w - proceeding water
bool get_next_state(int y, int x, vector<vector<bool>> &v, char c = 'c')
{
    bool up, down, left, right;
    int neighbors = 0, water_available = 0;

    if (y == 0) up = true;
    else up = false;
    if (y == N - 1) down = true;
    else down = false;
    if (x == 0) left = true;
    else left = false;
    if (x == N - 1) right = true;
    else right = false;

    if (!up)
    {
        neighbors += int(v[y - 1][x]);
        if (!left) neighbors += int(v[y - 1][x - 1]);
        if (!right) neighbors += int(v[y - 1][x + 1]);
    }
    if (!down)
    {
        neighbors += int(v[y + 1][x]);
        if (!left) neighbors += int(v[y + 1][x - 1]);
        if (!right) neighbors += int(v[y + 1][x + 1]);
    }
    if (!right) neighbors += int(v[y][x + 1]);
    if (!left) neighbors += int(v[y][x - 1]);

    if (c == 'c')
    {
        if (!up)
        {
            water_available += int(water[y - 1][x]);
            if (!left) water_available += int(water[y - 1][x - 1]);
            if (!right) water_available += int(water[y - 1][x + 1]);
        }
        if (!down)
        {
            water_available += int(water[y + 1][x]);
            if (!left) water_available += int(water[y + 1][x - 1]);
            if (!right) water_available += int(water[y + 1][x + 1]);
        }
        if (!right) water_available += int(water[y][x + 1]);
        if (!left) water_available += int(water[y][x - 1]);
    }

    if (c == 'c')
    {
        if (v[y][x])
        {
            if ((neighbors == 2 && water_available >= 3) || (neighbors == 3 && water_available >= 4)) return true;  //alive cell keeps living
            else return false;  //alive cell dies
        }
        else
        {
            if (neighbors == 3 && water_available >= 4) return true;    //dead cell resurrected
            else return false;  //dead cell is dead
        }
    }
    else if(c == 'w')
    {
        if (neighbors <= 2) return false;  //water drains
        if (neighbors == 3 && v[y][x]) return true;    //water stays
        if (neighbors >= 4) return true;    //water appears
    }
}

void evolve(vector<vector<bool>>& v, char c = 'c')
{
    vector<vector<bool>> sub(N, vector<bool>(N));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sub[i][j] = get_next_state(i, j, v, c);

    if(c == 'c') stagnation = (v == sub);
    v = sub;
}

bool auto_init()
{
    int n, i = 0, x, y;
    srand(time(0));
    if (!DEBUG)
    {
        system("cls"); 
        cout << "*************************AUTO_INIT*************************\n\n";

        cout << "Enter number of cells to init (-1 for automatical generation):\n>>";
        cin >> n;

        if (n == -1) n = N * N / 3 + N % 3;
        cout << "\n$Initializing " << n << " cells...\n\n";
    }
    else n = N * N / 3 + N % 3;

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
    i = 0; n = N * N * 0.4; //0.4 was found as optimal coefficient
    //cout << "water is " << n; //DEBUG
    while (i < n)
    {
        x = rand() % N;
        y = rand() % N;

        if (water[y][x]) continue;
        else
        {
            water[y][x] = true;
            i++;
        }
    }

    for (int i = 0; i < 50; i++) evolve(water, 'w');
    cout << "Initialization successful!\n";
    return true;
}

bool manual_init()
{
    system("cls");
    int x, y;
    cout << "*************************MANUAL_INIT*************************\n\n";

    cout << "Enter line and column numbers (-1 -1 as end of input):\n>>";
    cin >> y >> x;

    while (x != -1)
    {
        cells[y][x] = true;
        cout << ">>";
        cin >> y >> x;
    }

    cout << "\n\nInitialization successful!\n";
    return true;
}

bool menu()
{
    system("cls");
    string ans;

    if (DEBUG) 
    { 
        N = 10; G = -1;
        cells.resize(N, vector<bool>(N, false));
        water.resize(N, vector<bool>(N, false)); 
        return auto_init(); 
    }

    cout << "Enter size of the test field:\n>>";
    cin >> N;

    cells.resize(N, vector<bool>(N, false));
    water.resize(N, vector<bool>(N, false));

    cout << "\nEnter number of the generations (-1 for infinity):\n>>";
    cin >> G;

    while (true)
    {
        cout << "\nSelect type of initialization:\n\trand: automatic initialization\n\tman: manual initialization\n\n>>";
        cin >> ans;
    
        if (ans == "rand") return auto_init();
        else if (ans == "man") return manual_init();
        else
        {
            cout << "Fatal error: Command was not recognized" << endl;
            system("pause");
            system("cls");
        }
    }

}

void print(vector<vector<bool>> &vect)
{
    for (int i = 0; i < N; i++) cout << " _";
    cout << endl;
    for (vector<bool> v : vect)
    {
        for (bool a : v)
            if (a) cout << "|*";
            else cout << "| ";
        cout << "|\n";
    }
}

void print_layers()
{
    /*for (int i = 0; i < N; i++) cout << " _ "; 
    cout << "\t\t"; 
    for (int i = 0; i < N; i++) cout << " _ "; 
    cout << endl;*/
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {   
            cout << "|";
            if (cells[j][i]) { SetConsoleTextAttribute(hConsole, 10); cout << "*"; SetConsoleTextAttribute(hConsole, 7); }
            else { SetConsoleTextAttribute(hConsole, 4); cout << "X"; SetConsoleTextAttribute(hConsole, 7); }
            cout << "|";
        }

        cout << "\t\t";

        for (int j = 0; j < N; j++)
        {
            cout << "|";
            if (water[j][i]) { SetConsoleTextAttribute(hConsole, 11); cout << "w"; SetConsoleTextAttribute(hConsole, 7); }
            else { SetConsoleTextAttribute(hConsole, 4); cout << "_"; SetConsoleTextAttribute(hConsole, 7); }
            cout << "|";
        }

        cout << endl;
    }
}

int main()
{

    if (menu())          //init
    {
        if(!DEBUG) system("pause");
        system("cls");

        cout << "0 generation state:\n";
        print_layers();
        
        int i = 0;
        bool infinitive = (G == -1);

        if (!infinitive)
        {
            while (i < G && !stagnation)
            {
                evolve(cells);
                i++;
            }
            cout << "\n\n" << N << "th generation state:\n";
            print_layers();
        }
        else 
            while (!stagnation)
            {
                system("pause");
                evolve(cells);
                i++;
                cout << "\n" << i << " generation state:\n";
                print_layers();
            }

        if (stagnation)
        {
            cout << "\n$Found end of the world`s evolution!";
            cout << "\n" << i << "th generation state:\n";
            print_layers();
        }

        return 1;
    }
    else
    {
        system("pause");
        return 0;
    }

}
