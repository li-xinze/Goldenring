#include"MDLModel.h"
#include <QGLWidget>
#include <gl/gl.h>
#include <gl/glu.h>
#include<glut.h>
#include<QKeyEvent>
extern bool	   keys[256];	

class CMDLOBJ : public QGLWidget
{
    Q_OBJECT
public:
	CMDLOBJ();
	virtual ~CMDLOBJ();
	unsigned int Animation[10];
	TMDLModel	MdlModel[10];
	int		Type;
	bool	Anim_Fin[10];
	
	int		LBDown; //鼠标左键是否按下
	int		RBDown;
	int		Key_RDown;
	int		Key_1Down;
	int		Key_2Down;
	int		Key_3Down;
	int		Key_4Down;
	 
	int		InitGL(int a,char* na);  //初始化单个MDL模型
    //bool	render();
	void	DrawModels(float x,float y,float z,int a,float size,float rz,float ry);

     //绘制指定模型 入参 坐标 模型数组下标 缩放倍数 水平角 仰角



};

