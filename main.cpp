#include <iostream>

#include "map.hpp"

using namespace std;

int main()
{
	Map<int, int>mMap;

	mMap.Push(10, 104);
	mMap.Push(5, 102);
	mMap.Push(15, 108);
	mMap.Push(7, 103);
	mMap.Push(13, 106);
	mMap.Push(3, 101);
	mMap.Push(12, 105);
	mMap.Push(14, 107);
	mMap.Push(16, 109);

	std::cout << "map\n ";
	mMap.Show();

	for (Map<int, int>::iter it_Start = mMap.Begin(); it_Start != mMap.End(); ++it_Start)
	{
		std::cout << *it_Start << std::endl;
	}

	system("pause");
	return 0;
}
