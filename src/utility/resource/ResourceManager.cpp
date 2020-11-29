#include "ResourceManager.h"
#include "ResourceLayoutManager.h"
#include "src/utility/GameValues.h"

ResourceManager::ResourceManager(): resource(STARTING_RESOURCE), resourceCapacityLevel(0) {
}

int ResourceManager::getResource() const {
	return resource;
}

int ResourceManager::getResourceCapacity() const {
	return RESOURCE_CAPACITY[resourceCapacityLevel];
}

int ResourceManager::getResourceRequiredForUpgradeCapacity() const {
	return getResourceCapacity() * RESOURCE_CAPACITY_RATIO_TO_UPGRADE;
}

/* enough resource to spend -> spend & true
		 * else -> do nothing & false
		 * usage: if (spendResource(amount)) [doYourStuff] */
bool ResourceManager::spendResource(int amount) {
	if (resource < amount)
		return false;
	else {
		resource -= amount;
        resourceLayoutManager->updateResource(getResource());
		return true;
	}
}

/* add resource, but can't go over max resource */
void ResourceManager::gainResource(int amount) {
	resource += amount;
	// Prevent going past resource cap
	if (resource > getResourceCapacity())
		resource = getResourceCapacity();

    resourceLayoutManager->updateResource(getResource());
	return;
}

/* upgrade resource capacity
		 * if already max level, do nothing
		 * (but we should have disabled the upgrade button)
		 * can still check to place safe */
bool ResourceManager::upgradeResourceCapacity() {
	// max level
    if (resourceCapacityLevel == NUM_OF_RESOURCE_CAPACITY) {
        return false; }

    if (spendResource(getResourceRequiredForUpgradeCapacity())) {
        ++resourceCapacityLevel; }

    if (resourceCapacityLevel == NUM_OF_RESOURCE_CAPACITY) {
        resourceLayoutManager->isResourceCapacityUpgradeAvailable(false);
        resourceLayoutManager->ResourceUpgrade->setText("Maxed!");
    }

    resourceLayoutManager->updateResourceCapacity(getResourceCapacity());
	return true;
}

void ResourceManager::setLayoutManager(ResourceLayoutManager* resourceLayoutManager) {
	this->resourceLayoutManager = resourceLayoutManager;
}
