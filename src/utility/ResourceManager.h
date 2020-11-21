#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

class ResourceManager
{
	int resource; // currency/resource to build tower
	int resourceCapacityLevel; // max amount of resource that possible to have, can be upgraded
	ResourceLayoutManager resourceLayoutManager(this);

public:
	ResourceManager();

	int getResource() const;

	int getResourceCapacity() const;

	int getResourceRequiredForUpgradeCapacity() const;

	/* enough resource to spend -> spend & true
	 * else -> do nothing & false
	 * usage: if (spendResource(amount)) [doYourStuff] */
	bool spendResource(int amount);

	/* add resource, but can't go over max resource */
	void gainResource(int amount);

	/* upgrade resource capacity
	 * if already max level, do nothing
	 * (but we should have disabled the upgrade button)
	 * can still check to place safe */
	bool upgradeResourceCapacity();
};

#endif // RESOURCEMANAGER_H
