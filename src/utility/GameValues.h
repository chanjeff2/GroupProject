#ifndef GAMEVALUES_H
#define GAMEVALUES_H

enum class EnemyType: int {
	NormalHW = 100, Essay, EncryptedHW,
	GroupProj, MathHW, COMPLab, PA, Desmond,
	PopQuiz, Midterm, MATHExam, Final, ELPA, FYP
};

enum class TowerType: int {
	Regular = 0, Arts, WolframAlpha, Hacker, Calc, Nerd, Ghostwriter, Chegg
};

enum class AuraType {
	SlowAura, ArmorPierceAura, RageAura
};

// map
const int NUM_OF_ROW = 20; // y
const int NUM_OF_COL = 25; // x

const int START[] = {0, 0}; // x, y
const int END[] = {NUM_OF_COL, NUM_OF_ROW}; // x, y

// GPA (score)
const float MAX_GPA = 4.3;

// resources
const float REDEMPTION_RATIO = 0.5; // how much resource user get back after destroying tower

// week (wave)
const int WEEK_COOLDOWN = 3; // (in sec) cooldown before user can manually proceed to next week
const int WEEK_COUNTDOWN = 10; // (in sec) countdown between week end and next week start

// modifications
const float SLOW_TOWER_SLOW_RATIO = 0.7; // speed * 0.7 (slow aura)
const float ARMOR_PIERCE_RATIO = 0.5; // Halves armor (armor piercing aura)
const float RAGE_RATIO = 2.0; // When rage, speed and armor * 2 (rage aura)
const float DEFAULT_RATIO = 1.0;

#endif // GAMEVALUES_H
