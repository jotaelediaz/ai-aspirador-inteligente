#include "agent.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;
// -----------------------------------------------------------

//Asigna un obstaculo en la matriz del agente a la casilla siguiente a la actual.
void Agent::AsignarObstaculo() {

    if (orientacion_ == 0) { //Si Norte
        mi_mapa[x_actual-1][y_actual] = -1;
    } else if (orientacion_ == 1) { //Si Este
        mi_mapa[x_actual][y_actual+1] = -1;
    } else if (orientacion_ == 2) {  //Si Sur
        mi_mapa[x_actual+1][y_actual] = -1;
    } else if (orientacion_ == 3) { //Si Oeste
        mi_mapa[x_actual][y_actual-1] = -1;
    }

}

//AVANCE EN LA MATRIZ
void Agent::AvanzarCasilla() {

    if (orientacion_ == 0) { //Si Norte
        x_actual--;
    } else if (orientacion_ == 1) { //Si Este
        y_actual++;
    } else if (orientacion_ == 2) {  //Si Sur
        x_actual++;
    } else if (orientacion_ == 3) { //Si Oeste
        y_actual--;
    }
}

//Calcula cual de las cuatro direcciones desde la casilla actual es mejor (Hace mas tiempo que se paso)
int Agent::MejorCasilla() {

    int lamejor = -2;
    int direcciones[4];
    int vmenor = 9999;

    direcciones[0] = mi_mapa[x_actual-1][y_actual]; //NORTE
    direcciones[1] = mi_mapa[x_actual][y_actual+1]; //ESTE
    direcciones[2] = mi_mapa[x_actual+1][y_actual]; //SUR
    direcciones[3] = mi_mapa[x_actual][y_actual-1]; //OESTE


    for(int i=0; i<4; i++) {
        if (direcciones[i] < vmenor && direcciones[i]!= -1) {
            vmenor = direcciones[i];
            lamejor = i;
        }
    }

    //Si la mejor es tan buena como girar seguir recto hace esto.
    if(vmenor == direcciones[orientacion_]) {
        lamejor = orientacion_;
    }

    /*cout << "vmenor = " << vmenor << endl;
    cout << "mejor dir =" << lamejor << endl;*/

    return lamejor;
}

// 0 = RECTO , 1 = DERECHA, -1 = IZQUIERDA, 2 / -2 = A DOS GIROS DE LA ACTUAL!
int Agent::ElegirDireccion(int ori_deseada) {

    int dire;

    //Restamos a la orientacion deseada la actual, obteniendo así el sentido del giro que debemos hacer para llegar a la deseada:
    // 0 = RECTO , 1 = DERECHA, -1 = IZQUIERDA, 2 / -2 = A DOS GIROS DE LA ACTUAL!
    dire = ori_deseada - orientacion_;

    if(dire == 3) { dire = -1; } //Arreglamos el caso para el Oeste (3)
    if(dire == -3) { dire = 1; }

    return dire;
}

Agent::ActionType Agent::Think() {

	ActionType accion;



    switch(ult_accion_) {

            case actFORWARD:
                if (bump_) {
                    obstaculo_[orientacion_] = true;
                    AsignarObstaculo();//Marcamos la casilla con la que se choca como pared
                } else {
                    for(int i=0; i<4; i++) { obstaculo_[i]=false; }
                    AvanzarCasilla();
                }
            break;

            case actTURN_R:
                orientacion_++;
                if(orientacion_>3)
                    orientacion_=0;
            break;

            case actTURN_L:
                orientacion_--;
                if(orientacion_<0)
                    orientacion_=3;
            break;

        }

        mi_mapa[x_actual][y_actual] = turno_actual;

        //Imprimir la matriz tras el ultimo movimiento (El 2000)
        if(turno_actual == 2000) {

            for(int i=0; i<20; i++) {
                cout << "\n";
                for(int j=0; j<20; j++) {
                    if (mi_mapa[i][j] >= 1000) { cout << mi_mapa[i][j] << " "; }
                    else if (mi_mapa[i][j] >= 100) { cout << "0" << mi_mapa[i][j] << " "; }
                    else if (mi_mapa[i][j] >= 10) { cout << "00" << mi_mapa[i][j] << " "; }
                    else if (mi_mapa[i][j] >= 0) { cout << "000" << mi_mapa[i][j] << " "; }
                    else { cout << "----" << " "; }
                }
            }
            cout << "\n\n";
        }


    int cardinal_bueno = MejorCasilla();
    int hacia_donde = ElegirDireccion(cardinal_bueno);

    /*cout << "hacia donde = " << hacia_donde << endl;*/

    if (trufa_size_ > 5) { //S—lo recoge si hay m‡s de 5 trufas en esa casilla
        accion = actEXTRACT;
    } else if(trufa_size_ == -1) {
        accion = actSNIFF;
    } else if (hacia_donde == 0) {//RECTO!
        accion = actFORWARD;
    } else if (hacia_donde == 1) {//DERECHA
        accion = actTURN_R;
    } else if (hacia_donde == -1) {//IZQUIERDA
        accion = actTURN_L;
    } else { // SI ESTç A DOS GIROS
        accion = actTURN_L;
    }

    ult_accion_ = accion;
    turno_actual++;

	return accion;
}
// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	trufa_size_ = env.TrufaAmount();
	bump_ = env.isJustBump();
}
// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actSNIFF: return "SNIFF";
	case Agent::actEXTRACT: return "EXTRACT";
	case Agent::actIDLE: return "IDLE";
	default: return "???";
	}
}
