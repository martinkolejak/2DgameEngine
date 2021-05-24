#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H


#include "../Game.h"
#include "../EntityManeger.h"
#include "../Components/TransformComponent.h"


class ColliderComponent : public Component{
	public:
		std::string colliderTag;
		SDL_Rect collider;
		SDL_Rect sourceRectangle;
		SDL_Rect destinationRectangle;
		TransformComponent * transform;

		SDL_Renderer * renderer;

		ColliderComponent(std::string colliderTag, int x, int y, int width, int height, SDL_Renderer * renderer){
			this->colliderTag = colliderTag;
			this->collider = {x, y, width, height};
			this->renderer = renderer;	
		}
		
		void Initialize() override{
			if(owner->HasComponent<TransformComponent>()){	
				transform = owner->GetComponent<TransformComponent>();
				sourceRectangle = {0, 0, transform->width, transform->height};
				destinationRectangle = {collider.x, collider.y, collider.w, collider.h};	
			}	
		}

		void Render() override{
			SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
			SDL_RenderDrawRect( renderer, &collider);	
		}

		void Update(float deltaTime) override{
			collider.x = static_cast<int>(transform->position.x) - Game::camera.x;
			collider.y = static_cast<int>(transform->position.y) - Game::camera.y;
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;

			destinationRectangle.x = collider.x - Game::camera.x;
			destinationRectangle.y = collider.y - Game::camera.y;
		}

};









#endif 
