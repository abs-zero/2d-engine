#include "Display.h"
#include "Texture.h"
#include "World.h"
#include "Tilemap.h"
#include "Level.h"
#include "Entity.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

#define WIDTH 1280
#define HEIGHT 720

Vec2D movement;

void pMovement(Entity *player, Tilemap map) {
	if(isKeyPressed(GLFW_KEY_W)) {
		movement.y += SPEED;
	}

	if(isKeyPressed(GLFW_KEY_S)) {
		movement.y -= SPEED;
	}

	if(isKeyPressed(GLFW_KEY_A)) {
		movement.x -= SPEED;
	}

	if(isKeyPressed(GLFW_KEY_D)) {
		movement.x += SPEED;
	}

	moveEntity(&movement, player, map, getDelta());
}

int main() {

	createDisplay(WIDTH, HEIGHT, "2D-Engine");

	Level lvl1;
	lvl1.map = loadTiles("tilemap.png"); //t1 - 90 C-CW - Flip Horizontally - Flip V
	lvl1.bg = loadTexture("back.png");

	Entity player;
	player.pos.x = 0;
	player.pos.y = 500;
	movement.x = 0;
	movement.y = 0;

	loadWorld(WIDTH, HEIGHT, lvl1, &player);

	prepOGL();
	while(!shouldCloseWindow()) {
		startLoop();
		prepRender();
		renderWorld();

		pMovement(&player, lvl1.map);

		endLoop();
	}

	worldCleanUp();
	displayCleanUp();
}