#ifndef _WORD_INCLUDE
#define _WORD_INCLUDE

#include <vector>
#include "Sprite.h"


class Word
{

public:
	Word() {};
	Word(string word);
	~Word();
	void render();
	void setPosititon(glm::vec2 position);
	int getLenght();


private:
	glm::vec2 position;
	vector<Sprite*> letters;

	int lenght;
	int wordLenght;

};


#endif // _WORD_INCLUDE

