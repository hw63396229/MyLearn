#pragma once
 
#include "VTopoMesh.h"

//
class VJPerfGraph //: public VSPerfTopoGraph 
{
public :
    VJPerfGraph()
    {}
    ~VJPerfGraph(void)
    {}

    void Build( VSPerfTopoGraph & outVal , const VSSimpleGraph & mp )
    { 
        m_graph.Rebuild( mp.nVertCount, mp.nTriangleCount, mp.pTriangles ) ;

        outVal = ( VSPerfTopoGraph & )( TVPerfTopoGraphAdaptor<VSPerfTopoGraph>( m_graph , mp.pTriangles ) ) ;
    }

private : 
    VTopoMesh                           m_graph ;
} ;
