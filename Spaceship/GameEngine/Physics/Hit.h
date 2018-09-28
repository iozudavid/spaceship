#pragma once
#include "../utils/Rect.h"
class Hit {
public:
	Hit(Rect *bullet, Rect *individ);
	~Hit();
	bool didHit();

private:
	Rect *bullet;
	Rect *individ;
};