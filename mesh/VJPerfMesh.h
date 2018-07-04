#pragma once

#include "VTopoMesh.h"
#include "..\vmath\vtopoutil.h"

class VJPerfMesh //: public TVPerfectMeshAdaptor< VSPerfectMesh > 
{
public :
    VJPerfMesh()
    {}
    ~VJPerfMesh(void)
    {}

    void Build( VSPerfectMesh & outVal , const VSSimpleMeshF & mp )
    { 
        m_graph.Rebuild(mp.nVertCount, mp.nTriangleCount, mp.pTriangles);

        VFVECTOR3 norm(VFVECTOR3::ZERO);
        unsigned              VC = mp.nVertCount;
        unsigned              TC = mp.nTriangleCount;
        const VFVECTOR3     * pVerts = mp.pVertices;
        const VNVECTOR3UI   * pSurf = mp.pTriangles;

        m_lstVertNormals.resize(VC);
        m_lstSurfNormals.resize(TC);

        //

        for (unsigned i = 0; i < VC; i++)
            m_lstVertNormals[i] = VTopoGraphUtil::CalcVertexNormal(m_graph, pVerts, pSurf, i);

        for (unsigned i = 0; i < TC; i++)
            m_lstSurfNormals[i] = VTopoGraphUtil::CalcSurfaceNormal(pSurf[i], pVerts);

        //{
        //    ZeroMemory( & m_lstVertNormals[0] , sizeof( VFVECTOR3 ) * VC ) ;
        //    for( unsigned i = 0 ; i < TC ; i ++ )
        //    { 
        //        const VNVECTOR3UI & tri = pSurf[i] ; 
        //        VFVECTOR3 & nOut = m_lstSurfNormals[i] ;
        //        const VFVECTOR3 & v0 = pVerts[tri[0]] ;
        //        const VFVECTOR3 & v1 = pVerts[tri[1]] ;
        //        const VFVECTOR3 & v2 = pVerts[tri[2]] ;
        //        VFVECTOR3 u01( v1 - v0 ) , u12( v2 - v1 ) , u20( v0 - v2 ) ;
        //        if( u01.IsZero(0) || u12.IsZero(0) || u20.IsZero(0) ) 
        //        {
        //            //ATLTRACE( "ÓÐ»û±äÈý½ºÆ¬£¡\r\n" ) ;
        //            VASSERT(0); 
        //            return ;
        //        }  
        //        u01.Normalize() ; 
        //        u12.Normalize() ; 
        //        u20.Normalize() ;  
        //        nOut = u01.Cross( u12 ) ; 
        //        if( nOut.IsZero(0) )
        //        {   
        //            VASSERT(0);
        //            return ;
        //        }
        //        nOut.Normalize() ; 
        //        VFVECTOR3 & vOut0 = m_lstVertNormals[tri[0]] ;
        //        VFVECTOR3 & vOut1 = m_lstVertNormals[tri[1]] ;
        //        VFVECTOR3 & vOut2 = m_lstVertNormals[tri[2]] ; 
        //        vOut0 += nOut * acosf( - u01.Dot( u20 ) ) ;
        //        vOut1 += nOut * acosf( - u12.Dot( u01 ) ) ;
        //        vOut2 += nOut * acosf( - u20.Dot( u12 ) ) ;
        //    } 
        //    for( unsigned i = 0 ; i < VC ; i ++ )
        //    {
        //        if( m_lstVertNormals[i].IsZero() ) 
        //            return ; 
        //        m_lstVertNormals[i].Normalize() ;
        //    } ;
        //}
         
        outVal = TVPerfectMeshAdaptor< VSPerfectMesh >( m_graph , mp.pTriangles , mp.pVertices
                                                      , VD_V2CB( m_lstVertNormals ).pData
                                                      , VD_V2CB( m_lstSurfNormals ).pData );
    } 

private : 
    VTopoMesh                     m_graph           ;
    std::vector< VFVECTOR3 >      m_lstVertNormals  ;
    std::vector< VFVECTOR3 >      m_lstSurfNormals  ; 
} ;   
