#ifndef __VECTOR_H__
#define __VECTOR_H__



class Vector3
{
public:

	Vector3()  { x = 0.0; y = 0.0; z = 0.0; }
	Vector3( float xx, float yy, float zz)
	{
		x = xx;
		y = yy;
		z = zz;
	}
	Vector3(const Vector3& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}
    

    inline float length();
    Vector3 normalize();
    float dotProduct(const Vector3& v);
    Vector3 crossProduct(const Vector3& v);
	void DirectionAngle(const Vector3 &v);
	

    //重载运算符
	Vector3 operator + (const Vector3& v);
	Vector3 operator - (const Vector3& v);
	Vector3 operator * (float scale);
	Vector3 operator / (float scale);
	Vector3 operator - ();
	
public:
	  float x,y,z;
	  float cx,cy,cz;

};


/*class Vector2
{
public:
	/** 构造函数 */
	/*Vector2(float xx = 0.0,float yy = 0.0) { x = xx; y = yy;  }
	Vector2(const Vector2& v)
	{
		x = v.x;
		y = v.y;
	}

public:
	float x,y;
};
*/

#endif //__VECTOR_H__
