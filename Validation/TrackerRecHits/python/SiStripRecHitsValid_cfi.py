import FWCore.ParameterSet.Config as cms

stripRecHitsValid = cms.EDAnalyzer("SiStripRecHitsValid",
#    outputFile = cms.untracked.string('sistriprechitshisto.root'),
    outputFile = cms.string('sistriprechitshisto.root'),
    OutputMEsInRootFile = cms.bool(True),
    TopFolderName = cms.string('SiStrip/TrackerRecHits/'),
#    TopFolderName = cms.string('TrackerRecHitsV/TrackerRecHits/Strip/'),

    TH1NumTotRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(10000.),
        layerswitchon  = cms.bool(True)
   ),

    TH1NumTotSas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(10000.),
        layerswitchon  = cms.bool(True)
    ),

    TH1NumTotMatched = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(10000.),
        layerswitchon  = cms.bool(True)

    ),

  TH1NumRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(1000.),
        layerswitchon  = cms.bool(True)

    ),

  TH1NumSas = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(1000.),
        layerswitchon  = cms.bool(True)

    ),

  TH1NumMatched = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(1000.),
        layerswitchon  = cms.bool(True)

    ),

    TH1NstpRphi = cms.PSet(
        Nbinx          = cms.int32(20),
        xmin           = cms.double(-0.5),
        xmax           = cms.double(19.5),
        layerswitchon  = cms.bool(True)
    ),

    TH1AdcRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(500.),#300.
        layerswitchon  = cms.bool(True)
    ),

    TH1PosxRphi = cms.PSet(
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-6.0),#-6.0
        xmax           = cms.double(+6.0),#+6.0
        layerswitchon  = cms.bool(True)
    ),

    TH1ErrxRphi = cms.PSet( #<error>~20micron 
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(0.10),#0.01
        layerswitchon  = cms.bool(True)
    ),

    TH1ResRphi = cms.PSet( 
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-0.10),#-0.02
        xmax           = cms.double(+0.10),#+0.02
        layerswitchon  = cms.bool(True)
    ),

    TH1PullLFRphi = cms.PSet( 
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-10.),#-5.0
        xmax           = cms.double(+10.),#+5.0
        layerswitchon  = cms.bool(True)
    ),

    TH1PullMFRphi = cms.PSet( 
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-10.),#-5.0
        xmax           = cms.double(+10.),#+5.0
        layerswitchon  = cms.bool(True)
    ),

    TH1Chi2Rphi = cms.PSet( 
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(50.),
        layerswitchon  = cms.bool(True)
    ),

    TH1NstpSas = cms.PSet( 
        Nbinx          = cms.int32(20),
        xmin           = cms.double(-0.5),
        xmax           = cms.double(19.5),
        layerswitchon  = cms.bool(True)
    ),

    TH1AdcSas = cms.PSet( 
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(500.),#300
        layerswitchon  = cms.bool(True)
    ),

   TH1PosxSas = cms.PSet( 
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-6.0),
        xmax           = cms.double(+6.0),
        layerswitchon  = cms.bool(True)
    ),

   TH1ErrxSas = cms.PSet( 
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(0.1),#0.01
        layerswitchon  = cms.bool(True)
    ),

   TH1ResSas = cms.PSet( 
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-0.10),#-0.02
        xmax           = cms.double(+0.10),#+0.02
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
        xmin           = cms.double(-10.),#-4.0
        xmax           = cms.double(+10.),#+4.0
        layerswitchon  = cms.bool(True)
    ),

   TH1Chi2Sas = cms.PSet( 
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(100.),#50
        layerswitchon  = cms.bool(True)
    ),

   TH1PosxMatched = cms.PSet( 
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-10.0),#-6.0
        xmax           = cms.double(+10.0),#+6.0
        layerswitchon  = cms.bool(True)
    ),

   TH1PosyMatched = cms.PSet( 
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-10.0),#-6.0
        xmax           = cms.double(+10.0),#+6.0
        layerswitchon  = cms.bool(True)
    ),

   TH1ErrxMatched = cms.PSet( 
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(0.1),#0.01
        layerswitchon  = cms.bool(True)
    ),

   TH1ErryMatched = cms.PSet( 
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(0.25),#0.05
        layerswitchon  = cms.bool(True)
    ),

   TH1ResxMatched = cms.PSet( 
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-0.1),#-0.02
        xmax           = cms.double(+0.1),#+0.02
        layerswitchon  = cms.bool(True)
    ),

   TH1ResyMatched = cms.PSet( 
        Nbinx          = cms.int32(100),
        xmin           = cms.double(-10.), #-1
        xmax           = cms.double(+10. ), #+1
        layerswitchon  = cms.bool(True) 
    ),

   TH1Chi2Matched = cms.PSet( 
        Nbinx          = cms.int32(100),
        xmin           = cms.double(0.),
        xmax           = cms.double(50.),
        layerswitchon  = cms.bool(True)
    ),

    associatePixel = cms.bool(False),
    stereoRecHits = cms.InputTag("siStripMatchedRecHits","stereoRecHit"),
    matchedRecHits = cms.InputTag("siStripMatchedRecHits","matchedRecHit"),
    ROUList = cms.vstring('g4SimHitsTrackerHitsTIBLowTof', 
        'g4SimHitsTrackerHitsTIBHighTof', 
        'g4SimHitsTrackerHitsTIDLowTof', 
        'g4SimHitsTrackerHitsTIDHighTof', 
        'g4SimHitsTrackerHitsTOBLowTof', 
        'g4SimHitsTrackerHitsTOBHighTof', 
        'g4SimHitsTrackerHitsTECLowTof', 
        'g4SimHitsTrackerHitsTECHighTof'),
    associateRecoTracks = cms.bool(False),
    associateStrip = cms.bool(True),
    rphiRecHits = cms.InputTag("siStripMatchedRecHits","rphiRecHit"),
    RecHitProducer = cms.string('siStripMatchedRecHits'),
    verbose = cms.untracked.bool(False)
)


