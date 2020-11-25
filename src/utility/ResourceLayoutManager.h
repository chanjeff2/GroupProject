#ifndef RESOURCELAYOUTMANAGER_H
#define RESOURCELAYOUTMANAGER_H

#include <QString>
#include <vector>
#include <QLabel>
#include <QPushButton>
#include "src/utility/GameValues.h"
#include "src/utility/ResourceManager.h"

class ResoruceManager;

class ResourceLayoutManager {
    ResourceManager *resourceManager;
public:
    QLabel* Resource;
    QLabel* ResourceCap;
    QPushButton* ResourceUpgrade;
    ResourceLayoutManager(ResourceManager *resourceManager);

    void updateResource(const int resource);

    void updateResourceCapacity(const int resourceCapacity);

    void isResourceCapacityUpgradeAvailable(bool isAvailable);
};

#endif // RESOURCELAYOUTMANAGER_H
