#ifndef MODMANAGER_H
#define MODMANAGER_H

#include <map>
using namespace std;

#include "src/utility/GameValues.h"
// forward declaration
class IEnemy;

class ModManager {
public:
	// constructor
	ModManager(IEnemy *enemy);
	// destructor
	~ModManager() {}

	enum class Attribute {
		Speed, Armor
	};

	// methods
	virtual void addModifier(AuraType mod);

	virtual void removeModifier(AuraType mod);

	virtual float getActualValue(Attribute attribute);
private:
	class Modifier final {
		const float speedMod; // the order of member data should be the same as in enum class Attribute
		const float armorMod;
	public:
		Modifier(float speedMod, float armorMod);
		float getSpeedMod() const;
		float getArmorMod() const;
	};

	IEnemy *enemy;
	map<AuraType, Modifier*> modifiers; // key: Mods, value: {speed mod, armor mod}
};

#endif // MODMANAGER_H
