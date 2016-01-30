#include "tileLoader.h"
#include "loadTexture.h"
#include "tile.h"
#include "game.h"

tileLoader::tileLoader() {}


//// detects tiles around itself and attempts to merge them into one larger tile TODO
//std::vector<boost::shared_ptr<tile>> mergeTiles(std::vector<boost::shared_ptr<tile>> tiles, boost::shared_ptr<tile> t) {
//	for (int i = 0; i < (int)tiles.size(); i++) {
//		if (tiles.at(i)->getID() == t->getID()) {
//			boost::shared_ptr<tile> vec = tiles.at(i);
//			if (vec->getW() == t->getW() && vec->getH() == t->getH()) {
//				if (vec->getY() == t->getY()) {
//					if (vec->getX() == t->getX() - t->getW()) {
//						vec->setWidth(vec->getW() + t->getW());
//
//					} 
//				} 
//			} 
//		}
//	}
//
//	tiles.insert(tiles.begin(), t);
//	return tiles;
//}

std::vector<boost::shared_ptr<gameObject>> tileLoader::loadTiles(std::vector<boost::shared_ptr<gameObject>> objs, std::string filePath) {
	return loadTiles(objs, filePath, NULL);
}
std::vector<boost::shared_ptr<gameObject>> tileLoader::loadTiles(std::vector<boost::shared_ptr<gameObject>> objs, std::string filePath, GLuint spriteSheet) {
	GLuint tex = loadTexture::at(filePath);
	std::vector<boost::shared_ptr<tile>> tiles;
	if (tex != NULL) {
		glBindTexture(GL_TEXTURE_2D, tex);
		GLint textureW, textureH;
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureW);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureH);

		filePath = "res\\" + filePath;
		// .dib's have been found to be actually much more superior then .bmp's because .dib sounds cooler
		unsigned char *rgbaFucked = SOIL_load_image(filePath.c_str(), &textureW, &textureH, 0, SOIL_LOAD_RGBA);
		// goddamit SOIL, why does your origin start at the top left......
		// well, got to inverse the Y axis in order to properly line up tiles

		 // create a new array... going old school C with this
		unsigned char *rgba = (unsigned char *)malloc((textureW * textureH * 4) * sizeof(unsigned char));

		 // invert the Y axis of rgbaFucked (iterate backwards by height, forwards by width, copy to new array)
		for (int h = textureH - 1; h >= 0; h--) {
			for (int w = 0; w < textureW; w++) {
				// red
				rgba[(w + (textureW * ((textureH - 1) - h))) * 4 + 0] = rgbaFucked[(w + (textureW * h)) * 4 + 0];
				// green
				rgba[(w + (textureW * ((textureH - 1) - h))) * 4 + 1] = rgbaFucked[(w + (textureW * h)) * 4 + 1];
				// blue
				rgba[(w + (textureW * ((textureH - 1) - h))) * 4 + 2] = rgbaFucked[(w + (textureW * h)) * 4 + 2];
				// alpha
				rgba[(w + (textureW * ((textureH - 1) - h))) * 4 + 3] = rgbaFucked[(w + (textureW * h)) * 4 + 3];
			}
		}
		float TS = game::TS() / 2;

		// now we can iterate through the unfucked values and use them to generate tiles
		for (int h = 0; h < textureH; h++) {
			for (int w = 0; w < textureW; w++) {
				int r = rgba[(w + (textureW * h)) * 4 + 0];
				int g = rgba[(w + (textureW * h)) * 4 + 1];
				int b = rgba[(w + (textureW * h)) * 4 + 2];
				int a = rgba[(w + (textureW * h)) * 4 + 3];

				//printf("X %i\tY %i\t R: %i, G: %i, B: %i, A: %i\n", w, h, r, g, b, a);

				// too many variables for a switch statement...
				if (r == 195 && g == 195 && b == 195) {
					boost::shared_ptr<tile> t(new tile(w * TS, h * TS, TS, TS, false, ""));
					t->setID(0);
					t->setX(w * TS);
					t->setY(h * TS);
					t->setWidth(TS);
					t->setHeight(TS);
					t->setTexture(spriteSheet, 1, 1, 16, 1);
					//printf("x %1.0f, y %1.0f\n", t->getX(), t->getY());
					t->setCollides(false);

					tiles.insert(tiles.begin(), t);
				}
				else if(r == 127 && g == 127 && b == 127) {

					boost::shared_ptr<tile> t(new tile(w * TS, h * TS, TS, TS, true, ""));
					t->setID(1);
					//t->setColor(r, g, b, 255);
					t->setX(w * TS);
					t->setY(h * TS);
					t->setWidth(TS);
					t->setHeight(TS);
					t->setTexture(spriteSheet, 1, 0, 16, 1);
					t->setCollides(true);

					tiles.insert(tiles.begin(), t);
				}
			}
			//printf("-------------------------------\n");
		}
		free(rgba);
	}
	objs.insert(objs.begin(), tiles.begin(), tiles.end());
	return objs;
}


tileLoader::~tileLoader() {}
