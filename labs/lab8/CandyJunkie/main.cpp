#include <iostream>
#include <fstream>
#include <list>
#include "sokoban_field.h"

int main ()
{
	#ifdef _WIN32
	system ("chcp 1251"); 
	#endif

	std::ifstream in ("input.txt", std::ifstream::binary);
	sokoban_field * root = new sokoban_field (in);
	std::list<sokoban_field *> queue;
	queue.push_back (root);
	while (queue.size () >= 0) {
		sokoban_field * temp = queue.front ();
		queue.pop_front ();

		if (temp->is_finish ()) {
			temp->print_from_root ();
			return 0;
		}

		for (int m = 0; m < MOVE_MAX; ++m) {
			sokoban_field * child = temp->go ((MOVE)m);
			if (child != NULL) {
				queue.push_back (child);
			}
		}
	}
	std::cout << "No solution.\n";
	return 0;
}