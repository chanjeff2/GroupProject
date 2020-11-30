#ifndef GAMEVALUES_H
#define GAMEVALUES_H

#include <utility>
using namespace std;

typedef	pair<int /*col*/, int /*row*/> Coordinate;

enum class Element: int {
	Cell = 0, Indicator, Tower, Enemy
};

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

// Global setting
const float GAME_SPEED = 5.0;

// map
const int NUM_OF_ROW = 20; // y
const int NUM_OF_COL = 25; // x

const Coordinate START = make_pair(0, 0); // x, y
const Coordinate END = make_pair(NUM_OF_COL - 1, NUM_OF_ROW - 1); // x, y

// cell size for display
const pair<int /*width*/, int /*height*/> CELL_SIZE = make_pair(40, 40);

// Tower Prices
const int TOWER_PRICES[8] = {10, 15, 30, 35, 40, 50, 75, 250};

// GPA (score)
const float MAX_GPA = 4.3;
const float DAMAGE_RATIO = 0.1; // worth * ratio = damage to gpa after reaching exit

// resources
const float REDEMPTION_RATIO = 0.5; // how much resource user get back after destroying tower
const int STARTING_RESOURCE = 2000;
const int NUM_OF_RESOURCE_CAPACITY = 5;
const int RESOURCE_CAPACITY[NUM_OF_RESOURCE_CAPACITY] = {3000, 60, 100, 200, 300}; // just random number
const float RESOURCE_CAPACITY_RATIO_TO_UPGRADE = 0.6;

// week (wave)
const int WEEK_COOLDOWN = 3; // (in sec) cooldown before user can manually proceed to next week
const int WEEK_COUNTDOWN = 10; // (in sec) countdown between week end and next week start
const int ENEMY_GENERATE_INTERVAL = 1;

// modifications
const float SLOW_TOWER_SLOW_RATIO = 0.7; // speed * 0.7 (slow aura)
const float ARMOR_PIERCE_RATIO = 0.5; // Halves armor (armor piercing aura)
const float RAGE_RATIO = 2.0; // When rage, speed and armor * 2 (rage aura)
const float DEFAULT_RATIO = 1.0;

// attack damage
const float EFFECTIVE_ATTACK_RATIO = 2.0;

#endif // GAMEVALUES_H
