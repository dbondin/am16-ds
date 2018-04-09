int sokoban_field::width = 0;
int sokoban_field::height = 0;
LEGEND ** sokoban_field::field = NULL;
bool sokoban_field::older_steps[10][10][10][10][10][10][10][10];
int sokoban_field::box_amount = 0;

sokoban_field::sokoban_field (std::ifstream & in)
{
	box = new int * [3]; // Максимум коробок 3. 4 пихал - не влезает.
	for (int i = 0; i < 3; ++i) {
		box[i] = new int [2];
		box[i][0] = 0;
		box[i][1] = 0;
	}
	parent = NULL;

	for (int p_x = 0; p_x < height; ++p_x) {
		for (int p_y = 0; p_y < width; ++p_y) {
			for (int b1_x = 0; b1_x < height; ++b1_x) {
				for (int b1_y = 0; b1_y < width; ++b1_y) {
					for (int b2_x = 0; b2_x < height; ++b2_x) {
						for (int b2_y = 0; b2_y < width; ++b2_y) {
							for (int b3_x = 0; b3_x < height; ++b3_x) {
								for (int b3_y = 0; b3_y < width; ++b3_y) {
									older_steps[p_x][p_y][b1_x][b1_y][b2_x][b2_y][b3_x][b3_y] = false; // без комментариев.
								}
							}
						}
					}
				}
			}
		}
	}

	in >> height;
	if ((height < 0) || (height > MAX_SIZE)) {
		throw /*rotten tomato*/ std::runtime_error ("Too tall file");
	}
	in >> width;
	if ((width < 0) || (width > MAX_SIZE)) {
		throw /*rotten tomato*/ std::runtime_error ("Too fat file");
	}

	char c;
	while (in.get(c)) {
		if (c == '\n') {
			break; // считываем конец строки.
		}
	}

	field = new LEGEND * [height];
	for (int i = 0; i < height; ++i) {
		field[i] = new LEGEND [width];
		for (int j = 0; j < width; ++j) {
			in.get(c);
			while ((c == '\n') || (c == '\r')) {
				in.get(c);
			}
			switch (c) {
				case '@':
					field[i][j] = EMPTY;
					player_x = j;
					player_y = i;
					break;
				case '#':
					field[i][j] = WALL;
					break;
				case '0':
					field[i][j] = EMPTY;					
					box[box_amount][0] = j;
					box[box_amount][1] = i;
					++box_amount;
					break;
				case ' ':
					field[i][j] = EMPTY;
					break;
				case '!':
					field[i][j] = PLACE;
					player_x = j;
					player_y = i;
					break;
				case '1':
					field[i][j] = PLACE;
					box[box_amount][0] = j;
					box[box_amount][1] = i;
					++box_amount;
					break;
				case '_':
					field[i][j] = PLACE;
					break;
				case '\n':
					break;
				case '\r':
					break;
				default:
					std::cout << "wrong legend symbol\n";
			}
		}
	}
	for (int i = box_amount; i < 3; ++i) {
		box[i][0] = 0;
		box[i][1] = 0;
	}
	older_steps[player_x][player_y][box[0][0]][box[0][1]][box[1][0]][box[1][1]][box[2][0]][box[2][1]] = true; // Делаем вид, что это одномерный массив.
}

sokoban_field::~sokoban_field ()
{
	if (box) {
		for (int i = 0; i < 3; ++i) {
			delete [] box[i];
		}
		delete [] box;
	}
}

bool sokoban_field::can_move (MOVE move) const
{
	int add_pos_x = 0;
	int add_pos_y = 0;

	switch (move) {
		case RIGHT:
			++add_pos_x;
			break;
		case UP:
			--add_pos_y;
			break;
		case LEFT:
			--add_pos_x;
			break;
		case DOWN:
			++add_pos_y;
			break;
		default:
			return false;
	}

	int new_pos_x = player_x + add_pos_x;
	int new_pos_y = player_y + add_pos_y;

	if ((new_pos_x < 0) || (new_pos_x >= width)) {
		return false;
	}
	else if ((new_pos_y < 0) || (new_pos_y >= height)) {
		return false;
	}
	else if (field[new_pos_y][new_pos_x] == WALL) {
		return false;
	}
	else {
		for (int i = 0; i < box_amount; ++i) {
			if ((box[i][0] == new_pos_x) && (box[i][1] == new_pos_y)) {
				if ((new_pos_y + add_pos_y < 0) || (new_pos_y + add_pos_y >= height)) {
					return false;
				}
				if ((new_pos_x + add_pos_x < 0) || (new_pos_x + add_pos_x >= width)) {
					return false;
				}
				if ((field[new_pos_y + add_pos_y][new_pos_x + add_pos_x] == EMPTY) || (field[new_pos_y + add_pos_y][new_pos_x + add_pos_x] == PLACE)) {
					return !check_older (new_pos_x, new_pos_y, i, move);
				}
				else {
					return false;
				}
			}
		}
		return !check_older (new_pos_x, new_pos_y, -1, move);
	}
}

bool sokoban_field::is_finish () const
{
	if (box_amount == 0) {
		return true;
	}
	for (int i = 0; i < box_amount; ++i) {
		if (field[box[i][1]][box[i][0]] != PLACE) {
			return false;
		}
	}
	return true;
}

bool sokoban_field::check_older (int newpos_x, int newpos_y, int boxnum, MOVE move) const
{
	int add_pos_x = 0;
	int add_pos_y = 0;

	switch (move) {
		case RIGHT:
			++add_pos_x;
			break;
		case UP:
			--add_pos_y;
			break;
		case LEFT:
			--add_pos_x;
			break;
		case DOWN:
			++add_pos_y;
			break;
		default:
			return NULL;
	}

	int newboxpos_x = newpos_x + add_pos_x;
	int newboxpos_y = newpos_y + add_pos_y;

	switch (boxnum) {
		case 0:
			return older_steps[player_x][player_y][newboxpos_x][newboxpos_y][box[1][0]][box[1][1]][box[2][0]][box[2][1]];
		case 1:
			return older_steps[player_x][player_y][box[0][0]][box[0][0]][newboxpos_x][newboxpos_y][box[2][0]][box[2][1]];
		case 2:
			return older_steps[player_x][player_y][box[0][0]][box[0][0]][box[1][0]][box[1][1]][newboxpos_x][newboxpos_y];
		default:
			return false;
	}
}

sokoban_field * sokoban_field::go (MOVE move)
{
	if (!can_move (move)) {
		return NULL;
	}


	int add_pos_x = 0;
	int add_pos_y = 0;

	switch (move) {
		case RIGHT:
			++add_pos_x;
			break;
		case UP:
			--add_pos_y;
			break;
		case LEFT:
			--add_pos_x;
			break;
		case DOWN:
			++add_pos_y;
			break;
		default:
			return NULL;
	}

	int new_pos_x = player_x + add_pos_x;
	int new_pos_y = player_y + add_pos_y;

	sokoban_field * new_sokoban_field = new sokoban_field ();
	new_sokoban_field->player_x = new_pos_x;
	new_sokoban_field->player_y = new_pos_y;

	for (int i = 0; i < box_amount; ++i) {
		if ((box[i][0] == new_pos_x) && (box[i][1] == new_pos_y)) {
			new_sokoban_field->box[i][0] = new_pos_x + add_pos_x;
			new_sokoban_field->box[i][1] = new_pos_y + add_pos_y;
		}
		else {
			new_sokoban_field->box[i][0] = box[i][0];
			new_sokoban_field->box[i][1] = box[i][1];
		}
	}

	childs[(int)move] = new_sokoban_field;
	new_sokoban_field->parent = this;
	return new_sokoban_field;
}

void sokoban_field::print_from_root ()
{
	if (parent != NULL) {
		parent->print_from_root ();
	}
	
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if ((player_x == j) && (player_y == i)) {
				if (field[i][j] == PLACE) {
					std::cout << '!';
				}
				else {
					std::cout << '@';
				}
			}
			else {
				bool box_here = false;
				for (int b = 0; b < box_amount; ++b) {
					if ((box[b][0] == j) && (box[b][1] == i)) {
						if (field[i][j] == PLACE) {
							std::cout << '1';
							box_here = true;
							break;
						}
						else {
							std::cout << '0';
							box_here = true;
							break;
						}
					}
				}
				if (!box_here) {
					switch (field[i][j]) {
						case WALL:
							std::cout << '#';
							break;
						case EMPTY:
							std::cout << ' ';
							break;
						case PLACE:
							std::cout << '_';
							break;
						default:
							std::cout << 'X';
					}
				}
			}
		}
		std::cout << std::endl;
	}

	for (int j = 0; j < width; ++j) {
		std::cout << "-";
	}
	std::cout << std::endl;
}
