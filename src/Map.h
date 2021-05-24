#ifndef MAP_H
#define MAP_H

#include <string>

class Map{
	private:
		std::string textureID;
		int scale;
		int tileSize;
	public:
		Map(std::string textureid, int scale, int size);
		~Map();
		void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
		void AddTile(int sourceX, int sourceY, int x, int y);

};

















#endif
