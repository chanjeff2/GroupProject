#ifndef RESOURCELAYOUTMANAGER_H
#define RESOURCELAYOUTMANAGER_H

#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include "src/utility/GameValues.h"

class ResourceManager;

class ResourceLayoutManager
{
    ResourceManager *resourceManager;
public:
    QLabel* Resource;
    QLabel* ResourceCap;
    QLabel* ResourceNeededToUpg;
    QLabel* NotEnoughResources;
    QPushButton* ResourceUpgrade;

    ResourceLayoutManager(ResourceManager *resourceManager);

    //methods

    void updateResource(const int resource);

    void updateResourceCapacity(const int resourceCapacity);

    void updateResourceNeededToUpg(const int resourceNeededToUpg);

    void isResourceCapacityUpgradeAvailable(bool isAvailable);

    void indicateNotEnoughResource();
};

#endif // RESOURCELAYOUTMANAGER_H
