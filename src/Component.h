#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <string>
class Entity;

class Component{
	public:
		Entity* owner;;
		virtual ~Component(){};
		virtual void Initialize(){};
		virtual void Update(float deltaTime){};
		virtual void Render(){};
};

#endif

