#ifndef ENTITYMANGER_H
#define ENTITYMANGER_H

#include "./Entity.h"
#include "./Component.h"
#include <string>
#include <vector>


class EntityManager {
	private:
		std::vector<Entity *> entities;	
	public:	
		void ClearData();	
		void Update(float deltaTime);	
		void Render();
		bool HasNoEntities();
		Entity& AddEntitty(std::string entityName, LayerType layer);
		std::vector<Entity *> GetEntities() const;
		std::vector<Entity *> GetEntitiesByLayer(LayerType layer) const;
		unsigned int GetEntityCount();
		CollisionType CheckCollisions() const;
		void DestroyInactiveEntities();
		Entity* GetEntityByName(std::string entityName) const;
		Entity& AddEntity(std::string entityName, LayerType layer);	
		void ListAllEntities() const;
}; 
#endif
