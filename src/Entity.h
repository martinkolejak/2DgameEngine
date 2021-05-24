#ifndef ENTITY_H
#define ENTITY_H 

#include <string>
#include <typeinfo>
#include <utility>
#include "./Constants.h"
#include <map>
#include <vector>
#include "./Component.h"

class EntityManager;
class Component;

class Entity{
	private:
		EntityManager& manager;
		bool isActive;
		std::vector<Component*> components;
//map keeps track of the keys(types) and components of that type 	
//The typeid operator returns an lvalue of type const type_info& that represents the type of our value.
		std::map<const std::type_info*, Component *> componentTypeMap;
	public:
		std::string name;
		LayerType layer;
		Entity(EntityManager& manager, std::string name, LayerType layer);
		Entity(EntityManager& manager);
		void Update(float deltaTime);
		void Render();
		void Destroy();
		bool IsActive() const;		

		void ListAllComponents() const;
		
		template <typename T, typename... TArgs>
		T& AddComponent(TArgs&&... args){
			T* newComponent(new T(std::forward<TArgs>(args)...));
			newComponent->owner = this;
			components.emplace_back(newComponent);
//The typeid operator allows the type of an object to be determined at run time.
			componentTypeMap[&typeid(* newComponent)] = newComponent;	
			newComponent->Initialize();
			return *newComponent;			
		}		

		//Looks for the type key in map and returns the accurate component
		template <typename T>
		T* GetComponent(){
//The typeid operator allows the type of an object to be determined at run time.
//static_cast is an unary operator which forces one data type to be converted into another data type.		
//In this case static_cast downcasts Component pointer to base class into desired pointer to derived class although this operation is considered to be dangerous 
			return static_cast<T*>(componentTypeMap[&typeid(T)]);
		}

		template <typename T>
		bool HasComponent() const {
			return componentTypeMap.count(&typeid(T));	
		}

};

#endif

