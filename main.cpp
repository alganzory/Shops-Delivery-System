#include "SH_List.h"
#include "SO_List.h"

int main ()
{
	SO_List::filePath = "shlist.txt";
	SO_List::readFromFile();
	SH_List::setList();
	std::cin.get();
}
