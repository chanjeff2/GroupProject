#ifndef GAMEVALUES_H
#define GAMEVALUES_H

enum class EnemyType: int {
    NormalHW = 100, Essay, EncryptedHW,
    GroupProj, MathHW, COMPLab, PA, Desmond,
    PopQuiz, Midterm, MATHExam, Final, ELPA, FYP
};

enum class TowerType: int {
    Regular = 0, Arts, WolframAlpha, Hacker, Calc, Nerd, Ghostwriter, Chegg, None
};

enum class AuraType {
	SlowAura, ArmorPierceAura, RageAura, Null
};

enum class TargetSelectionType {
	Random, Priority, All, Null
};

// map
const int NUM_OF_ROW = 20; // y
const int NUM_OF_COL = 25; // x

const int START[] = {0, 0}; // x, y
const int END[] = {NUM_OF_COL, NUM_OF_ROW}; // x, y

// Tower Prices
const int TOWER_PRICES[8] = {10, 15, 30, 35, 40, 50, 75, 250};

// GPA (score)
const float MAX_GPA = 4.3;

// resources
const float REDEMPTION_RATIO = 0.5; // how much resource user get back after destroying tower
const int STARTING_RESOURCE = 20;
const int NUM_OF_RESOURCE_CAPACITY = 5;
const int RESOURCE_CAPACITY[NUM_OF_RESOURCE_CAPACITY] = {30, 60, 100, 200, 300}; // just random number
const float RESOURCE_CAPACITY_RATIO_TO_UPGRADE = 0.6;

// week (wave)
const int WEEK_COOLDOWN = 3; // (in sec) cooldown before user can manually proceed to next week
const int WEEK_COUNTDOWN = 10; // (in sec) countdown between week end and next week start

// modifications
const float SLOW_TOWER_SLOW_RATIO = 0.7; // speed * 0.7 (slow aura)
const float ARMOR_PIERCE_RATIO = 0.5; // Halves armor (armor piercing aura)
const float RAGE_RATIO = 2.0; // When rage, speed and armor * 2 (rage aura)
const float DEFAULT_RATIO = 1.0;

// attack damage
const float EFFECTIVE_ATTACK_RATIO = 2.0;

#endif // GAMEVALUES_H
