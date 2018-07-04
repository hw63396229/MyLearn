#ifndef __SCCMN_VMATH_VECTOR3_H__
#define __SCCMN_VMATH_VECTOR3_H__

#include "vmathpredef.h"
#include <math.h>
#include "../vstd/dstrm.h"

typedef struct VFVector3 
{
    float x ;
    float y ;
    float z ;

    // =====================================
    // Constructors
    // =====================================
    VFVector3() ; 
    VFVector3( float _x, float _y, float _z) ;
    VFVector3( const float * f );
    VFVector3( const VFVector3 & src ) ; 
    //VFVector3( VFVector3 && src );                 // move constructor  

    const float * Ptr() const ;
    float * Ptr() ;

    const VFVector3 & operator=( VFVector3 const& src ) ; // copy assignment operator  

    // =====================================
    // Access grants
    // =====================================
    const float&operator[]( unsigned i) const;
    float&operator[]( unsigned i) ;  

    // =====================================
    // operators
    // =====================================
    VFVector3& operator += (const VFVector3& v);
    VFVector3& operator -= (const VFVector3& v);
    VFVector3& operator *= (const VFVector3& v);
    VFVector3& operator /= (const VFVector3& v);
    VFVector3& operator *= (float s);
    VFVector3& operator /= (float s); 
    
    friend VFVector3    operator + ( const VFVector3  & v ) ;
    //friend VFVector3 && operator + ( VFVector3 && v ) ; 
    friend VFVector3    operator - ( const VFVector3  & v ) ;  
    //friend VFVector3 && operator + ( VFVector3 && v ) ; 

    friend VFVector3    operator +  ( const VFVector3  & x , const VFVector3  & v )  ;
    //friend VFVector3 && operator +  ( const VFVector3 & x , VFVector3 && v )  ;
    //friend VFVector3 && operator +  ( VFVector3 && v , const VFVector3 & x )  ;
    //friend VFVector3 && operator +  ( VFVector3 && v , VFVector3 && x )  ;

    friend VFVector3    operator -  ( const VFVector3  & x , const VFVector3  & v )  ;
    //friend VFVector3 && operator -  ( const VFVector3 & x , VFVector3 && v )  ;
    //friend VFVector3 && operator -  ( VFVector3 && v , const VFVector3 & x )  ;
    //friend VFVector3 && operator -  ( VFVector3 && v , VFVector3 && x )  ;
       
    void MakeFloor( const VFVector3 & cmp ) ;
    void MakeCeil ( const VFVector3 & cmp ) ;

    VFVector3 operator *  ( float s ) const ;
    VFVector3 operator * ( const VFVector3 & rhs) const ; // ע���ǲ�� ,�����( x1 * x2 , y1 * y2 , z1 * z2 ) ; 
    VFVector3 operator /  ( float s ) const ; 

    bool             operator <  ( const VFVector3 & v ) const ;
    bool             operator <= ( const VFVector3 & v ) const ;
    bool             operator >  ( const VFVector3 & v ) const ;
    bool             operator >= ( const VFVector3 & v ) const ;
    bool             operator == ( const VFVector3 & v ) const ;
    bool             operator != ( const VFVector3 & v ) const ;

    friend VFVector3    operator * ( float s, const VFVector3 &  v ) ;  
    //friend VFVector3 && operator * ( float s, VFVector3 && v ) ;  

    float      Dot         ( const VFVector3& v ) const ; // ���
    float      AbsDot      ( const VFVector3& v ) const ; // |x1*x2| + |y1*y2| + |z1*z2| 

    VFVector3  Cross( const VFVector3 & v )     const ; // ��� 
    VFVector3  operator / ( const VFVector3& v )  const ; // (x1/x2,y1/y2,z1/z2)

    float      Magnitude   ()                      const ; // ģ��
    float      SqrMagnitude()                      const ; // ģ��ƽ��
    VFVector3  Direction    ()                      const ; // ����, ��λ������Լ�
    void        Normalize  ()                            ; // ��λ��
    //VFVector3  ToNormal    ()                      const ; // ���ɵ�λ������
    VFVector3  GetOrthoVector()            const ; // ����һ�����Լ���ֱ������
    VFVector3  GetOrthoNormal()            const ; // ����һ�����Լ���ֱ�ĵ�λ����

    bool IsZero( float threshold = VF_EPS_2 ) const ;
    bool IsNormalized( float threshold = VF_EPS_2 ) const ; 

    static const VFVector3 ORIGIN     ;
    static const VFVector3 ZERO       ;
    static const VFVector3 AXIS_X     ;
    static const VFVector3 AXIS_Y     ;
    static const VFVector3 AXIS_Z     ;
    static const VFVector3 AXIS_NEG_X ;
    static const VFVector3 AXIS_NEG_Y ;
    static const VFVector3 AXIS_NEG_Z ;
    static const VFVector3 UNIT_SCALE ;
    static const VFVector3 VTBL[3]    ;
    static const VFVector3 NEG_VTBL[3];
    static const VFVector3 DIR_VTBL[6]; // ��EV_DIR_AXI_TYPE����
} VFVECTOR3 , * LPVFVECTOR3 ;


inline VDataOutput & operator <<( VDataOutput & dOut , const VFVECTOR3 & v )
{
    dOut << v.x << v.y << v.z ;

    return dOut ;
}

inline VDataInput & operator >>( VDataInput & dIn , VFVECTOR3 & v )
{
    dIn >> v.x >> v.y >> v.z ;

    return dIn ;
}


typedef const VFVECTOR3 *  LPCVFVECTOR3 ;

#include "vfvector3.inl"

#endif