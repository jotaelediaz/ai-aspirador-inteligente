#ifndef AGENT__
#define AGENT__
#include <vector>
#include <string>
using namespace std;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent(){
        trufa_size_=-1;
        bump_=false;
        orientacion_ = 0;
        ult_accion_ = actIDLE;

        x_actual = 9;
        y_actual = 9;

        turno_actual = 1;

        for(int i=0; i<4; i++) {
            obstaculo_[i] = false;
        }

        for(int i=0; i<20; i++) {
            for(int j=0; j<20; j++) {
                mi_mapa[i][j] = 0;
            }
        }
	}

	enum ActionType
	{
	    actFORWARD,
	    actTURN_L,
	    actTURN_R,
	    actSNIFF,
	    actEXTRACT,
	    actIDLE
	};

	void Perceive(const Environment &env);
	ActionType Think();

	void AsignarObstaculo();
	void AvanzarCasilla();
    int MejorCasilla();
    int ElegirDireccion(int ori_deseada);

private:
	int trufa_size_;
	bool bump_;

	int orientacion_;
	bool obstaculo_[4];
	ActionType ult_accion_;
    int mi_mapa[20][20];
    int x_actual;
    int y_actual;
    int turno_actual;
};

string ActionStr(Agent::ActionType);

#endif
