#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

ofstream ofs("TheGameOfLife_PPM.ppm", ios_base::out | ios_base::binary);

int N, G;
bool stagnation = false;
vector<vector<bool>> cells;


void write_file()
{
    ofs << "P6" << endl << N << ' ' << N << endl << "255" << endl;

    for (auto j = 0; j < N; ++j)
        for (auto i = 0; i < N; ++i)
            if(cells[j][i]) ofs << (char)(255) << (char)(255) << (char)(255);       // red, green, blue
            else ofs << (char)(0) << (char)(0) << (char)(0);
}

bool get_next_state(int y, int x)
{
    bool up, down, left, right;
    int neighbors = 0;

    if (y == 0) up = true;
    else up = false;
    if (y == N - 1) down = true;
    else down = false;
    if (x == 0) left = true;
    else left = false;
    if (x == N - 1) right = true;
    else right = false;
//qq?
    if (!up)
    {
        neighbors += int(cells[y - 1][x]);
        if (!left) neighbors += int(cells[y - 1][x - 1]);
        if (!right) neighbors += int(cells[y - 1][x + 1]);
    }
    if (!down)
    {
        neighbors += int(cells[y + 1][x]);
        if (!left) neighbors += int(cells[y + 1][x - 1]);
        if (!right) neighbors += int(cells[y + 1][x + 1]);
    }
    if (!right) neighbors += int(cells[y][x + 1]);
    if (!left) neighbors += int(cells[y][x - 1]);

    if (cells[y][x])
    {
        if (neighbors >= 2 && neighbors <= 3) return true;    //alive cell keeps living
        else return false;                       //alive cell dies
    }
    else
    {
        if (neighbors == 3) return true;                 //dead cell resurrected
        else return false;                        //dead cell is dead
    }

}

bool auto_init()
{
    int n, i = 0, x, y;
    system("cls");
    srand(time(0));
    cout << "*************************AUTO_INIT*************************\n\n";

    cout << "Enter number of cells to init (-1 for automatical generation):\n>>";
    cin >> n;

    if (n == -1) n = N * N / 3 + N % 3;
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

void evolve()
{
    vector<vector<bool>> sub(N, vector<bool>(N));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sub[i][j] = get_next_state(i, j);
 
    stagnation = (cells == sub);
    cells = sub;
}

bool menu()
{
    system("cls");
    string ans;
    cout << "Enter size of the test field:\n>>";
    cin >> N;

    cells.resize(N, vector<bool>(N, false));

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

void print()
{
    for (int i = 0; i < N; i++) cout << " _";
    cout << endl;
    for (vector<bool> v : cells)
    {
        for (bool a : v)
            if (a) cout << "|*";
            else cout << "| ";
        cout << "|\n";
    }
}


int main()
{

    if (menu())          //init
    {
        system("pause");
        system("cls");

        cout << "0 generation state:\n";
        print();
        
        write_file();
        return 0;

        int i = 0;
        bool infinitive = (G == -1);

        if (!infinitive)
        {
            while (i < G && !stagnation)
            {
                evolve();
                i++;
            }
            cout << "\n\n" << N << "th generation state:\n";
            print();
        }
        else 
            while (!stagnation)
            {
                system("pause");
                evolve();
                i++;
                cout << "\n" << i << " generation state:\n";
                print();
            }

        if (stagnation)
        {
            cout << "\n$Found end of the world`s evolution!";
            cout << "\n" << i << "th generation state:\n";
            print();
        }

        ofs.close();
        return 1;
    }
    else
    {
        system("pause");
        ofs.close();
        return 0;
    }

}

//PPM version