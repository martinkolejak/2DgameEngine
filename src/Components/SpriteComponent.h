#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H 

#include <SDL2/SDL.h>
#include <string>
#include "../Component.h"
#include "../TextureManager.h"
#include "./TransformComponent.h"
#include "../Animation.h"


class SpriteComponent: public Component {
	private:
		//in order to keep track of the transform comonent here;
		TransformComponent * transform;	
		SDL_Texture * texture;
//-----------------------------------------------------
		SDL_Rect sourceRectangle;
		SDL_Rect destinationRectangle;
//Variables needed for aniamations --------------------------
		bool isAnimated;
		bool isFixed;
		int numFrames;
		int animationSpeed;
		std::string currentAnimationName;
		unsigned int animationIndex = 0;
//Map that keeps track of animation class--------------------
		std::map<std::string, Animation> animations;
	public:
		SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

		SpriteComponent(std::string filePath) {
			isAnimated = false;
			isFixed = false;	
			SetTexture(filePath);	
		}
	
		 SpriteComponent(std::string assetTextureId, bool isFixed) {
			this->isAnimated = false;
			this->isFixed = isFixed;
			SetTexture(assetTextureId);
		}

		SpriteComponent(std::string id, int numFrames, int animationSpeed, bool hasDirection, bool isFixed){
			this->isAnimated = true;
			this->numFrames = numFrames;
			this->animationSpeed = animationSpeed;
			this->isFixed = isFixed;
			
			if(hasDirection){
				Animation downAnimation = Animation(0, numFrames, animationSpeed);	
				Animation rightAnimation = Animation(1, numFrames, animationSpeed);	
				Animation leftAnimation = Animation(2, numFrames, animationSpeed);	
				Animation upAnimation = Animation(3, numFrames, animationSpeed);	
			
				animations.emplace("DownAnimation", downAnimation);
				animations.emplace("RightAnimation", rightAnimation);
				animations.emplace("LeftAnimation", leftAnimation);
				animations.emplace("UpAnimation", upAnimation);	
			
				this->animationIndex = 0;
				this->currentAnimationName = "DownAnimation"; 
			}

			else{
				Animation singleAnimation = Animation(0, numFrames, animationSpeed);
				animations.emplace("SingleAnimation", singleAnimation);
				this->animationIndex = 0;
				this->currentAnimationName = "SingleAnimation";	
			}	
		
			Play(this->currentAnimationName);	
			SetTexture(id);	
		}

		void Play(std::string animationName){
			numFrames = animations[animationName].numFrames;
			animationIndex = animations[animationName].index;	
			animationSpeed = animations[animationName].animationSpeed;
			currentAnimationName = animationName;	
		}


//SetTexture initializes texture in this component to the texture stored in the assetmanager's map which has already created texture by TextureManager 
		void SetTexture(std::string assetTextureID){
			texture = Game::assetManager->GetTexture(assetTextureID);
		}

		void Initialize() override{
		//Used GetComponent in order to get the transform from the owner of this component 
		//The entity of this component is owner which is inside the parent component 
			transform = owner->GetComponent<TransformComponent>();
			sourceRectangle.x = 0.0;
			sourceRectangle.y = 0.0;
			sourceRectangle.w = transform->width;
			sourceRectangle.h = transform->height;
		}

		void Update(float deltaTime) override{
//source rectangle is looping by 32 units on the sprite thanks to the mod of number of frames which is either 1 or 0 
			if(isAnimated){
				sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);
			}
			sourceRectangle.y = animationIndex * transform->height;	

			destinationRectangle.x = static_cast<int>(transform->position.x) - (isFixed ? 0: Game::camera.x);
			destinationRectangle.y = static_cast<int>(transform->position.y) - (isFixed ? 0 : Game::camera.y);
			destinationRectangle.w = transform->width * transform->scale; 
			destinationRectangle.h = transform->height * transform->scale;	
		}

		void Render() override{
			TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);	
		}
};










#endif
