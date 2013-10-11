import FWCore.ParameterSet.Config as cms

StripTrackingRecHitsValid = cms.EDAnalyzer("SiStripTrackingRecHitsValid",
    outputFile = cms.string('striptrackingrechitshisto.root'),
    OutputMEsInRootFile = cms.bool(True),
    TopFolderName = cms.string('Tracking/TrackingRecHits/'),

    TH1Errx_LF = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(0.005),
        layerswitchon  = cms.bool(True)
    ),

    TH1Errx_MF = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(0.5),
        layerswitchon  = cms.bool(True)
    ),

    TH1Res_LF = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-0.02),
        xmax           = cms.double(+0.02),
        layerswitchon  = cms.bool(True)
    ),

    TH1Res_MF = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-2.0),
        xmax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

    TH1Pull_LF = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-5.0),
        xmax           = cms.double(+5.0),
        layerswitchon  = cms.bool(True)
    ),

    TH1Pull_MF = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-5.0),
        xmax           = cms.double(+5.0),
        layerswitchon  = cms.bool(True)
    ),

    TH1Category = cms.PSet(
        Nbinx          = cms.int32(10),
        xmin           = cms.double(0.),
        xmax           = cms.double(10.0),
        layerswitchon  = cms.bool(True)
    ),

    TH1Trackwidth = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        layerswitchon  = cms.bool(True)
    ),

    TH1Expectedwidth = cms.PSet(
        Nbinx          = cms.int32(10),
        xmin           = cms.double(0.),
        xmax           = cms.double(10.0),
        layerswitchon  = cms.bool(True)
    ),

    TH1Clusterwidth= cms.PSet(
        Nbinx          = cms.int32(10),
        xmin           = cms.double(0.),
        xmax           = cms.double(10.0),
        layerswitchon  = cms.bool(True)
    ),

    TH1Trackanglealpha = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-100.0),
        xmax           = cms.double(+100.0),
        layerswitchon  = cms.bool(True)
    ),

    TH1Trackanglebeta = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-100.0),
        xmax           = cms.double(+100.0),
        layerswitchon  = cms.bool(True)
    ),

    TProfErrxMFTrackwidthProfile_WClus1 = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(0.),
        ymax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

    TProfErrxMFTrackwidthProfile_WClus2 = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(0.),
        ymax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

    TProfErrxMFTrackwidthProfile_WClus3 = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(0.),
        ymax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

    TProfErrxMFTrackwidthProfile_WClus4 = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(0.),
        ymax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

    TProfResMFTrackwidthProfile_WClus1 = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(0.),
        ymax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

    TProfResMFTrackwidthProfile_WClus2 = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(0.),
        ymax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

    TProfResMFTrackwidthProfile_WClus21 = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

    TProfResMFTrackwidthProfile_WClus22 = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-5.0),
        ymax           = cms.double(+5.0),
        layerswitchon  = cms.bool(True)
    ),

    TProfResMFTrackwidthProfile_WClus23 = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-0.5),
        ymax           = cms.double(+0.5),
        layerswitchon  = cms.bool(True)
    ),

     TProfResMFTrackwidthProfile_WClus3 = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(0.),
        ymax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

    TProfResMFTrackwidthProfile_WClus4 = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(0.),
        ymax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

    TProfErrxMFTrackwidthProfile = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(0.),
        ymax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

    TProfErrxMFTrackwidthProfile_Category1 = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

    TProfErrxMFTrackwidthProfile_Category2 = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

    TProfErrxMFTrackwidthProfile_Category3 = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

    TProfErrxMFTrackwidthProfile_Category4 = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

    TProfErrxMFClusterwidthProfile_Category1 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(10.),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

    TProfErrxMFAngleProfile = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(60.0),
        ymin           = cms.double(0.),
        ymax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1NstpRphi = cms.PSet(
        Nbinx          = cms.int32(20),
        xmin           = cms.double(0.5),
        xmax           = cms.double(20.5),
        layerswitchon  = cms.bool(True)
    ),

   TH1AdcRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(300.),
        layerswitchon  = cms.bool(True)
    ),

   TH1PosxRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-6.0),
        xmax           = cms.double(+6.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1ErrxLFRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(0.005),
        layerswitchon  = cms.bool(True)
    ),

   TH1ErrxMFRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1ErrxMFRphiwclus1 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1ErrxMFRphiwclus2 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1ErrxMFRphiwclus3 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1ErrxMFRphiwclus4 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1ResLFRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-0.02),
        xmax           = cms.double(+0.02),
        layerswitchon  = cms.bool(True)
    ),

   TH1ResMFRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-2.0),
        xmax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1ResMFRphiwclus1 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-2.0),
        xmax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1ResMFRphiwclus2 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-2.0),
        xmax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1ResMFRphiwclus3 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-2.0),
        xmax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1ResMFRphiwclus4 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-2.0),
        xmax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1PullLFRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-5.0),
        xmax           = cms.double(+5.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1PullMFRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-5.0),
        xmax           = cms.double(+5.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1PullMFRphiwclus1 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-2.0),
        xmax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1PullMFRphiwclus2 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-2.0),
        xmax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1PullMFRphiwclus3 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-2.0),
        xmax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1PullMFRphiwclus4 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-2.0),
        xmax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1TrackangleRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-20.0),
        xmax           = cms.double(+20.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1TrackanglebetaRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-20.0),
        xmax           = cms.double(+20.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1Trackangle2Rphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-20.0),
        xmax           = cms.double(+20.0),
        layerswitchon  = cms.bool(True)
    ),

    TProfPullTrackangleProfileRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-20.0),
        xmax           = cms.double(+20.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1PullTrackangle2DRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(1.0),
        layerswitchon  = cms.bool(True)
    ),

  TH1TrackwidthRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(1.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1ExpectedwidthRphi = cms.PSet(
        Nbinx          = cms.int32(10),
        xmin           = cms.double(0.),
        xmax           = cms.double(10.),
        layerswitchon  = cms.bool(True)
    ),

    TH1ClusterwidthRphi = cms.PSet(
        Nbinx          = cms.int32(10),
        xmin           = cms.double(0.),
        xmax           = cms.double(10.),
        layerswitchon  = cms.bool(True)
    ),

   TH1CategoryRphi = cms.PSet(
        Nbinx          = cms.int32(10),
        xmin           = cms.double(0.),
        xmax           = cms.double(10.),
        layerswitchon  = cms.bool(True)
    ),

   TProfPullTrackwidthProfileRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

   TProfPullTrackwidthProfileRphiwclus1 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

   TProfPullTrackwidthProfileRphiwclus2 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

   TProfPullTrackwidthProfileRphiwclus3 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

   TProfPullTrackwidthProfileRphiwclus4 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

   TProfPullTrackwidthProfileCategory1Rphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(1.),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfPullTrackwidthProfileCategory2Rphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(1.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfPullTrackwidthProfileCategory3Rphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(1.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfPullTrackwidthProfileCategory4Rphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(1.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfErrxMFTrackwidthProfileRphi = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(8.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfErrxMFTrackwidthProfileWclus1Rphi = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfErrxMFTrackwidthProfileWclus2Rphi = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfErrxMFTrackwidthProfileWclus3Rphi = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfErrxMFTrackwidthProfileWclus4Rphi = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfResMFTrackwidthProfileWclus1Rphi = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfResMFTrackwidthProfileWclus2Rphi = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfResMFTrackwidthProfileWclus3Rphi = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfResMFTrackwidthProfileWclus4Rphi = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfErrxMFTrackwidthProfileCategory1Rphi = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfErrxMFTrackwidthProfileCategory2Rphi = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfErrxMFTrackwidthProfileCategory3Rphi = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfErrxMFTrackwidthProfileCategory4Rphi = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfErrxMFAngleProfileRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(1.0),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfErrxMFClusterwidthProfileCategory1Rphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(10.),
        ymin           = cms.double(-2.0),
        ymax           = cms.double(+2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfrapidityResProfilewclus1 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-2.5),
        xmax           = cms.double(+2.5),
        ymin           = cms.double(0.0),
        ymax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfrapidityResProfilewclus2 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-2.5),
        xmax           = cms.double(+2.5),
        ymin           = cms.double(0.0),
        ymax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfrapidityResProfilewclus3 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-2.5),
        xmax           = cms.double(+2.5),
        ymin           = cms.double(0.0),
        ymax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

  TProfrapidityResProfilewclus4 = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-2.5),
        xmax           = cms.double(+2.5),
        ymin           = cms.double(0.0),
        ymax           = cms.double(2.0),
        layerswitchon  = cms.bool(True)
    ),

  TH1NstpSas = cms.PSet(
        Nbinx          = cms.int32(20),
        xmin           = cms.double(0.5),
        xmax           = cms.double(20.5),
        layerswitchon  = cms.bool(True)
    ),

  TH1AdcSas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(300.),
        layerswitchon  = cms.bool(True)
    ),

  TH1PosxSas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-6.0),
        xmax           = cms.double(+6.0),
        layerswitchon  = cms.bool(True)
    ),

  TH1ErrxLFSas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(0.005),
        layerswitchon  = cms.bool(True)
    ),

  TH1ErrxMFSas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(0.5),
        layerswitchon  = cms.bool(True)
    ),

  TH1ResLFSas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-0.02),
        xmax           = cms.double(+0.02),
        layerswitchon  = cms.bool(True)
    ),

  TH1ResMFSas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-2.),
        xmax           = cms.double(+2.),
        layerswitchon  = cms.bool(True)
    ),

  TH1PullLFSas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-4.),
        xmax           = cms.double(+4.),
        layerswitchon  = cms.bool(True)
    ),

  TH1PullMFSas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-4.),
        xmax           = cms.double(+4.),
        layerswitchon  = cms.bool(True)
    ),

  TH1TrackangleSas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-40.),
        xmax           = cms.double(+40.),
        layerswitchon  = cms.bool(True)
    ),

  TH1TrackanglebetaSas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-40.),
        xmax           = cms.double(+40.),
        layerswitchon  = cms.bool(True)
    ),

  TProfPullTrackangleProfileSas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-40.),
        xmax           = cms.double(+40.),
        ymin           = cms.double(-4.),
        ymax           = cms.double(+4.),
        layerswitchon  = cms.bool(True)
    ),

  TH1TrackwidthSas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(1.),
        layerswitchon  = cms.bool(True)
    ),

  TH1ExpectedwidthSas = cms.PSet(
        Nbinx          = cms.int32(10),
        xmin           = cms.double(0.),
        xmax           = cms.double(10.),
        layerswitchon  = cms.bool(True)
    ),

  TH1ClusterwidthSas = cms.PSet(
        Nbinx          = cms.int32(10),
        xmin           = cms.double(0.),
        xmax           = cms.double(10.),
        layerswitchon  = cms.bool(True)
    ),

  TH1CategorySas = cms.PSet(
        Nbinx          = cms.int32(10),
        xmin           = cms.double(0.),
        xmax           = cms.double(10.),
        layerswitchon  = cms.bool(True)
    ),

  TProfPullTrackwidthProfileSas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(1.),
        ymin           = cms.double(-2.),
        ymax           = cms.double(+2.),
        layerswitchon  = cms.bool(True)
    ),

  TProfPullTrackwidthProfileCategory1Sas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(1.),
        ymin           = cms.double(-2.),
        ymax           = cms.double(+2.),
        layerswitchon  = cms.bool(True)
    ),

  TProfPullTrackwidthProfileCategory2Sas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(1.),
        ymin           = cms.double(-2.),
        ymax           = cms.double(+2.),
        layerswitchon  = cms.bool(True)
    ),

  TProfPullTrackwidthProfileCategory3Sas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(1.),
        ymin           = cms.double(-2.),
        ymax           = cms.double(+2.),
        layerswitchon  = cms.bool(True)
    ),

  TProfPullTrackwidthProfileCategory4Sas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(1.),
        ymin           = cms.double(-2.),
        ymax           = cms.double(+2.),
        layerswitchon  = cms.bool(True)
    ),

  TProfErrxMFTrackwidthProfileSas = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.),
        ymin           = cms.double(-2.),
        ymax           = cms.double(+2.),
        layerswitchon  = cms.bool(True)
    ),

  TProfErrxMFTrackwidthProfileCategory1Sas = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.),
        ymin           = cms.double(-2.),
        ymax           = cms.double(+2.),
        layerswitchon  = cms.bool(True)
    ),

  TProfErrxMFTrackwidthProfileCategory2Sas = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.),
        ymin           = cms.double(-2.),
        ymax           = cms.double(+2.),
        layerswitchon  = cms.bool(True)
    ),

  TProfErrxMFTrackwidthProfileCategory3Sas = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.),
        ymin           = cms.double(-2.),
        ymax           = cms.double(+2.),
        layerswitchon  = cms.bool(True)
    ),

  TProfErrxMFTrackwidthProfileCategory4Sas = cms.PSet(
        Nbinx          = cms.int32(12),
        xmin           = cms.double(0.),
        xmax           = cms.double(4.),
        ymin           = cms.double(-2.),
        ymax           = cms.double(+2.),
        layerswitchon  = cms.bool(True)
    ),

  TProfErrxMFAngleProfileSas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(1.),
        ymin           = cms.double(-2.),
        ymax           = cms.double(+2.),
        layerswitchon  = cms.bool(True)
    ),

  TProfErrxMFClusterwidthProfileCategory1Sas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(10.),
        ymin           = cms.double(-2.),
        ymax           = cms.double(+2.),
        layerswitchon  = cms.bool(True)
    ),

  TH1PosxMatched = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-6.0),
        xmax           = cms.double(+6.0),
        layerswitchon  = cms.bool(True)
    ),

  TH1PosyMatched = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-6.0),
        xmax           = cms.double(+6.0),
        layerswitchon  = cms.bool(True)
    ),

  TH1ErrxMatched = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(0.05),
        layerswitchon  = cms.bool(True)
    ),

  TH1ErryMatched = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(0.05),
        layerswitchon  = cms.bool(True)
    ),

  TH1ResxMatched = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-0.02),
        xmax           = cms.double(+0.02),
        layerswitchon  = cms.bool(True)
    ),

  TH1ResyMatched = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-1.),
        xmax           = cms.double(+1.),
        layerswitchon  = cms.bool(True)
    ),

  TH1PullxMatched = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-5.),
        xmax           = cms.double(+5.),
        layerswitchon  = cms.bool(True)
    ),

  TH1PullyMatched = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-5.),
        xmax           = cms.double(+5.),
        layerswitchon  = cms.bool(True)
    ),

    trajectoryInput = cms.InputTag("generalTracks"),
    associatePixel = cms.bool(False),
    ROUList = cms.vstring('g4SimHitsTrackerHitsTIBLowTof', 
			'g4SimHitsTrackerHitsTIBHighTof', 
			'g4SimHitsTrackerHitsTIDLowTof', 
			'g4SimHitsTrackerHitsTIDHighTof', 
			'g4SimHitsTrackerHitsTOBLowTof', 
			'g4SimHitsTrackerHitsTOBHighTof', 
			'g4SimHitsTrackerHitsTECLowTof', 
			'g4SimHitsTrackerHitsTECHighTof'),
    associateRecoTracks = cms.bool(False),
    #	string trajectoryInput = "rsWithMaterialTracks"
    associateStrip = cms.bool(True)
)


