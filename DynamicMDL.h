#include "Vector.h"
#include"CMDLOBJ.h"

class DynamicMDL
{
public:
	DynamicMDL();
	~DynamicMDL();
    bool init(int a);
    bool render(int a,float x,float y,float z,float rz,float Moved);
    CMDLOBJ	m_MDLOBJ;
    void change_model_press(int a);
    void change_model_release(int a);
    void MOUSEPRESS();
    void afterhit();

private:
	//static Static3DS  *m_pStatic3DS;    

     //TMDLModel	MdlModel[10];


};

