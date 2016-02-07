#include "game.h"




// you should set the variables of all objects in THIS constructor, as the constructors of all other objects get called every frame
game::game() {
	
	float TS = game::TS();

	boost::shared_ptr<tile> t1 (new tile(TS * 5, TS * 5, TS, TS, true, ""));
	boost::shared_ptr<player> pl(new player(TS * 4, TS * 4, TS, TS));
	boost::shared_ptr<computer> terminal(new computer());
	bouncer *b1 = new bouncer(TS, TS * 4);
	
	terminal->setX(1 * TS);
	terminal->setY(3 * TS);
	terminal->setWidth(TS);
	terminal->setHeight(TS);
	printf("%s\n", gluErrorString(glGetError()));

	pl->setVariables(TS * 2, TS * 4, TS, TS, 255, 255, 255, 255, false, "items.png", 0, 0, 16, 1);

	pl->enableObjs(this->objects);
	this->ply = pl;

	this->objects.push_back(terminal);
	this->objects.push_back(pl);

}

void game::contextCreated() {
	this->objects = tileLoader::loadTiles(this->objects, "room3.dib", loadTexture::at("tiles.png"));
	updateObjs();

	for (int i = 0; i < (int)(this->objects.size()); i++) {
		this->objects.at(i)->contextCreated();
	}
}

void game::render() {	
	// iterate through every game object and render
	
	blockVisionAndRender();

	//for(int i = 0; i < (int)(this->objects.size()); i++) {
	//	boost::shared_ptr<gameObject> go = this->objects.at(i);
	//	if (typeid(*go) != typeid(player)) {

	//	}
	//	//go->render(); <--- THAT IS NOW DONE IN BLOCKVISION
	//}

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

std::array<bool, 4> game::areSharingCoordinates(boost::shared_ptr<gameObject> obj) {
	// x1, x2, y1, y2 of the inputted obj
	float thisX1 = obj->getX();
	float thisX2 = obj->getX() + obj->getW();
	float thisY1 = obj->getY();
	float thisY2 = obj->getY() + obj->getH();
	std::array<bool, 4> out = { false, false, false, false };

	for (int i = 0; i < (int)(this->objects.size()); i++) {
		boost::shared_ptr<gameObject> obj2 = this->objects.at(i);
		float objX1 = obj2->getX();
		float objX2 = obj2->getX() + obj2->getW();
		float objY1 = obj2->getY();
		float objY2 = obj2->getY() + obj2->getH();

		// object is directly to the left
		if (thisX1 == objX2 && thisY1 == objY1)
			if (thisX1 == objX2 && thisY2 == objY2)
				out.at(0) = true;

		// object is directly above
		if (thisX1 == objX1 && thisY2 == objY1)
			if (thisX2 == objX2 && thisY2 == objY1)
				out.at(1) = true;

		// object is directly to the right
		if (thisX2 == objX1 && thisY1 == objY1)
			if (thisX2 == objX1 && thisY2 == objY2)
				out.at(2) = true;

		// object is directly below
		if (thisX1 == objX1 && thisY1 == objY2)
			if (thisX2 == objX2 && thisY1 == objY2)
				out.at(3) = true;
	}
	//return false;
	return out;
}

void game::blockVisionAndRender() {
	// right/top of screen
	float scrW = glutGet(GLUT_WINDOW_WIDTH);
	float scrH = glutGet(GLUT_WINDOW_HEIGHT);

	// left/bottom of screen
	float scrX = 0;
	float scrY = 0;
	for (int i = 0; i < (int)(this->objects.size()); i++) {
		boost::shared_ptr<gameObject> obj = this->objects.at(i);

		float x1 = -1.f;
		float y1 = -1.f;
		float x2 = -1.f;
		float y2 = -1.f;
		float x3 = -1.f;
		float y3 = -1.f;
		float x4 = -1.f;
		float y4 = -1.f;

		if (typeid(*obj) == typeid(tile)) {
			if (obj->getOpaque()) {

				// get a list of the coordinates that are being shared
				std::array<bool, 4> shared = areSharingCoordinates(obj);

				// four corners of the tile
				y1 = obj->getY();
				y2 = obj->getY() + obj->getH();
				x1 = obj->getX();
				x2 = obj->getX() + obj->getW();

				// are these coordinates shared with another?
				bool x1y1Shared = false;
				bool x1y2Shared = false;
				bool x2y1Shared = false;
				bool x2y2Shared = false;


				// the center x of the player
				float plyCX = ply->getX() + (ply->getW() / 2);
				// the center y of the player
				float plyCY = ply->getY() + (ply->getH() / 2) + (game::TS() / 80 * 32);

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

					// something about swapping stds...
					std::swap(y1, y2);
					
					x3 = (plyCX + ((x2 - plyCX) * (1 + lenCoord3)));
					y3 = (plyCY + ((y2 - plyCY) * (1 + lenCoord3)));
					x4 = (plyCX + ((x1 - plyCX) * (1 + lenCoord4)));
					y4 = (plyCY + ((y1 - plyCY) * (1 + lenCoord4)));
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

					std::swap(x1, x2);
					std::swap(y1, y2);

					x3 = (plyCX + ((x2 - plyCX) * (1 + lenCoord3)));
					y3 = (plyCY + ((y2 - plyCY) * (1 + lenCoord3)));
					x4 = (plyCX + ((x1 - plyCX) * (1 + lenCoord4)));
					y4 = (plyCY + ((y1 - plyCY) * (1 + lenCoord4)));
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

					std::swap(y1, y2);

					x3 = (plyCX + ((x2 - plyCX) * (1 + lenCoord3)));
					y3 = (plyCY + ((y2 - plyCY) * (1 + lenCoord3)));
					x4 = (plyCX + ((x1 - plyCX) * (1 + lenCoord4)));
					y4 = (plyCY + ((y1 - plyCY) * (1 + lenCoord4)));
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

					std::swap(y1, y2);
					x1 = x2;

					x3 = (plyCX + ((x1 - plyCX) * (1 + lenCoord3)));
					y3 = (plyCY + ((y2 - plyCY) * (1 + lenCoord3)));
					x4 = (plyCX + ((x1 - plyCX) * (1 + lenCoord4)));
					y4 = (plyCY + ((y1 - plyCY) * (1 + lenCoord4)));
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

					std::swap(x2, x1);
					y2 = y1;

					x3 = (plyCX + ((x2 - plyCX) * (1 + lenCoord3)));
					y3 = (plyCY + ((y2 - plyCY) * (1 + lenCoord3)));
					x4 = (plyCX + ((x1 - plyCX) * (1 + lenCoord4)));
					y4 = (plyCY + ((y2 - plyCY) * (1 + lenCoord4)));
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

					x2 = x1;

					x3 = (plyCX + ((x1 - plyCX) * (1 + lenCoord3)));
					y3 = (plyCY + ((y2 - plyCY) * (1 + lenCoord3)));
					x4 = (plyCX + ((x1 - plyCX) * (1 + lenCoord4)));
					y4 = (plyCY + ((y1 - plyCY) * (1 + lenCoord4)));
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
					
					y1 = y2;

					x3 = (plyCX + ((x2 - plyCX) * (1 + lenCoord3)));
					y3 = (plyCY + ((y2 - plyCY) * (1 + lenCoord3)));
					x4 = (plyCX + ((x1 - plyCX) * (1 + lenCoord4)));
					y4 = (plyCY + ((y2 - plyCY) * (1 + lenCoord4)));
				}

				// now just hope that that you never run into the scenario where all 4 coordinates are actually exactly -1, -1
				if(x1 != -1 && y1 != -1 && x2 != -1 && y2 != -1 && x3 != -1 && y3 != -1 && x4 != -1 && y4 != -1)
					draw::polygon(x1, y1, x2, y2, x3, y3, x4, y4, 0, 0, 0, 255);
			}
		}
		obj->render();
	}
}


game::~game() {}
