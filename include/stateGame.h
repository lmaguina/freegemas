/**
 * @file stateJuego.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Archivo para la clase de juego principal
 * 
 * Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */


#ifndef _STATEGAME_H_
#define _STATEGAME_H_

#include <Gosu/Gosu.hpp>

#include <utility>
#include <set>
using namespace std;

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "state.h"
#include "board.h"
#include "floatingScore.h"
#include "baseButton.h"
#include "scoreTable.h"

class Game;

/**
 * @class StateGame
 *
 * @brief State de game principal, con board, gemas y demás.
 *
 * Este es el state en el que el jugador puede interactuar con el board y jugar.
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */


class StateGame : public State{
public:
    StateGame(Game * p);
    void update();
    void draw();
    void buttonDown(Gosu::Button B);
    void buttonUp(Gosu::Button B);
    ~StateGame();

private:

    /** Función para el cálculo de animaciones.

	@param t Tiempo transcurrido
	@param b Valor inicial (beginning)
	@param c Diferencia entre inicial y final (change)
	@param d Duración
    */
    static float eqMovIn(float t, float b, float c, float d);
    static float eqMovOut(float t, float b, float c, float d);

    void gemsOutScreen();

    int mostrandoPista;
    int totalAnimPista;

    coord coordPista;

    /// Carga las imágenes de las gemas
    //void cargarGemas();

    void init();
    void loadGems();

    /// Indica si está sobre una gema
    //bool sobreGema(int mX, int mY);

    bool overGem(int mX, int mY);

    /// Devuelve las coordenadas de casilla correspondientes a las coordenadas de ratón mX,mY.
    //pair<int,int> dameGema(int mX, int mY);

    coord getCoord(int mX, int mY);

    /// Regenera la imagen del marcador de puntos

    void redrawScoreboard();

    void createFloatingScores();
    
    bool checkClickedSquare(int mX, int mY);

    void showHint();

    void playMatchSound();

	void resetGame();
    Board board;

    enum tState{
        eFirstFlip,
        eLoading,
	eInicialGemas,
	eEspera,
	eGemaMarcada,
	eGemasCambiando,
	eGemasDesapareciendo,
	eGemasNuevasCayendo,
	eDesapareceBoard,
	eTimeFinished,
	eShowingScoreTable
    };

    tState state;

    coord selectedSquareFirst;

    /// Coordenadas de la segunda casilla marcada
    int casillaMarcada2X, casillaMarcada2Y;

    /// Paso actual en la animación
    int pasoAnim;

    /// Total de pasos en la animación
    int totalAnim;

    /// Total de pasos en la animación inicial
    int totalAnimInit;

    /// Contenedor temporal de las squares a borrar
    MultipleMatch groupedSquares;

    boost::shared_ptr<Gosu::Image> imgBoard;

    boost::shared_ptr<Gosu::Image> imgWhite;
    boost::shared_ptr<Gosu::Image> imgRed;
    boost::shared_ptr<Gosu::Image> imgPurple;
    boost::shared_ptr<Gosu::Image> imgOrange;
    boost::shared_ptr<Gosu::Image> imgGreen;
    boost::shared_ptr<Gosu::Image> imgYellow;
    boost::shared_ptr<Gosu::Image> imgBlue;

    boost::shared_ptr<Gosu::Image> imgSelector;

    boost::shared_ptr<Gosu::Image> txtPuntos;
    int puntos;

    boost::scoped_ptr<BaseButton> hintButton;
    boost::scoped_ptr<BaseButton> resetButton;
    boost::scoped_ptr<BaseButton> exitButton;
    boost::scoped_ptr<BaseButton> musicButton;
    
    vector<FloatingScore> scoreSet;

    boost::shared_ptr<Gosu::Image> imgTimeBackground;
    boost::shared_ptr<Gosu::Font> fontTime;
    
    boost::shared_ptr<Gosu::Image> imgLoadingBanner;

    string txtTime;
    double timeStart;


    boost::scoped_ptr<Gosu::Sample> sfxMatch1, sfxMatch2, sfxMatch3;
    boost::scoped_ptr<Gosu::Sample> sfxSelect;
    boost::scoped_ptr<Gosu::Sample> sfxFall;

    boost::scoped_ptr<Gosu::Song> sfxSong;
    int acumulator;

    bool clicking;

    boost::scoped_ptr<ScoreTable> scoreTable;
};

#endif /* _STATEGAME_H_ */
