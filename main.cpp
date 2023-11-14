#include "Game.h"
#include <time.h>
#include "ScoreList.h"

int main()
{
	ScoreList score_list("highscore.txt");
	score_list.loadFile();
	Game game(&score_list);
	game.run();
	score_list.saveFile();
	return 0;
}