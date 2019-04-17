#include "DynamicMDL.h"
#include"QDebug"


//Static3DS* Static3DS::m_pStatic3DS = NULL;

DynamicMDL::DynamicMDL()
{
	//m_pStatic3DS = this;	
}
DynamicMDL::~DynamicMDL()
{
}
bool DynamicMDL::init(int a)
{
    switch(a){
    case 1:
        m_MDLOBJ.InitGL(1,"C:/mdl/vip.mdl");
        break;
    case 2:
        m_MDLOBJ.InitGL(2,"C:/mdl/aflock.mdl");
        break;
    case 3:
        m_MDLOBJ.InitGL(3,"C:/mdl/vip.mdl");
        break;
    default:
        break;
    }
    qDebug()<<"load the mdl file";
    return true ;
}
bool DynamicMDL::render(int a, float x, float y, float z, float rz, float Moved)
{
    switch(a){
    case 1:{
        glPushMatrix();
        glLoadIdentity();
        m_MDLOBJ.DrawModels(0.0,-0.02,-0.5,1,0.004f,90,0);
        glPopMatrix();
         qDebug()<<"q";
        break;
    }
    case 2:{
          /* long current =  m_MDLOBJ.MdlModel[2].GetSequence();
           if(current != 2.0 && Moved ==2.0){
           m_MDLOBJ.MdlModel[2].SetSequence(4);
           }
           if(current != 1.0 && Moved ==1.0){
           m_MDLOBJ.MdlModel[2].SetSequence(4);
           }*/
        glPushMatrix();
        qDebug()<<"q2";
        m_MDLOBJ.DrawModels(-24.0,5.0,45.0,2,0.4f,0,0);
        glPopMatrix();
        break;
    }
    case 3:{
          long current =  m_MDLOBJ.MdlModel[3].GetSequence();
           if(current != 2.0 && Moved ==2.0){
           m_MDLOBJ.MdlModel[3].SetSequence(4);
           }
           if(current != 1.0 && Moved ==1.0){
           m_MDLOBJ.MdlModel[3].SetSequence(4);
           }
        glPushMatrix();
        qDebug()<<"q2";
        m_MDLOBJ.DrawModels(x,y-0.02,z-0.5,3,0.004f,90+rz,0);
        glPopMatrix();
        break;
    }
   default:
        break;
    }
	return true ;
}
void DynamicMDL::MOUSEPRESS(){
    long currents;
    currents =  m_MDLOBJ.MdlModel[2].GetSequence();
     if(currents == 1){
         m_MDLOBJ.MdlModel[2].SetSequence(5);
}
}
void DynamicMDL::afterhit(){
    long currents;
    currents =  m_MDLOBJ.MdlModel[2].GetSequence();
    if(currents == 5){
        m_MDLOBJ.MdlModel[2].SetSequence(1);
}
}
void DynamicMDL::change_model_press(int a){
    long currents;
    currents =  m_MDLOBJ.MdlModel[a].GetSequence();
    if(currents != 4){
        m_MDLOBJ.MdlModel[a].SetSequence(4);
}
}
void DynamicMDL::change_model_release( int a){

        m_MDLOBJ.MdlModel[a].SetSequence(1);
}
