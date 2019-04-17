// baiscobj.h: interface for the baiscobj class.
//
//////////////////////////////////////////////////////////////////////
/*
#if !defined(AFX_BAISCOBJ_H__6F90C6A0_F5E4_4482_BA6B_136D5C922B31__INCLUDED_)
#define AFX_BAISCOBJ_H__6F90C6A0_F5E4_4482_BA6B_136D5C922B31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<QKeyEvent>

class baiscobj  
{
public:
	baiscobj();
	virtual ~baiscobj();
public:
		int			m_Time,m_Fram;
private:GLdouble	g_eye[3];		//视点
        GLdouble	g_look[3];		//目标点
        float		rad_xz;	        //角度
        float		g_Angle;        //方位角
        float		g_elev;	        //俯仰角
        UINT g_cactus[16];
		GLUquadricObj *g_text; 
public:	GLvoid		DrawGround();
        BOOL		DisplayScene(QKeyEvent *event);	         //摄像漫游
		void		light0();
};

#endif // !defined(AFX_BAISCOBJ_H__6F90C6A0_F5E4_4482_BA6B_136D5C922B31__INCLUDED_)
*/
