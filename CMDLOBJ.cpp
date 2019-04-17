#include "MDLModel.h"
#include "CMDLOBJ.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction

//////////////////////////////////////////////////////////////////////////
CMDLOBJ::CMDLOBJ()
{

	Type = 0 ;
	LBDown = 0;
	RBDown = 0;
	Key_RDown = 0;
	Key_1Down = 0;
	Key_2Down = 0;
	Key_3Down = 0;
	Key_4Down = 0;
}
CMDLOBJ::~CMDLOBJ()
{
}
/////////////////////////////////////////////////////////////////////
//初始化

int CMDLOBJ::InitGL(int a,char* na)	
{	
	
	MdlModel[a].Init(na);
    MdlModel[a].SetSequence(1);
	Animation[a]=0;
	Anim_Fin[a] = true;
	return TRUE;							// Initialization Went OK
}


//绘制模型
void CMDLOBJ::DrawModels(float x,float y,float z,int a,float size,float rz,float ry)
{
	glPushMatrix();
	glEnable(GL_LIGHT0); 
	//glEnable(GL_LIGHTING);            
	glEnable(GL_TEXTURE_2D);     
	//移动到指定坐标
	glTranslatef(x, y, z);
	glScalef(size,size,size);	//缩放
	//旋转
    glRotated(-90,1.0f,0.0f,0.0f);
	//水平角
    glRotated(rz,0.0f,0.0f,1.0f);
	//仰角
    //glRotated(-ry*2/3-5,0.0f,1.0f,0.0f);
    glRotated(-ry*2/3-5,0.0f,1.0f,0.0f);

	//刷新当前动作序列的帧
    MdlModel[a].AdvanceFrame2();

	//绘制
	MdlModel[a].DrawModel();///////////////

    /*if(Animation[a]==1)
	{
		Animation[a]=0;
		MdlModel[a].SetSequence(0);
	}
	if(Animation[a]>0) 
        Animation[a]--;*/

	glPopMatrix();
}


/*bool CMDLOBJ::init(Camera  *m_Camera)
{
	this->m_Camera = m_Camera;
		//导入骨骼初始化
	InitGL(5,"data/mdl/aflock.mdl");
	InitGL(4,"data/mdl/qiang4.mdl");	//导入骨骼初始化
	InitGL(3,"data/mdl/knife.mdl");	//导入刀子
	InitGL(2,"data/mdl/qiang2.mdl");	//导入冲锋枪
	InitGL(1,"data/mdl/qiang1.mdl");	//导入手枪
	EnemyCount = MAX_ENEMY;
	
    Type = 1 ;
	InitEnemy();
	return TRUE ;
}

{
	Vector3 v;
	for (int i = 0;i<MAX_ENEMY;i++)
	{
		for(int j = Bullet.speed;j>-Bullet.speed;j--)
		{
			v.x = Enemy[i].x-Bullet.x+j*Bullet.cx;
			v.y = Enemy[i].y-Bullet.y+j*Bullet.cy;
			v.z = Enemy[i].z-Bullet.z+j*Bullet.cz;
			if (sqrt(v.dotProduct(v))<1)
			{
				Bullet.x=Enemy[i].x;
				Bullet.y=Enemy[i].y;
				Bullet.z=Enemy[i].z;
				Enemy[i].x=0;
				Enemy[i].y=0;
				Enemy[i].z=0;
				EnemyCount--;
				if (EnemyCount==0)
				{
					InitEnemy();
				}
				return true;
			}
		}
	}
	return false;
}
*/
/*bool CMDLOBJ::renderEnemy()
{
	for (int i = 0;i<MAX_ENEMY;i++)
	{
		glPushMatrix();
		//glTranslatef(Enemy[i].x,Enemy[i].y,Enemy[i].z);
		//glDisable(GL_TEXTURE_2D);
		//auxSolidTeapot(1);

		DrawModels(Enemy[i].x,Enemy[i].y,Enemy[i].z,5,0.1,0,0);
		
		glPopMatrix();
	}
	return true;

}
bool CMDLOBJ::render()
{
	bool first = false;
	//DrawModels(760,4,-340,5,0.1f,0,0);//怪物模型
	
	
	renderEnemy();
	if (LBDown==1)
	{	
		
		if(Anim_Fin[Type]==true) //换枪完毕才能攻击
			switch(Type)
			{
			case 1:
				if (Animation[Type]==0) //不能让子弹连发
				{	
					fire(1,5);
					Bullet.init(m_Camera->m_Position,m_Camera->m_View-m_Camera->m_Position);
					Bullet.shoot();
					sndPlaySound("data/sound/qiang1shoot.wav",SND_ASYNC);
				}
				break;
			case 2:
				if (Animation[Type]<25)  //冲锋枪的特殊待遇 哈哈
				{
					fire(2,1);
					Bullet.init(m_Camera->m_Position,m_Camera->m_View-m_Camera->m_Position);
					sndPlaySound("data/sound/qiang2shoot.wav",SND_ASYNC);
				}
				
				break;
			case 3:
				if (Animation[Type]==0)
				{
					fire(3,2);
					sndPlaySound("data/sound/knifehit.wav",SND_ASYNC);
				}
				break;
			case 4:
				if (Animation[Type]==0)
				{
					fire(4,1);
					Bullet.init(m_Camera->m_Position,m_Camera->m_View-m_Camera->m_Position);
					sndPlaySound("data/sound/qiang4shoot.wav",SND_ASYNC);
				}
				break;
				
			}
		//LBDown = 0;
		
	}
	if (Bullet.y<0||hitEnemy())
			{	
				//LBDown = false;
				if (Bullet.y<0)
				{
					Bullet.y=0; // 免得他在地下爆炸
					sndPlaySound("data/sound/hitground.wav",SND_ASYNC);
				}else
				{
					sndPlaySound("data/sound/hitobject.wav",SND_ASYNC);			
				}
				Bullet.Explosion(Bullet.x,Bullet.y,Bullet.z,20,0.2);//爆炸init代码
				Bullet.plosion();
				//枪声
				Bullet.y=2000; //清除子弹


			}
	if (RBDown==1)
	{	//fire(2,4);
		//sndPlaySound("data/sound/explode1.wav",SND_ASYNC);
		RBDown = 0;

	}

	if (keys[82]==true)		//R
	{	fire(2,4);
		//sndPlaySound("data/sound/explode1.wav",SND_ASYNC);
		RBDown = 0;

	}
	glPushMatrix();
	glLoadIdentity();
	//m_MDLOBJ.DrawModels(m_Camera.m_Position.x,m_Camera.m_Position.y,m_Camera.m_Position.z,1,0.02f,m_Camera.m_AngleX*300,m_Camera.m_AngleY*200);//怪物模型
	//DrawModels(0,0,-0.04,3,0.005f,40,0);//刀子
	
	for (int i=1;i<=4;i++)
	{
		if (keys[i+48]==true)
		{
			Type = i;
			first = true;
			Anim_Fin[Type] = false;
			break;
		}
	}

		switch(Type)  // 换枪
		{
		case 1:
			if (first)
			{
				fire(1,8);//手枪
				first = false;
			}
			if (!Anim_Fin[Type]&&Animation[1]==24)
			{
				sndPlaySound("data/sound/qiangdraw.wav",SND_ASYNC);
				
			}
			if (Animation[Type]==0)
					Anim_Fin[Type] = true;
			break;
		case 2:
			if (first)
			{
				fire(2,5);//手枪
				first = false;
			}
			if (!Anim_Fin[Type]&&Animation[Type]==24)
			{
				sndPlaySound("data/sound/qiangdraw.wav",SND_ASYNC);

			}
			if (Animation[Type]==0)
				Anim_Fin[Type] = true;
			 //冲锋枪
			
			break;
		case 3:
			if (first)
			{
				fire(3,3);
				first = false;
			}
			if (!Anim_Fin[Type]&&Animation[Type]==24)
			{
				sndPlaySound("data/sound/knifedraw.wav",SND_ASYNC);

			}
			if (Animation[Type]==0)
				Anim_Fin[Type] = true;
			
			break;
		case 4:
			if (first)
			{
				fire(4,6);
				first = false;
			}
			if (!Anim_Fin[Type]&&Animation[Type]==24)
			{
				sndPlaySound("data/sound/qiangdraw.wav",SND_ASYNC);

			}
			if (Animation[Type]==0)
				Anim_Fin[Type] = true;
//散弹枪
			break;
		}
		
	
	switch(Type)
	{
		
	case 1:
		DrawModels(0,0.3,-0.02,1,0.05f,50,5);//手枪   在这里复原
		break;
	case 2:
		DrawModels(0,0,-0.02,2,0.05f,50,0);//冲锋枪
		break;
	case 3:
		DrawModels(0,0,-0.02,3,0.05f,40,0);//刀子
		break;
	case 4:
		DrawModels(0,0,-0.02,4,0.05f,50,0);//双枪
		break;
	}
	
	glPopMatrix();

	//Bullet.render();
	return true ;
	
}*/
