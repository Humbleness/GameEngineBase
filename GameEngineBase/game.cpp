#include "game.h"




// you should set the variables of all objects in THIS constructor, as the constructors of all other objects get called every frame
game::game() {
	
	float TS = game::TS();

	boost::shared_ptr<tile> t1 (new tile(TS * 5, TS * 5, TS, TS, true, ""));
	boost::shared_ptr<player> pl(new player(TS * 4, TS * 4, TS, TS));
	bouncer *b1 = new bouncer(TS, TS * 4);

	//ground->setTexture("love.bmp");
	pl->setVariables(TS * 2, TS * 4, TS, TS, 255, 255, 255, 255, false, "items.png", 0, 0, 16, 1);

	pl->enableObjs(this->objects);
	this->ply = pl;

	this->objects.push_back(pl);

}

void game::contextCreated() {
	this->objects = tileLoader::loadTiles(this->objects, "room2.dib", loadTexture::at("tiles.png"));
	updateObjs();

	for (int i = 0; i < (int)(this->objects.size()); i++) {
		this->objects.at(i)->contextCreated();
	}
}

void game::render() {	
	// iterate through every game object and render
	for(int i = 0; i < (int)(this->objects.size()); i++) {
		boost::shared_ptr<gameObject> go = this->objects.at(i);
		blockVision(go);
		if (typeid(*go) != typeid(player)) {

		}
		go->render();
	}

	// finish drawing, display to screen
	draw::render();
}

void game::update() {
	int size = (int)this->objects.size();
	for (int i = 0; i < size; i++) {
		boost::shared_ptr<gameObject> go = this->objects.at(i);
		go->update();
		go->doGameObjectShit();
	}

	//this->blockVision();

	render();
}

void game::recieveInput(char key, int x, int y, int mod) {
	for (int i = 0; i < (int)this->objects.size(); i++) {
		this->objects.at(i)->input(key, x, y, mod);
	}
}

void game::keyUp(char key, int x, int y) {
	for (int i = 0; i < (int)this->objects.size(); i++)
		this->objects.at(i)->keyUp(key, x, y);
}

void game::updateObjs() {
	for (int i = 0; i < (int)(this->objects.size()); i++) {
		this->objects.at(i)->updateObjs(this->objects);
	}
}

bool game::areSharingCoordinates(float x, float y) {
	bool out = false;
	for (int i = 0; i < (int)(this->objects.size()); i++) {
		boost::shared_ptr<gameObject> obj = this->objects.at(i);
		if (obj->getX() == x && obj->getY() == y) out = true;
	}
	return out;
}

void game::blockVision(boost::shared_ptr<gameObject> obj) {
	// make a copy of the current player
	//boost::shared_ptr<gameObject> ply;

	// right/top of screen
	float scrW = glutGet(GLUT_WINDOW_WIDTH);
	float scrH = glutGet(GLUT_WINDOW_HEIGHT);

	// left/bottom of screen
	float scrX = 0;
	float scrY = 0;

	//// find the player object
	//for (int i = 0; i < (int)this->objects.size(); i++) {
	//	boost::shared_ptr<gameObject> obj = this->objects.at(i);
	//	if (typeid(*obj) == typeid(player)) {
	//		ply = obj;
	//		break;
	//	}
	//}

	// use two loops over the same vector cause i dont give a fuck
	//for (int i = 0; i < (int)this->objects.size(); i++) {
		//boost::shared_ptr<gameObject> obj = this->objects.at(i);
		if (typeid(*obj) == typeid(tile)) {
			if (obj->collides()) {
				// four corners of the tile
				float y1 = obj->getY();
				float y2 = obj->getY() + obj->getH();
				float x1 = obj->getX();
				float x2 = obj->getX() + obj->getW();

				float x3 = 0;
				float y3 = 0;
				float x4 = 0;
				float y4 = 0;


				// the center x of the player
				float plyCX = ply->getX() + (ply->getW() / 2);
				// the center y of the player
				float plyCY = ply->getY() + (ply->getH() / 2) + (game::TS()/80 * 32);

				// and this is 10/10 how you get rid of divide by zero errors
				if (plyCX == 0) plyCX = 0.1f;
				if (plyCY == 0) plyCY = 0.1f;

				// tile is to the bottem left
				if (plyCX > x2 && plyCY > y2) {
					// length between corner and player
					float lenPlyX3 = x2 - plyCX;
					lenPlyX3 = lenPlyX3 == 0 ? .01 : lenPlyX3;
					float lenPlyY3 = y1 - plyCY;
					lenPlyY3 = lenPlyY3 == 0 ? .01 : lenPlyY3;
					// length between corner and edge of screen
					float lenScrX3 = scrX - x2;
					float lenScrY3 = scrY - y1;
					// get the ratio between the two lengths
					float lenCoord3 = lenScrX3 / lenPlyX3;

					// repeat with fourth set of coordinates
					float lenPlyX4 = x1 - plyCX;
					lenPlyX4 = lenPlyX4 == 0 ? .01 : lenPlyX4;
					float lenPlyY4 = y2 - plyCY;
					lenPlyY4 = lenPlyY4 == 0 ? .01 : lenPlyY4;
					float lenScrX4 = scrX - x1;
					float lenScrY4 = scrY - y2;
					float lenCoord4 = lenScrX4 / lenPlyX4;

					x3 = (plyCX + ((x2 - plyCX) * (1 + lenCoord3)));
					y3 = (plyCY + ((y1 - plyCY) * (1 + lenCoord3)));
					x4 = (plyCX + ((x1 - plyCX) * (1 + lenCoord4)));
					y4 = (plyCY + ((y2 - plyCY) * (1 + lenCoord4)));

					draw::polygon(x1, y2, x2, y1, x3, y3, x4, y4, 0, 0, 0, 255);
				}

				// tile is to the top left
				else if (plyCX > x2 && plyCY < y1) {
					// length between corner and player
					float lenPlyX3 = x1 - plyCX;
					lenPlyX3 = lenPlyX3 == 0 ? .01 : lenPlyX3;
					float lenPlyY3 = y1 - plyCY;
					lenPlyY3 = lenPlyY3 == 0 ? .01 : lenPlyY3;
					// length between corner and edge of screen
					float lenScrX3 = scrX - x1;
					float lenScrY3 = scrY - y1;
					// get the ratio between the two lengths
					float lenCoord3 = lenScrX3 / lenPlyX3;

					// repeat with fourth set of coordinates
					float lenPlyX4 = x2 - plyCX;// -x2;
					lenPlyX4 = lenPlyX4 == 0 ? .01 : lenPlyX4;
					float lenPlyY4 = y2 - plyCY;// -y2;
					lenPlyY4 = lenPlyY4 == 0 ? .01 : lenPlyY4;
					float lenScrX4 = scrX - x2;
					float lenScrY4 = scrY - y2;
					float lenCoord4 = lenScrX4 / lenPlyX4;

					x3 = (plyCX + ((x1 - plyCX) * (1 + lenCoord3)));
					y3 = (plyCY + ((y1 - plyCY) * (1 + lenCoord3)));
					x4 = (plyCX + ((x2 - plyCX) * (1 + lenCoord4)));
					y4 = (plyCY + ((y2 - plyCY) * (1 + lenCoord4)));

					draw::polygon(x2, y2, x1, y1, x3, y3, x4, y4, 0, 0, 0, 255);
				}

				// tile is to the top right
				else if (plyCX < x1 && plyCY < y1) {
					// length between corner and player
					float lenPlyX3 = x2 - plyCX;
					lenPlyX3 = lenPlyX3 == 0 ? .01 : lenPlyX3;
					float lenPlyY3 = y1 - plyCY;
					lenPlyY3 = lenPlyY3 == 0 ? .01 : lenPlyY3;
					// length between corner and edge of screen
					float lenScrX3 = scrW - x2;
					float lenScrY3 = scrH - y1;
					// get the ratio between the two lengths
					float lenCoord3 = lenScrX3 / lenPlyX3;

					// repeat with fourth set of coordinates
					float lenPlyX4 = x1 - plyCX;
					lenPlyX4 = lenPlyX4 == 0 ? .01 : lenPlyX4;
					float lenPlyY4 = y2 - plyCY;
					lenPlyY4 = lenPlyY4 == 0 ? .01 : lenPlyY4;
					float lenScrX4 = scrW - x1;
					float lenScrY4 = scrH - y2;
					float lenCoord4 = lenScrX4 / lenPlyX4;

					x3 = (plyCX + ((x2 - plyCX) * (1 + lenCoord3)));
					y3 = (plyCY + ((y1 - plyCY) * (1 + lenCoord3)));
					x4 = (plyCX + ((x1 - plyCX) * (1 + lenCoord4)));
					y4 = (plyCY + ((y2 - plyCY) * (1 + lenCoord4)));

					draw::polygon(x1, y2, x2, y1, x3, y3, x4, y4, 0, 0, 0, 255);
				}

				// tile is bottem right
				else if (plyCX < x1 && plyCY > y2) {
					// length between corner and player
					float lenPlyX3 = x2 - plyCX;
					lenPlyX3 = lenPlyX3 == 0 ? .01 : lenPlyX3;
					float lenPlyY3 = y2 - plyCY;
					lenPlyY3 = lenPlyY3 == 0 ? .01 : lenPlyY3;
					// length between corner and edge of screen
					float lenScrX3 = scrW - x2;
					float lenScrY3 = scrH - y2;
					// get the ratio between the two lengths
					float lenCoord3 = lenScrX3 / lenPlyX3;

					// repeat with fourth set of coordinates
					float lenPlyX4 = x1 - plyCX;
					lenPlyX4 = lenPlyX4 == 0 ? .01 : lenPlyX4;
					float lenPlyY4 = y1 - plyCY;
					lenPlyY4 = lenPlyY4 == 0 ? .01 : lenPlyY4;
					float lenScrX4 = scrW - x1;
					float lenScrY4 = scrH - y1;
					float lenCoord4 = lenScrX4 / lenPlyX4;

					x3 = (plyCX + ((x2 - plyCX) * (1 + lenCoord3)));
					y3 = (plyCY + ((y2 - plyCY) * (1 + lenCoord3)));
					x4 = (plyCX + ((x1 - plyCX) * (1 + lenCoord4)));
					y4 = (plyCY + ((y1 - plyCY) * (1 + lenCoord4)));

					draw::polygon(x1, y1, x2, y2, x3, y3, x4, y4, 0, 0, 0, 255);
				}

				// tile is left
				else if ((plyCX > x2 && plyCY <= y2) && (plyCX > x2 && plyCY > y1)) {
					// length between corner and player
					float lenPlyX3 = x2 - plyCX;
					lenPlyX3 = lenPlyX3 == 0 ? .01 : lenPlyX3;
					float lenPlyY3 = y1 - plyCY;
					lenPlyY3 = lenPlyY3 == 0 ? .01 : lenPlyY3;
					// length between corner and edge of screen
					float lenScrX3 = scrX - x2;
					float lenScrY3 = scrY - y1;
					// get the ratio between the two lengths
					float lenCoord3 = lenScrX3 / lenPlyX3;

					// repeat with fourth set of coordinates
					float lenPlyX4 = x2 - plyCX;
					lenPlyX4 = lenPlyX4 == 0 ? .01 : lenPlyX4;
					float lenPlyY4 = y2 - plyCY;
					lenPlyY4 = lenPlyY4 == 0 ? .01 : lenPlyY4;
					float lenScrX4 = scrX - x2;
					float lenScrY4 = scrY - y2;
					float lenCoord4 = lenScrX4 / lenPlyX4;

					x3 = (plyCX + ((x2 - plyCX) * (1 + lenCoord3)));
					y3 = (plyCY + ((y1 - plyCY) * (1 + lenCoord3)));
					x4 = (plyCX + ((x2 - plyCX) * (1 + lenCoord4)));
					y4 = (plyCY + ((y2 - plyCY) * (1 + lenCoord4)));

					draw::polygon(x2, y2, x2, y1, x3, y3, x4, y4, 0, 0, 0, 255);
				}

				// tile is above
				else if ((plyCX >= x1 && plyCY < y1) && (plyCX <= x2 && plyCY < y1)) {
					// length between corner and player
					float lenPlyX3 = x1 - plyCX;
					lenPlyX3 = lenPlyX3 == 0 ? .01 : lenPlyX3;
					float lenPlyY3 = y1 - plyCY;
					lenPlyY3 = lenPlyY3 == 0 ? .01 : lenPlyY3;
					// length between corner and edge of screen
					float lenScrX3 = scrW - x1;
					float lenScrY3 = scrH - y1;
					// get the ratio between the two lengths
					float lenCoord3 = lenScrY3 / lenPlyY3;

					// repeat with fourth set of coordinates
					float lenPlyX4 = x2 - plyCX;
					lenPlyX4 = lenPlyX4 == 0 ? .01 : lenPlyX4;
					float lenPlyY4 = y1 - plyCY;
					lenPlyY4 = lenPlyY4 == 0 ? .01 : lenPlyY4;
					float lenScrX4 = scrW - x2;
					float lenScrY4 = scrH - y1;
					float lenCoord4 = lenScrY4 / lenPlyY4;

					x3 = (plyCX + ((x1 - plyCX) * (1 + lenCoord3)));
					y3 = (plyCY + ((y1 - plyCY) * (1 + lenCoord3)));
					x4 = (plyCX + ((x2 - plyCX) * (1 + lenCoord4)));
					y4 = (plyCY + ((y1 - plyCY) * (1 + lenCoord4)));

					draw::polygon(x2, y1, x1, y1, x3, y3, x4, y4, 0, 0, 0, 255);
				}

				// tile is right
				else if ((plyCX < x1 && plyCY <= y2) && (plyCX < x2 && plyCY >= y1)) {
					// length between corner and player
					float lenPlyX3 = x1 - plyCX;
					lenPlyX3 = lenPlyX3 == 0 ? .01 : lenPlyX3;
					float lenPlyY3 = y2 - plyCY;
					lenPlyY3 = lenPlyY3 == 0 ? .01 : lenPlyY3;
					// length between corner and edge of screen
					float lenScrX3 = scrW - x1;
					float lenScrY3 = scrH - y2;
					// get the ratio between the two lengths
					float lenCoord3 = lenScrX3 / lenPlyX3;

					// repeat with fourth set of coordinates
					float lenPlyX4 = x1 - plyCX;
					lenPlyX4 = lenPlyX4 == 0 ? .01 : lenPlyX4;
					float lenPlyY4 = y1 - plyCY;
					lenPlyY4 = lenPlyY4 == 0 ? .01 : lenPlyY4;
					float lenScrX4 = scrW - x1;
					float lenScrY4 = scrH - y1;
					float lenCoord4 = lenScrX4 / lenPlyX4;

					x3 = (plyCX + ((x1 - plyCX) * (1 + lenCoord3)));
					y3 = (plyCY + ((y2 - plyCY) * (1 + lenCoord3)));
					x4 = (plyCX + ((x1 - plyCX) * (1 + lenCoord4)));
					y4 = (plyCY + ((y1 - plyCY) * (1 + lenCoord4)));

					draw::polygon(x1, y1, x1, y2, x3, y3, x4, y4, 0, 0, 0, 255);
				}

				// tile is underneath
				else if ((plyCX >= x1 && plyCY > y2) && (plyCX <= x2 && plyCY > y2)) {
					// length between corner and player
					float lenPlyX3 = x2 - plyCX;
					lenPlyX3 = lenPlyX3 == 0 ? .01 : lenPlyX3;
					float lenPlyY3 = y2 - plyCY;
					lenPlyY3 = lenPlyY3 == 0 ? .01 : lenPlyY3;
					// length between corner and edge of screen
					float lenScrX3 = scrX - x2;
					float lenScrY3 = scrY - y2;
					// get the ratio between the two lengths
					float lenCoord3 = lenScrY3 / lenPlyY3;

					// repeat with fourth set of coordinates
					float lenPlyX4 = x1 - plyCX;
					lenPlyX4 = lenPlyX4 == 0 ? .01 : lenPlyX4;
					float lenPlyY4 = y2 - plyCY;
					lenPlyY4 = lenPlyY4 == 0 ? .01 : lenPlyY4;
					float lenScrX4 = scrX - x1;
					float lenScrY4 = scrY - y2;
					float lenCoord4 = lenScrY4 / lenPlyY4;

					x3 = (plyCX + ((x2 - plyCX) * (1 + lenCoord3)));
					y3 = (plyCY + ((y2 - plyCY) * (1 + lenCoord3)));
					x4 = (plyCX + ((x1 - plyCX) * (1 + lenCoord4)));
					y4 = (plyCY + ((y2 - plyCY) * (1 + lenCoord4)));

					draw::polygon(x1, y2, x2, y2, x3, y3, x4, y4, 0, 0, 0, 255);
				}
			}
		}
	//}
}


game::~game() {}
