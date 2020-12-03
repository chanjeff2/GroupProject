#include "src/utility/GameValues.h"
#include "ModManager.h"
#include "IEnemy.h"

// constructor
ModManager::ModManager(IEnemy *enemy): enemy(enemy) {}

// destructor
ModManager::~ModManager() {
	for (auto mod: modifiers) {
		delete mod.second;
	}
}

// nested class Modifier constructor
ModManager::Modifier::Modifier(float speedMod, float armorMod): speedMod(speedMod), armorMod(armorMod) {};

// nested class Modifier getters
float ModManager::Modifier::getSpeedMod() const {
	return this->speedMod;
}

float ModManager::Modifier::getArmorMod() const {
	return this->armorMod;
}

// methods
void ModManager::addModifier(AuraType mod) {
	switch(mod) {
		case AuraType::SlowAura: {
			if (enemy->getCanSlow()) {
				// only apply to who can be slowed
				qDebug() << "FocusManager: apply alow aura to" << *enemy;
				modifiers[mod] = new Modifier(SLOW_TOWER_SLOW_RATIO, DEFAULT_RATIO);
			}
			break;
		}
		case AuraType::ArmorPierceAura: {
			if (enemy->getCanPierceArmor()) {
				// only apply to whose armor can be pierced
				qDebug() << "FocusManager: apply armor pierce aura to" << *enemy;
				modifiers[mod] = new Modifier(DEFAULT_RATIO, ARMOR_PIERCE_RATIO);
			}
			break;
		}
		case AuraType::RageAura: {
			if (enemy->getCanEnrage()) {
				// only apply to who can be enraged
				qDebug() << "FocusManager: apply rage aura to" << *enemy;
				enemy->toggleRage(true);
				modifiers[mod] = new Modifier(RAGE_RATIO, RAGE_RATIO);
			}
			break;
		}
		default: {
			// Null Aura (place safe)
			break;
		}
	}
}

void ModManager::removeModifier(AuraType mod) {
	switch (mod) {
		case AuraType::SlowAura:
			if (enemy->getCanSlow()) {
				qDebug() << "FocusManager: remove slow aura from" << *enemy;
				delete modifiers[mod];
				modifiers.erase(mod);
			}
			break;
		case AuraType::ArmorPierceAura:
			if (enemy->getCanPierceArmor()) {
				qDebug() << "FocusManager: remove armor pierce aura from" << *enemy;
				delete modifiers[mod];
				modifiers.erase(mod);
			}
			break;
		case AuraType::RageAura:
			if (enemy->getCanEnrage()) {
				qDebug() << "FocusManager: remove rage aura from" << *enemy;
				enemy->toggleRage(false);
				delete modifiers[mod];
				modifiers.erase(mod);
			}
			break;
		default:
			// NULL Aura
			break;
	}
}

float ModManager::getActualValue(Attribute attribute) {
	switch (attribute) {
		case Attribute::Speed: {
			// get raw value
			float value = enemy->getRawSpeed();

			// apply modifiers
			for (const auto modifier: this->modifiers) {
				value *= modifier.second->getSpeedMod();
			}

			return value;
		}
		case Attribute::Armor: {
			// get raw value
			float value = enemy->getRawArmor();

			// apply modifiers
			for (const auto modifier: this->modifiers) {
				value *= modifier.second->getArmorMod();
			}

			return value;
		}
	}
}
