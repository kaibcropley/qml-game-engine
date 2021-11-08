#include "gridgamemanager.h"

GridGameManager::GridGameManager() :
    m_gridMatrix(nullptr),
    m_entityManager(nullptr)
{

}

void GridGameManager::initializeGridGame(int rows, int columns)
{
    m_gridMatrix = new GridMatrix(this, rows, columns);
    m_entityManager = new EntityManager(this, m_gridMatrix);
}
