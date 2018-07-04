#pragma once
    
#include "..\vmath\vfmesh.h"
#include "..\vstd\tisys.h"

namespace VNALGMESH
{   
    struct VSPathTerminal
    {
        VSMeshPoint  mpBegin ;
        VSMeshPoint  mpEnd   ;
    } ; 

    typedef VSConstBuffer< VSMeshPoint > IVSurfPath ;

    struct VSSbrBall
    {
        unsigned    stTriangle   ;  // 中心三角片
        VFVECTOR3   vCenter      ;  // 球心
        float       sqrR         ;  // 搜索半径的平方
        VSConstBuffer< VFVECTOR3 > vertices ;
    } ;

    struct VSSbrThrshld : VSConstBuffer< double >
    {
        unsigned    stTriangle   ;  // 中心三角片
        float       threshould   ;
    } ;

    struct VSSubMesh : VSSimpleGraph //: VTopoGraph
    {
        //// pData1: triangles , pData2: map to surface of src mesh
        //VSConstBuffer< VNVECTOR3UI , unsigned > mapSuface  ; // 
        //// pData : map to vertices of src mesh
        //VSConstBuffer< unsigned     > mapVertice ; //
        const unsigned * mapSurface  ; // Length = surface count ;
        const unsigned * mapVerteice ; // Length = vertex  count ; 
    } ;

    struct VSMeshGeodic
    {
        VSConstBuffer< float > lstDist ;
    } ;

    struct  VSCtrlPoint
    {
        unsigned  nIndx;
        float     fRadius;
        VFVECTOR3 posDest;
    }; 
    
    struct VSPointOnEdge
    {
        unsigned   EdgeIndx  ;      //曲线点所在的边列表
        float      Alpha     ;   
    } ;

    typedef VSConstBuffer< unsigned      > VSMeshVertLine ; // 由顶点连接起来的曲面上的曲线
    //typedef VSConstBuffer< VSPointOnEdge > VSCurveOnMesh  ;

    struct VSCurveOnMesh
    {
        VSConstBuffer< unsigned      > circles    ;  // Len：环的个数+1，pData: 每个环起始位置
        VSConstBuffer< VSPointOnEdge > edgePoints ;  // 所有环的点
    } ;

    // New Structure 
    VD_DEFRELATION( VRPerfMesh       , VSSimpleMeshF                                         ,  VSPerfectMesh   ) ;
    VD_DEFRELATION( VRSurfPath       , VI_AND< VSPerfectMesh   , VSPathTerminal            > ,  IVSurfPath      ) ;
    VD_DEFRELATION( VRPerfGraph      , VSSimpleGraph                                         ,  VSPerfTopoGraph ) ;
    VD_DEFRELATION( VRSubMesh        , VI_AND< VSPerfTopoGraph , VSSbrBall                 > ,  VSSubMesh       ) ;
    VD_DEFRELATION( VRGeodicMesh     , VI_AND< VSGraphMesh     , VSConstBuffer< unsigned > > ,  VSMeshGeodic    ) ;
    VD_DEFRELATION( VRPointPatch     , VI_AND< VSGraphMesh     , VSCtrlPoint               > ,  VSGraphMesh     ) ; 
    VD_DEFRELATION( VRSubMeshThrs    , VI_AND< VSPerfTopoGraph , VSSbrThrshld              > ,  VSSubMesh       ) ;
    VD_DEFRELATION( VRRefineTooth    , VSSimpleMeshF                                         ,  VSSimpleMeshF   ) ;

    using IVDSGenPerfMesh     = IVSysDynamic< VRPerfMesh       > ;
    using IVDSFindMeshPath    = IVSysDynamic< VRSurfPath       > ;
    using IVDSGenGraph        = IVSysDynamic< VRPerfGraph      > ;
    using IVDSSubtractor      = IVSysDynamic< VRSubMesh        > ;
    using IVDSGenGeodesic     = IVSysDynamic< VRGeodicMesh     > ;
    using IVDSPointShaper     = IVSysDynamic< VRPointPatch     > ;
    using IVDSSubtractorThrs  = IVSysDynamic< VRSubMeshThrs    > ;
    using IVDSToothRefine     = IVSysDynamic< VRRefineTooth    > ;
 } ;