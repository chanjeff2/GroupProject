#ifndef GAMEVALUES_H
#define GAMEVALUES_H

#include <utility>
#include <string>

using namespace std;

typedef	pair<int /*col*/, int /*row*/> Coordinate;

enum class Element: int {
	Cell = 0, Indicator, Preview, Tower, Enemy, HP_bg, HP, ID_Tag, Selling
};

enum class EnemyType: int {
    NormalHW = 100, Essay, EncryptedHW,
    GroupProj, MathHW, COMPLab, PA, Desmond,
    PopQuiz, Midterm, MATHExam, Final, ELPA, FYP, _END_POINTER/*keep this as the last element*/
};

const string ENEMY_NAME[14] = {
	"NormalHW", "Essay", "EncryptedHW",
	"GroupProj", "MathHW", "COMPLab", "PA", "Desmond",
	"PopQuiz", "Midterm", "MATHExam", "Final", "ELPA", "FYP"
};

enum class TowerType: int {
    Regular = 0, Arts, WolframAlpha, Hacker, Calc, Nerd, Ghostwriter, Chegg, None
};

const string TOWER_NAME[8] = {
	"Regular", "Arts", "WolframAlpha", "Hacker", "Calc", "Nerd", "Ghostwriter", "Chegg"
};

enum class AuraType {
	SlowAura, ArmorPierceAura, RageAura, Null
};

enum class CellType {
    EMPTY, BLOCKED, SPAWN, END
};

enum class TargetSelectionType {
	Random, Priority, All, Null
};

// Global setting
extern float GAME_SPEED/* = 1.0*/; // higher -> game process faster (defined in mainwindow.cpp)

// map
const int NUM_OF_ROW = 20; // y
const int NUM_OF_COL = 25; // x

constexpr Coordinate START = make_pair(0, 0); // x, y
constexpr Coordinate END = make_pair(NUM_OF_COL - 1, NUM_OF_ROW - 1); // x, y
constexpr Coordinate nullCoordinate = make_pair(-1, -1);

// cell size for display
constexpr pair<int /*width*/, int /*height*/> CELL_SIZE = make_pair(40, 40);
// enemy hp bar
constexpr pair<int /*width*/, int /*height*/> HP_BAR_BG_SIZE = make_pair(CELL_SIZE.first * 3 / 4, 8);
const pair<int /*width*/, int /*height*/> HP_BAR_SIZE = make_pair(CELL_SIZE.first * 5 / 8, 6);
const string HP_BAR_BG_GREY = "#9f9f9f";
const string HP_BAR_RED = "#de4f4f";
const string HP_BAR_YELLOW = "#f0c861";
const string HP_BAR_GREEN = "#8de98d";

// Tower Prices
const int TOWER_PRICES[8] = {10, 15, 30, 35, 40, 50, 75, 250};
const int TOWER_RANGES[8] = {3, 3, 4, 3, 4, 2, 9, 5};

// Tower
const AuraType TOWER_AURAS[8] = {
	AuraType::Null, // Regular
	AuraType::Null, // Arts
	AuraType::Null, // WolframAlpha
	AuraType::SlowAura, // Hacker
	AuraType::ArmorPierceAura, // Calc
	AuraType::Null, // Nerd
	AuraType::RageAura, // Ghostwriter
	AuraType::Null // Chegg
};

const string TOWER_IMAGES[8] = {
    ":/res/res/towers_images/RegularStudent Grid",
    ":/res/res/towers_images/ArtsStudent Grid",
    ":/res/res/towers_images/Wolfram Grid",
    ":/res/res/towers_images/Hackerman Grid",
    ":/res/res/towers_images/Calculator Grid",
    ":/res/res/towers_images/Nerd Grid",
    ":/res/res/towers_images/Ghostwriter Grid",
    ":/res/res/towers_images/Chegg Grid"
};

// Enemy

// GPA (score)
const float MAX_GPA = 4.3;
const float DAMAGE_RATIO = 0.1; // worth * ratio = damage to gpa after reaching exit

// resources
const float REDEMPTION_RATIO = 0.5; // how much resource user get back after destroying tower
const int STARTING_RESOURCE = 50;
const int NUM_OF_RESOURCE_CAPACITY = 5;
const int RESOURCE_CAPACITY[NUM_OF_RESOURCE_CAPACITY] = {50, 75, 100, 200, 300}; // just random number
const float RESOURCE_CAPACITY_RATIO_TO_UPGRADE = 0.6;

// week (wave)
const int WEEK_COOLDOWN = 1; // (in sec) cooldown before user can manually proceed to next week after last enemy spawn
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
