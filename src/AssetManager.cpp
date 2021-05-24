#include "./AssetManager.h"
#include <algorithm>
#include <string>

AssetManager::AssetManager(EntityManager* manager):  manager(manager){

}

void AssetManager::ClearData(){
	textures.clear();
	fonts.clear();
};

void AssetManager::AddTexture(std::string textureID, const char* filePath){
//LoadTexture returns pointer to the texture created from filepath 
	textures.emplace(textureID, TextureManager::LoadTexture(filePath));
};

void AssetManager::AddFont(std::string fontID, const char* filePath, int fontSize){
	fonts.emplace(fontID, FontManager::LoadFont(filePath, fontSize));	
}

SDL_Texture * AssetManager::GetTexture(std::string textureID){
	return textures[textureID];
};

TTF_Font* AssetManager::GetFont(std::string fontID){
	return fonts[fontID];
}

void GetName(){
	std::cout << "Cunt" << std::endl;
}





