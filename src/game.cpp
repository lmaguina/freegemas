#include "game.h"

#include "log.h"
#include "state.h"

#include "stateGame.h"
#include "stateMainMenu.h"

#include "resManager.h"

Game::Game () : Gosu::Window(800, 600, false) {
    lDEBUG << Log::CON("Game");
    setCaption(L"FreeGemas v0.3");
    
    mousePointer.reset(new Gosu::Image(graphics(), Gosu::resourcePrefix() + L"media/handCursor.png"));
    ResourceManager::instance() -> init(graphics());    

    changeState("stateMainMenu");
}

void Game::update(){
    currentState -> update();
}

void Game::draw(){
    mousePointer -> draw(input().mouseX(), input().mouseY(), 90);
    currentState -> draw();
}

void Game::buttonDown(Gosu::Button button){
    currentState -> buttonDown(button);
}

void Game::buttonUp(Gosu::Button button){
    currentState -> buttonUp(button);
}

void Game::changeState(string S){
    if(S == currentStateString)
	return;

    if(S == "stateMainMenu"){
	currentState . reset(new StateMainMenu(this));
	currentStateString = "stateMainMenu";
    }
    else if(S == "stateGame"){
	currentState . reset(new StateGame(this));
	currentStateString = "estadoGame";
    }
}

Game::~Game(){
    lDEBUG << Log::DES("Game");
}
