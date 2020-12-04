#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "ResourceLayoutManager.h"

class ResourceManager
{
	int resource; // currency/resource to build tower
	int resourceCapacityLevel; // max amount of resource that possible to have, can be upgraded
    ResourceLayoutManager* resourceLayoutManager;

public:
	ResourceManager();

    // getters
	int getResource() const;
	int getResourceCapacity() const;
	int getResourceRequiredForUpgradeCapacity() const;

    //methods
    bool spendResource(int amount); // deduct resource if can afford and returns true, otherwise returns false
    void gainResource(int amount); // add resource, but can't go over max resource
    bool upgradeResourceCapacity(); // upgrade resource capacity if valid
	void setLayoutManager(ResourceLayoutManager* resourceLayoutManager);
    void manager_reset();
};

#endif // RESOURCEMANAGER_H
