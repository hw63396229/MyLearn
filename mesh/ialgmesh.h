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
        unsigned    stTriangle   ;  // ��������Ƭ
        VFVECTOR3   vCenter      ;  // ����
        float       sqrR         ;  // �����뾶��ƽ��
        VSConstBuffer< VFVECTOR3 > vertices ;
    } ;

    struct VSSbrThrshld : VSConstBuffer< double >
    {
        unsigned    stTriangle   ;  // ��������Ƭ
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
        unsigned   EdgeIndx  ;      //���ߵ����ڵı��б�
        float      Alpha     ;   
    } ;

    typedef VSConstBuffer< unsigned      > VSMeshVertLine ; // �ɶ������������������ϵ�����
    //typedef VSConstBuffer< VSPointOnEdge > VSCurveOnMesh  ;

    struct VSCurveOnMesh
    {
        VSConstBuffer< unsigned      > circles    ;  // Len�����ĸ���+1��pData: ÿ������ʼλ��
        VSConstBuffer< VSPointOnEdge > edgePoints ;  // ���л��ĵ�
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