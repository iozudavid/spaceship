#include "EnemyDifficulty.h"

int EnemyDifficulty::getMoreDamage(int enemyArmyNo) {
	if (enemyArmyNo % 4 == 0)
		return 1;
	return 0;
}

int EnemyDifficulty::getMoreLives(int enemyArmyNo) {
	if (enemyArmyNo == 1)
		return 0;
	if ((enemyArmyNo-1) % 2 == 0)
		return 1;
	return 0;
}

float EnemyDifficulty::getMoreSpeedMovement(int enemyArmyNo) {
	return .01 * enemyArmyNo;
}

