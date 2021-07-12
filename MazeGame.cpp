#include<iostream>
#include<fstream>
#include<vector>
#include <string>
#include<stack>
using namespace std;
struct position
{
	int row;
	int col;
};
int countsize()
{
	int count = 0;
	string c;
	ifstream fin("maze.txt");
	while(getline(fin,c))
	count++;
	return count;
}
void readmap(ifstream& fin, vector<vector<int>> &MAP)
{
	for (int istart = 0; istart < MAP.size(); istart++)
		for (int jstart = 0; jstart < MAP[0].size(); jstart++)
			fin >> MAP[istart][jstart];
	fin.close();
}
void show(vector<vector<int>> &MAP)
{
	for (int istart = 0; istart < MAP.size(); istart++)
	{
		for (int jstart = 0; jstart < MAP[0].size(); jstart++)
		{
			cout << MAP[istart][jstart] << " ";
		}
		cout << endl;
	}
}
void resizemap(vector<vector<int>>& MAP, int row, int col)
{
	MAP.resize(row);
	for (int istart = 0; istart < row; istart++)
		MAP[istart].resize(col);
}

void UpdatingAMap(vector<vector<int>>& MAP, stack<position> &Loc)
{
	position NewP;
	while (!Loc.empty())
	{
		NewP = Loc.top();
		Loc.pop();
		MAP[NewP.row][NewP.col] = '-';
	}
}
void printmap(vector<vector<int>>& MAP)
{

	for (int istart = 0; istart < MAP.size(); istart++)
	{
		for (int jstart = 0; jstart < MAP[0].size(); jstart++)
		{
			if (MAP[istart][jstart] == 45)
			{
				MAP[istart][jstart] = 1;
				cout<<MAP[istart][jstart]<<" ";
			}
			else
			{
				MAP[istart][jstart] = 0;
				cout << MAP[istart][jstart] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
	
}
bool Pathfind(vector<vector<int>>& MAP ,stack<position> & l)
{
	int istart = 0;
	int jstart = 0;
	cout << endl;
	position k;
	for (; istart < MAP.size(); )
	{
		for (; jstart < MAP.size(); )
		{
			if (istart >= MAP.size()-1 && jstart >= MAP[0].size()-1)
			{
				if (MAP[istart][jstart] == 1)
				{
					k.row = istart;
					k.col = jstart;
					l.push(k);
					return true;
				}
			}
			if (MAP[istart][jstart] == 1 )
			{
				
				k.row = istart;
				k.col = jstart;
				l.push(k);
				if (MAP[istart][jstart + 1] == 1)
					jstart++;
				else if (MAP[istart + 1][jstart] == 1)
					istart++;
				else
				{
					cout << "Path doesnot exists ";
					cout << endl;
					return false;
				}

			}
			else
			{
				cout << "Path doesnot exists ";
				cout << endl;
				return false;
			}
		}
	}
}
int main()
{
	ifstream fin("maze.txt");
	int row=countsize();
	vector<vector<int>> MAP;
	int col = row;
	resizemap(MAP, row, col);
	readmap(fin,MAP);
	cout << "MAP ";
	cout << endl;
	show(MAP);
	stack<position> l;
	if (!Pathfind(MAP, l))
		return 0;

	cout << endl;
	vector<vector<int>> MAPNEW = MAP;
	UpdatingAMap(MAPNEW, l);
	cout << "PATH ";
	cout << endl << endl<<"1 shows the path ";
	cout << endl;
	cout << endl;
	printmap(MAPNEW);
	return 0;
}