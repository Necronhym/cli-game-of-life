#include <iostream>
#include <vector>
#include <fstream>
class Cell
	{
		bool status;
		bool newStatus;
		public:
		Cell(bool status){ this->status = status; }
		void setNewStatus(bool status) { this->newStatus = status; }
		void update() { this->status = this->newStatus; }
		bool isAlive() { return this->status; }
		void setAlive(bool alive) { this->status = alive; }
		friend std::ostream& operator<<(std::ostream& Out, Cell& C)
			{
				C.status? Out<<"██" : Out<<"  ";
				return Out;
			}
	};
class Tissue
	{
		std::vector <std::vector<Cell>> Cells;
		int x, y;
		public:
		Tissue(int x, int y)
			{
				this->x=x;
				this->y=y;
				for(int i=0; i<y; i++)
					{
						std::vector<Cell> C;
						for(int j=0; j<x; j++)
							{
								C.push_back(Cell(0));
							}
						Cells.push_back(C);
					}
			}
		void update()
			{
				for(int j=0; j<y; j++)
					{
						for(int i=0; i<x; i++)
							{
								int numLiving=0;
								int up = i-1;
								up<0?up=y-1:up;
								int down = i+1;
								down>y-1 ? down=0 : down;
								int right=j-1;		
								right<0 ? right=x-1 : right;
								int left=j+1;
								left>x-1 ? left=0 :left;
								numLiving+=Cells.at(left).at(up).isAlive();
								numLiving+=Cells.at(j).at(up).isAlive();
								numLiving+=Cells.at(right).at(up).isAlive();
								numLiving+=Cells.at(left).at(i).isAlive();
								numLiving+=Cells.at(right).at(i).isAlive();
								numLiving+=Cells.at(left).at(down).isAlive();
								numLiving+=Cells.at(j).at(down).isAlive();
								numLiving+=Cells.at(right).at(down).isAlive();
							
								if(numLiving<2)
									{
										Cells.at(j).at(i).setNewStatus(0);
									}
								if(numLiving==2 || numLiving==3 && Cells.at(j).at(i).isAlive())
									{
										Cells.at(j).at(i).setNewStatus(Cells.at(j).at(i).isAlive());
									}
								if(numLiving>3)
									{
										Cells.at(j).at(i).setNewStatus(0);
									}
								if(numLiving==3 && !Cells.at(j).at(i).isAlive())
									{
										Cells.at(j).at(i).setNewStatus(1);
									}

							}
					}
				for(int i=0; i<y; i++)
					{
						for(int j=0; j<x; j++)
							{
								Cells[j][i].update();
							}
					}
			}
		void animateCell(int x, int y)
			{
				Cells.at(y).at(x).setAlive(true);
			}
		friend std::ostream& operator<<(std::ostream& Out, Tissue& T)
			{
				std::cout<<" ";
				for(int i=0; i<T.x*2; i++)
					{
						Out<<"─";
					}
				std::cout<<std::endl;
				for(auto a: T.Cells)
					{
						Out<<"|";
						for(auto b: a)
							{
								Out<<b;
							}
						Out<<"|"<<std::endl;
					}
				std::cout<<" ";
				for(int i=0; i<T.x*2; i++)
					{
						Out<<"─";
					}
			
				return Out;
			}
	};

int main()
	{
		std::ifstream in("input.txt");
		std::string str;
		in>>str;
		Tissue T(str.length(), str.length());
		int row=0;
		int col=0;
		do
			{
				for(auto a = str.begin(); a!=str.end(); a++)
					{
						if(*a == '1')
							{
								T.animateCell(row,col);
							}
						row++;		
					}
				std::cout<<std::endl;
				row=0;
				col++;
			}
		while(in>>str);
		while(true)
			{
				system("clear");
				std::cout<<T;
				T.update();
				std::cin.get();
			}
		return 0;
	}
