#include "Score.h"

Score::Score(std::string name, unsigned long score) {

    this->name = name;
    this->score = score;
}

/**
 * à«çµª×èÍ
 *
 * @param string
 */
void Score::setName(std::string name) {

    this->name = name;
}

/**
 * ´Ö§ª×èÍ
 *
 * @return string
 */
std::string Score::getName() {

    return this->name;
}

/**
 * à«çµ¤Ðá¹¹
 *
 * @param int
 */
void Score::setScore(unsigned long score) {

    this->score = score;
}

/**
 * ´Ö§¤Ðá¹¹
 *
 * @return int
 */
unsigned long Score::getScore() {

    return this->score;
}
