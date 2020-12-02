#include "ResourceManager.h"
#include "ResourceLayoutManager.h"
#include "src/utility/GameValues.h"

#include <QDebug>

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
	if (resource < amount) {
		qDebug() << "ResourceManager: not enough resource";
		return false;
	} else {
		resource -= amount;
		qDebug() << "ResourceManager: spend resource:" << amount << "; new resource amount: " << resource;
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

	qDebug() << "ResourceManager: gain resource:" << amount << "; new resource amount: " << resource;
    resourceLayoutManager->updateResource(getResource());
	return;
}

/* upgrade resource capacity
		 * if already max level, do nothing
		 * (but we should have disabled the upgrade button)
		 * can still check to place safe */
bool ResourceManager::upgradeResourceCapacity() {
	// max level
    if (resourceCapacityLevel == NUM_OF_RESOURCE_CAPACITY - 1) {
		qDebug() << "ResourceManager: failed upgrade capacity, max level";
		return false;
	}

    if (spendResource(getResourceRequiredForUpgradeCapacity())) {
		++resourceCapacityLevel;
		qDebug() << "ResourceManager: upgrade capacity to :" << getResourceCapacity();
	}

    if (resourceCapacityLevel == NUM_OF_RESOURCE_CAPACITY - 1) {
        resourceLayoutManager->isResourceCapacityUpgradeAvailable(false);
        resourceLayoutManager->ResourceUpgrade->setText("Maxed!");
    }

    resourceLayoutManager->updateResourceCapacity(getResourceCapacity());
    resourceLayoutManager->updateResourceNeededToUpg(getResourceRequiredForUpgradeCapacity());
	return true;
}

void ResourceManager::setLayoutManager(ResourceLayoutManager* resourceLayoutManager) {
	this->resourceLayoutManager = resourceLayoutManager;
}

void ResourceManager::manager_reset() {
    resource = STARTING_RESOURCE;
    resourceCapacityLevel = 0;
    resourceLayoutManager->updateResource(getResource());
    resourceLayoutManager->updateResourceCapacity(getResourceCapacity());
    resourceLayoutManager->updateResourceNeededToUpg(getResourceRequiredForUpgradeCapacity());
}
