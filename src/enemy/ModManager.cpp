#include "ModManager.h"
#include "IEnemy.h"

// constructor
ModManager::ModManager(IEnemy *enemy): enemy(enemy) {}

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
			if (enemy->getCanSlow()) // only apply to who can be slowed
				modifiers[mod] = new Modifier(SLOW_TOWER_SLOW_RATIO, DEFAULT_RATIO);
			break;
		}
		case AuraType::ArmorPierceAura: {
			modifiers[mod] = new Modifier(DEFAULT_RATIO, ARMOR_PIERCE_RATIO);
			break;
		}
		case AuraType::RageAura: {
			modifiers[mod] = new Modifier(RAGE_RATIO, RAGE_RATIO);
			break;
		}
	}
}

void ModManager::removeModifier(AuraType mod) {
	delete modifiers[mod];
	modifiers.erase(mod);
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
