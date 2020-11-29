#include "ResourceLayoutManager.h"
#include "ResourceManager.h"

ResourceLayoutManager::ResourceLayoutManager(ResourceManager* resourceManager) :
    resourceManager(resourceManager) {}

void ResourceLayoutManager::updateResource(const int resource) {
    Resource->setText(QString::number(resource));
}

void ResourceLayoutManager::updateResourceCapacity(const int resourceCapacity) {
    ResourceCap->setText(QString::number(resourceCapacity));
}

void ResourceLayoutManager::updateResourceNeededToUpg(const int resourceNeededToUpg) {
    ResourceNeededToUpg->setText("Cost: " + QString::number(resourceNeededToUpg));
}

void ResourceLayoutManager::isResourceCapacityUpgradeAvailable(bool isAvailable) {
    ResourceUpgrade->setEnabled(isAvailable);
}
