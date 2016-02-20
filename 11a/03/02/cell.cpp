#include "cell.h"
#include <stdlib.h>


Cell::Cell()
{
	_walls = ALL;
}

void Cell::Drill(Direction dir)
{
	_walls = (Direction)(_walls ^ dir);
}

Cell* Cell::RandomDrill()
{
	std::vector<std::pair<Direction, Cell*> > unvisited = GetUnvisited();

	int random = rand() % unvisited.size();

	Direction dir = unvisited[random].first;
	Cell* selected = unvisited[random].second;

	Drill(dir);
	
	Direction reverse = (Direction)((dir <= RIGHT) ? dir << 2 : dir >> 2);
	selected->Drill(reverse);

	return selected;
}

bool Cell::HasUnvisitedNeighbours() const
{
	for (std::map<Direction,Cell*>::const_iterator it = _neighbours.begin(); it != _neighbours.end(); ++it)
	{
		if(!it->second->_visited)
			return true;
	}

	return false;
}

std::vector<std::pair<Direction, Cell*> > Cell::GetUnvisited()
{
	std::vector<std::pair<Direction, Cell*> > unvisited;

	for (std::map<Direction,Cell*>::iterator it = _neighbours.begin(); it != _neighbours.end(); ++it)
	{
		if(!it->second->_visited)
			unvisited.push_back(*it);
	}

	return unvisited;
}

void Cell::Visit()
{
	_visited = true;
}

void Cell::SetNeighbour(Direction dir, Cell* neighbour)
{
	_neighbours.insert(std::pair<Direction,Cell*>(dir,neighbour));
}