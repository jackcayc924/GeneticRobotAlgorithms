//Jack Caycedo
//Genetic Robot Algorithms
//main.cpp
//5-12-2022

#include <iostream>
#include <unistd.h>
#include <algorithm>  

using namespace std;

struct Robot
{
	int startingPower = 5;
	int gene[16][5];
	int survivedTurns = 0;
	int currentLocationX = 0;
	int currentLocationY = 0;
	int CompareLocGene[0][4];
	int batteriesCollected = 0;
	
};

struct Robot robot[200];

struct Grid
{
	int grid[12][12];
}grid;

struct Misc
{
	int NUMBER_OF_ROBOTS = 200;
	int correctGenes = 0;
	void Move(Robot &robot);
	void PopulateGrid(Robot &robot);
	void BreedRobots();
	int energyHarvestedTotal = 0;
	float TotalFitnessScore = 0;
	float AverageFitnessScore = 0;
	int rounds = 0;
}misc;

bool customer_sorter(Robot &a, Robot &b);
bool fivePercentChance(float num);
void Intro();

void Misc::Move(Robot &robot)
{
	// Grabbing the current location of the robot while also checking if there is a wall near it

	for(int i = 0; i < 12; i++)
    {
      	for(int j = 0; j < 12; j++)
        {
			if(grid.grid[i][j] == 1)
			{
				robot.currentLocationX = i;
				robot.currentLocationY = j;
			}
        }
    }
	if(grid.grid[robot.currentLocationX - 1][robot.currentLocationY] == 4) // North
	{
		robot.CompareLocGene[0][0] = 1;
	}
	else
	{
		robot.CompareLocGene[0][0] = 0;
	}

	if(grid.grid[robot.currentLocationX + 1][robot.currentLocationY] == 4) // South
	{
		robot.CompareLocGene[0][1] = 1;
	}  
	else
	{
		robot.CompareLocGene[0][1] = 0;
	}

	if(grid.grid[robot.currentLocationX][robot.currentLocationY + 1] == 4) // East
	{
		robot.CompareLocGene[0][2] = 1;
	} 
	else
	{
		robot.CompareLocGene[0][2] = 0;
	}

	if(grid.grid[robot.currentLocationX][robot.currentLocationY - 1] == 4) // West
	{
		robot.CompareLocGene[0][3] = 1;
	}
	else
	{
		robot.CompareLocGene[0][3] = 0;
	}

	if(grid.grid[robot.currentLocationX - 1][robot.currentLocationY] == 8) // North
	{
		robot.CompareLocGene[0][0] = 2;
	}
	if(grid.grid[robot.currentLocationX + 1][robot.currentLocationY] == 8) // South
	{
		robot.CompareLocGene[0][1] = 2;
	}  
	if(grid.grid[robot.currentLocationX][robot.currentLocationY + 1] == 8) // East
	{
		robot.CompareLocGene[0][2] = 2;
	} 
	if(grid.grid[robot.currentLocationX][robot.currentLocationY - 1] == 8) // West
	{
		robot.CompareLocGene[0][3] = 2;
	}	
	// TIME TO COMPARE THE GENES!!!! 

	for(int i = 0; i < 16; i++)
    {
		for(int j = 0; j < 4; j++)
		{
			if(robot.gene[i][j] == robot.CompareLocGene[0][j])
			{
				misc.correctGenes += 1;
				if(misc.correctGenes == 4) // if we get a matching gene
				{
					if(robot.gene[i][4] == 1 && robot.CompareLocGene[0][0] != 1) //if we are NOT hitting a wall NORTH
					{
						grid.grid[robot.currentLocationX][robot.currentLocationY] = 0;
						if(grid.grid[robot.currentLocationX - 1][robot.currentLocationY] == 8) // check if battery on spot
						{
							grid.grid[robot.currentLocationX - 1][robot.currentLocationY] = 1;
							robot.currentLocationX -= 1;
							robot.survivedTurns += 1;
							robot.batteriesCollected += 1;
							goto map;
						}
						else
						{
							grid.grid[robot.currentLocationX - 1][robot.currentLocationY] = 1;
							robot.currentLocationX -= 1;
							robot.startingPower -= 1;
							robot.survivedTurns += 1;
							goto map;
						}
					}
					
					if(robot.gene[i][4] == 2 && robot.CompareLocGene[0][1] != 1) //if we are not hitting a wall SOUTH
					{
						grid.grid[robot.currentLocationX][robot.currentLocationY] = 0; //original spot is now free (0)
						if(grid.grid[robot.currentLocationX + 1][robot.currentLocationY] == 8) // check if battery on spot
						{
							grid.grid[robot.currentLocationX + 1][robot.currentLocationY] = 1;
							robot.currentLocationX += 1;
							robot.survivedTurns += 1;
							robot.batteriesCollected += 1;
							goto map;
						}
						else
						{
							grid.grid[robot.currentLocationX + 1][robot.currentLocationY] = 1;
							robot.currentLocationX += 1;
							robot.startingPower -= 1;
							robot.survivedTurns += 1;
							goto map;
						}
					}
					if(robot.gene[i][4] == 3 && robot.CompareLocGene[0][2] != 1) //if we are not hitting a wall EAST
					{
						grid.grid[robot.currentLocationX][robot.currentLocationY] = 0; //original spot is now free (0)
						if(grid.grid[robot.currentLocationX ][robot.currentLocationY + 1] == 8) // check if battery on spot
						{
							grid.grid[robot.currentLocationX ][robot.currentLocationY + 1] = 1;
							robot.currentLocationY += 1;
							robot.survivedTurns += 1;
							robot.batteriesCollected += 1;
							goto map;
						}
						else
						{
							grid.grid[robot.currentLocationX ][robot.currentLocationY + 1] = 1;
							robot.currentLocationY += 1;
							robot.startingPower -= 1;
							robot.survivedTurns += 1;
							goto map;
						}
					}
					if(robot.gene[i][4] == 4 && robot.CompareLocGene[0][3] != 1) //if we are not hitting a wall WEST
					{
						grid.grid[robot.currentLocationX][robot.currentLocationY] = 0; //original spot is now free (0)
						if(grid.grid[robot.currentLocationX ][robot.currentLocationY - 1] == 8) // check if battery on spot
						{
							grid.grid[robot.currentLocationX ][robot.currentLocationY - 1] = 1;
							robot.currentLocationY -= 1;
							robot.survivedTurns += 1;
							robot.batteriesCollected += 1;
							goto map;
						}
						else
						{
							grid.grid[robot.currentLocationX ][robot.currentLocationY - 1] = 1;
							robot.currentLocationY -= 1;
							robot.startingPower -= 1;
							robot.survivedTurns += 1;
							goto map;
						}
					}
					break;
				}
				else
				{
					if(i == 15)
					{
						goto nohit;
					}
				}
				if(j == 3 && misc.correctGenes != 4)
				{
					misc.correctGenes = 0;
				}
			}
		}
    }

nohit:
	if(robot.gene[15][4] == 1 && robot.CompareLocGene[0][0] != 1) //if we are NOT hitting a wall NORTH
	{
		grid.grid[robot.currentLocationX][robot.currentLocationY] = 0; //original spot is now free (0)
		if(grid.grid[robot.currentLocationX - 1 ][robot.currentLocationY] == 8) // check if battery on spot
		{
			grid.grid[robot.currentLocationX - 1 ][robot.currentLocationY] = 1;
			robot.currentLocationX -= 1;
            robot.survivedTurns += 1;
			robot.batteriesCollected += 1;
			goto map;
		}
		else
		{
			grid.grid[robot.currentLocationX - 1 ][robot.currentLocationY] = 1;
			robot.currentLocationX -= 1;
			robot.startingPower -= 1;
            robot.survivedTurns += 1;
			goto map;
		}
	}
	else if (robot.gene[15][4] == 1 && robot.CompareLocGene[0][0] == 1)
	{
		robot.startingPower -= 1;
		robot.survivedTurns += 1;
		goto map;
	}
	if(robot.gene[15][4] == 2 && robot.CompareLocGene[0][1] != 1) //if we are not hitting a wall SOUTH
	{
		grid.grid[robot.currentLocationX][robot.currentLocationY] = 0; //original spot is now free (0)
		if(grid.grid[robot.currentLocationX + 1][robot.currentLocationY] == 8) // check if battery on spot
		{
			grid.grid[robot.currentLocationX + 1][robot.currentLocationY] = 1;
			robot.currentLocationX += 1;
            robot.survivedTurns += 1;
			robot.batteriesCollected += 1;
			goto map;
		}
		else
		{	
			grid.grid[robot.currentLocationX + 1][robot.currentLocationY] = 1;
			robot.currentLocationX += 1;
			robot.startingPower -= 1;
            robot.survivedTurns += 1;
			goto map;
		}
	}
	else if (robot.gene[15][4] == 2 && robot.CompareLocGene[0][1] == 1)
	{
		robot.startingPower -= 1;
		robot.survivedTurns += 1;
		goto map;
	}

	if(robot.gene[15][4] == 3 && robot.CompareLocGene[0][2] != 1) //if we are not hitting a wall EAST
	{
		grid.grid[robot.currentLocationX][robot.currentLocationY] = 0; //original spot is now free (0)
		if(grid.grid[robot.currentLocationX ][robot.currentLocationY + 1] == 8) // check if battery on spot
		{
			grid.grid[robot.currentLocationX ][robot.currentLocationY + 1] = 1;
			robot.currentLocationY += 1;
            robot.survivedTurns += 1;
			robot.batteriesCollected += 1;
			goto map;
		}
		else // means its a zero and free spot
		{
			grid.grid[robot.currentLocationX ][robot.currentLocationY + 1] = 1;
			robot.currentLocationY += 1;
			robot.startingPower -= 1;
            robot.survivedTurns += 1;
			goto map;
		}

	}
	else if (robot.gene[15][4] == 3 && robot.CompareLocGene[0][2] == 1)
	{
		robot.startingPower -= 1;
		robot.survivedTurns += 1;
		goto map;
	}

	if(robot.gene[15][4] == 4 && robot.CompareLocGene[0][3] != 1) //if we are not hitting a wall WEST
	{
		grid.grid[robot.currentLocationX][robot.currentLocationY] = 0; //original spot is now free (0)
		if(grid.grid[robot.currentLocationX ][robot.currentLocationY - 1] == 8) // check if battery on spot
		{
			grid.grid[robot.currentLocationX ][robot.currentLocationY - 1] = 1;
			robot.currentLocationY -= 1;
            robot.survivedTurns += 1;
			robot.batteriesCollected += 1;
			goto map;
		}
		else
		{
			grid.grid[robot.currentLocationX ][robot.currentLocationY - 1] = 1;
			robot.currentLocationY -= 1;
			robot.startingPower -= 1;
            robot.survivedTurns += 1;
			goto map;
		}
	}
	else if (robot.gene[15][4] == 4 && robot.CompareLocGene[0][3] == 1)
	{
		robot.startingPower -= 1;
		robot.survivedTurns += 1;
		goto map;
	}
	
map:
	cout << ""; //do nothing, just to get out of the loops
}

void Misc::PopulateGrid(Robot &robot)
{
 	for(int i = 0; i < 12; i++)
    {
      	for(int j = 0; j < 12; j++)
        {
			grid.grid[i][j] = 0; // Populate our grid with zeros
        }
    }

	for(int i = 0; i < 12; i++)
    {
      	for(int j = 0; j < 12; j++)
        { // define the walls
			grid.grid[0][j] = 4;
			grid.grid[11][j] = 4;
			grid.grid[j][0] = 4;
			grid.grid[j][11] = 4;
        }
    }

    for (int i = 0; i < 40; i++)
    {   
		int Xrand = (rand() % 10) + 1;
		int Yrand = (rand() % 10) + 1;
        do
		{
			Xrand = (rand() % 10) + 1;
		 	Yrand = (rand() % 10) + 1;
        }
		while (grid.grid[Xrand][Yrand] != 0 || grid.grid[Xrand][Yrand] == 4);

        grid.grid[Xrand][Yrand] = 8; // Place our battery!
    }

	for (int i = 0; i < 100; i++)
    {    
		int Xrand = (rand() % 10) + 1;
		int Yrand = (rand() % 10) + 1;
        do
		{
			Xrand = (rand() % 10) + 1;
		 	Yrand = (rand() % 10) + 1;
        }
		while (grid.grid[Xrand][Yrand] != 8 || grid.grid[Xrand][Yrand] == 4);

        grid.grid[Xrand][Yrand] = 1; // place our robot!
		robot.currentLocationX = Yrand;
		robot.currentLocationY = Xrand;
		break;
    }

	if(misc.rounds == 0)
	{
		for(int i = 0; i < 16; i++) // determine robot genes
		{
			for(int j = 0; j < 5; j++)
			{
				if(j = 4)
				{
					int randomLastGene  = (rand() % 4) + 1;
					robot.gene[i][j] = randomLastGene;
				}
				else
				{
					int randomGene  = rand() % 3;
					robot.gene[i][j] = randomGene;
				}
			}
		}
	}
}

void Misc::BreedRobots()
{

	int highest = 0;
	int robotNumber = 0;
	for(int i = 0; i < misc.NUMBER_OF_ROBOTS; i++)
    {
		if(robot[i].survivedTurns > highest)
		{
			highest = robot[i].survivedTurns; 
			robotNumber = i; // I am unsure why the compiler thinks im not using this? when I am?
		}
    }

	//Calculate Fitness
	for(int i = 0; i < misc.NUMBER_OF_ROBOTS; i++)
    {
		misc.TotalFitnessScore += (float)robot[i].batteriesCollected;
    }
	//Get our average
	misc.AverageFitnessScore = misc.TotalFitnessScore / 200;
	   
	cout << endl;
	cout << "GENERATION #" << misc.rounds + 1 << endl;
	for(int i = 0; i < misc.NUMBER_OF_ROBOTS; i++)
    {
		misc.energyHarvestedTotal += robot[i].survivedTurns;
    }
	cout << "Total Energy Harvested: " << misc.energyHarvestedTotal << endl;
	cout << "Total Power Harvested: " << misc.TotalFitnessScore << endl;
	cout << "Average Fitness Score: " << misc.AverageFitnessScore << endl;
	cout << "Commencing Reproduction..." << endl;

 	int n = sizeof(robot) / sizeof(robot[0]);

	sort(robot, robot + n, &customer_sorter);

	// Begin to kill
	cout << "Killing..." << endl;
	for(int i = 0; i < 100; i++)
    {
		robot[i].survivedTurns = 0;
		robot[i].currentLocationX = 0;
		robot[i].currentLocationY = 0;
		for(int j = 0; j < 16; j++)
		{
			robot[i].gene[j][0] = 0;
			robot[i].gene[j][1] = 0;
			robot[i].gene[j][2] = 0;
			robot[i].gene[j][3] = 0;
			robot[i].gene[j][4] = 0;
		}
    }
	
	cout << "Killed!" << endl;
	int parents = 201;
	cout << "Breeding..." << endl;
	//Breed top 2 parents and produce 2 children
	for(int i = 0; i < 100;)
    {
		parents -= 2;
		for(int h = parents; h > 0; h - 2)
		{
			for(int j = 0; j < 8; j++)
			{
				for(int p = 0; p < 5; p++)
				{
					robot[i].gene[j][p] = robot[h].gene[j][p];
					robot[i + 1].gene[j][p] = robot[h].gene[15-j][p];
				}
				if((rand() % 100 < 5))
				{		
					robot[i].gene[j][rand() % 4] = rand() % 3;
				}
			}
			for(int j = 8; j < 16; j++)
			{
				for(int p = 0; p < 5; p++)
				{
					robot[i].gene[j][p] = robot[h].gene[j][p];
					robot[i + 1].gene[j][p] = robot[h].gene[15-j][p];
				}
				if((rand() % 100 < 5))
				{		
					robot[i].gene[j][rand() % 4] = rand() % 3;
				}
			}
			break;
		}
		i += 2;
    }

	cout << "Breeded!" << endl;

	misc.AverageFitnessScore = 0;
	misc.TotalFitnessScore = 0;
	misc.energyHarvestedTotal = 0;
}

int main()
{
	Intro();
	srand(time(NULL));
	int counter = 0;
	while(counter < 1000)
	{
		for(int i = 0; i < misc.NUMBER_OF_ROBOTS; i++)
		{
			for(int j = 0; j < misc.NUMBER_OF_ROBOTS; j++)
			{
				robot[j].startingPower = 5;
			}
			misc.PopulateGrid(robot[i]);
			while(robot[i].startingPower > 0)
			{
				misc.Move(robot[i]);
			}
		}
		misc.BreedRobots();	
		misc.rounds += 1;
		counter += 1;
	}
}

bool customer_sorter(Robot &a, Robot &b) {
	if (a.survivedTurns != b.survivedTurns)
	{
		return a.survivedTurns < b.survivedTurns;
	}
	return false;
}

void Intro()
{
	cout << "Welcome to the Genetic Robot Algorithm! By Jack Caycedo" << endl;
	cout << "This program will run simulation of robots that look for energy" << endl;
	cout << "and will breed and evolve over time getting better and better as the generations go on" << endl;
	cout << "It will run through 1000 generations of 200 robots each, killing off and" << endl;
	cout << "rebreeding 50 percent of the population with the parents" << endl;
	cout << endl;
	cout << "It will be fun  to watch them improve! Press [ENTER] whenever you are ready." << endl;
	getchar();
}


