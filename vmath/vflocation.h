#pragma once

#include "vfvector3.h"
#include "vfquaternion.h"
#include "VFMatrix4.h"

struct VFLocation
{
public:
    // construction
    VFLocation(){}
    VFLocation( const VFVECTOR3 & pos , const VFQuaternion & q )
        :position( pos ) , orientation( q ){}
    ~VFLocation(){}

public :
    VFLocation TransLocalPosToGlobal( const VFLocation & v ) const
    {
        VFLocation vRtn ;
        VFVECTOR3 vx , vy , vz ;

        vRtn.position = TransLocalVertexToGlobal( v.position ) ;
        
        vx = v.orientation * VFVECTOR3::AXIS_X ;
        vy = v.orientation * VFVECTOR3::AXIS_Y ;
        vz = v.orientation * VFVECTOR3::AXIS_Z ;


        vx = TransLocalNormalToGlobal( vx ) ;
        vy = TransLocalNormalToGlobal( vy ) ;
        vz = TransLocalNormalToGlobal( vz ) ;

        vRtn.orientation = VFQuaternion::FromAxes( vx , vy , vz ) ;

        return vRtn ;
    }

    VFLocation TransGlobalPosToLocal( const VFLocation & v ) const
    {
        VFLocation vRtn ;
        VFVECTOR3 vx , vy , vz ;

        vRtn.position = TransGlobalVertexToLocal( v.position ) ;
        
        vx = v.orientation * VFVECTOR3::AXIS_X ;
        vy = v.orientation * VFVECTOR3::AXIS_Y ;
        vz = v.orientation * VFVECTOR3::AXIS_Z ;

        vx = TransGlobalNormalToLocal( vx ) ;
        vy = TransGlobalNormalToLocal( vy ) ;
        vz = TransGlobalNormalToLocal( vz ) ;

       vRtn.orientation = VFQuaternion::FromAxes( vx , vy , vz ) ;

        return vRtn ;
    }

    VFVECTOR3 TransLocalVertexToGlobal( const VFVECTOR3 & v ) const
    {
        return position + orientation * v ; // orientation.Inverted() * ( v - position ) + position ;
    }

    VFVECTOR3 TransGlobalVertexToLocal( const VFVECTOR3 & v ) const
    {
        return orientation.Inverted() * ( v - position ) ; // orientation * ( v + position ) - position ;
    }

    VFVECTOR3 TransLocalNormalToGlobal( const VFVECTOR3 & v ) const
    {
        return orientation * v ;
    }

    VFVECTOR3 TransGlobalNormalToLocal( const VFVECTOR3 & v ) const
    {
        return orientation.Inverted() * v ;
    }

    //VFLocation CalcRelativeLocation( const VFLocation & v ) const
    //{
    //    VFLocation vRtn ;

    //    vRtn.position    = TransLocalNormalToGlobal( v.position - position ) ;
    //    vRtn.orientation = orientation.Inverted() * v.orientation ;

    //    return vRtn ;
    //} ;

    //VFLocation CalcGlobalLocation( const VFLocation & v ) const
    //{
    //    VFLocation vRtn ;

    //    vRtn.position    = TransGlobalNormalToLocal( v.position ) + position ;
    //    vRtn.orientation = orientation * v.orientation ;

    //    return vRtn ;
    //} ;

    VFMatrix4 ToMatrix4() const
    {
        VFMatrix4 mat4( orientation ) ;
        mat4.SetTrans( position ); 

        return mat4 ;
    }

    VFLocation Inverted() const
    {
        VFVECTOR3 v = orientation.Inverted() * (-position) ;
        return VFLocation( v , orientation.Inverted() ) ;
    }

    bool IsZero( float threshold = VF_EPS_2 ) const
    {
        return vf_equal_real( 1.f , orientation.w , threshold ) && position.IsZero( threshold ) ;
    }
       
    bool operator == ( const VFLocation & v ) const
    {
        return ( position == v.position && orientation == v.orientation ) ;
    }
       
    bool operator != ( const VFLocation & v ) const
    {
        return ( position != v.position || orientation != v.orientation ) ;
    }

	//! linear VFQuaternion interpolation
	static VFLocation Lerp( const VFLocation & L1 , const VFLocation & L2 , float t) 
	{ 
        VFLocation loc ;
        loc.position    = L1.position * ( 1 - t ) + L2.position * t ;
        loc.orientation = VFQuaternion::Lerp( L1.orientation , L2.orientation , t ) ;

        return loc ;
    }

    static VFLocation SLerp( const VFLocation & L1 , const VFLocation & L2 , float t )
    {
        VFLocation loc;
        loc.position = L1.position * ( 1 - t ) + L2.position * t;
        loc.orientation = VFQuaternion::SLerp( L1.orientation , L2.orientation , t );

        return loc;
    }

public :
    VFVECTOR3    position    ;
    VFQuaternion orientation ;

    // static variable 
    static const VFLocation ORIGIN ;
};

inline VDataOutput & operator <<( VDataOutput & stm , const VFLocation & ti )
{
    stm << ti.position << ti.orientation ;

    return stm ;
}

inline VDataInput & operator >>( VDataInput & stm , VFLocation & ti )
{
    stm >> ti.position >> ti.orientation ;

    return stm ;
}

