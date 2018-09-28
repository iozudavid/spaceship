#include "Hit.h"

Hit::Hit(Rect* bullet, Rect* individ) {
	this->bullet = bullet;
	this->individ = individ;
}

Hit::~Hit() {
	delete bullet;
	delete individ;
}

bool Hit::didHit() {
	std::tuple<int, int> bulletTLCorner = bullet->getTopLeftCorner();
	std::tuple<int, int> bulletBRCorner = bullet->getBottomRightCorner();

	std::tuple<int, int> individTLCorner = individ->getTopLeftCorner();
	std::tuple<int, int> individBRCorner = individ->getBottomRightCorner();

	if(std::get<0>(bulletTLCorner) > std::get<0>(individBRCorner) || std::get<0>(individTLCorner) > std::get<0>(bulletBRCorner))
		return false;

	if (std::get<1>(bulletTLCorner) < std::get<1>(individBRCorner) || std::get<1>(individTLCorner) < std::get<1>(bulletBRCorner))
		return false;

	return true;


}
