import FWCore.ParameterSet.Config as cms

def getPU(process) :
    n=0
    if hasattr(process,'reconstruction') or hasattr(process,'dqmoffline_step'):
        if hasattr(process,'mix'): 
            if hasattr(process.mix,'input'):
                n=process.mix.input.nbPileupEvents.averageNumber.value()
#        else:
#            print 'phase1TkCustoms requires a --pileup option to cmsDriver to run the reconstruction/dqm'
#            print 'Please provide one!'
#            sys.exit(1)
    print "getPU " + str(n)
    return n         

def trackerValidationCustomisePhase1(process):

    pileup=getPU(process)
    phase=1
    if hasattr(process,'dqmoffline_step'):
        process=trackerValidationCustomise_DQM(process,phase,pileup)
    if hasattr(process,'dqmHarvesting'):
        process=trackerValidationCustomise_HARVESTING(process)
    if hasattr(process,'validation_step'):
        process=trackerValidationCustomise_VALIDATION(process,phase,pileup)
    
    return process

def trackerValidationCustomisePhase2(process):
    pileup=getPU(process)
    phase=2
    if hasattr(process,'dqmoffline_step'):
        process=trackerValidationCustomise_DQM(process,phase,pileup)
    if hasattr(process,'dqmHarvesting'):
        process=trackerValidationCustomise_HARVESTING(process)
    if hasattr(process,'validation_step'):
        process=trackerValidationCustomise_VALIDATION(process,phase,pileup)
    
    return process

# DQM steps change
def trackerValidationCustomise_DQM(process,phase,pileup):

    if hasattr(process.dqmoffline_step,"muonAnalyzer") :
        process.dqmoffline_step.remove(process.muonAnalyzer)
    process.dqmoffline_step.remove(process.jetMETAnalyzer)

    #put isUpgrade flag==true
    process.SiPixelRawDataErrorSource.isUpgrade  = cms.untracked.bool(True)
    process.SiPixelDigiSource.isUpgrade          = cms.untracked.bool(True)
    process.SiPixelClusterSource.isUpgrade       = cms.untracked.bool(True)
    process.SiPixelRecHitSource.isUpgrade        = cms.untracked.bool(True)
    process.SiPixelTrackResidualSource.isUpgrade = cms.untracked.bool(True)
    process.SiPixelHitEfficiencySource.isUpgrade = cms.untracked.bool(True)

    if phase==1 :

        from DQM.TrackingMonitor.customizeTrackingMonitorSeedNumber import customise_trackMon_IterativeTracking_PHASE1PU140
        from DQM.TrackingMonitor.customizeTrackingMonitorSeedNumber import customise_trackMon_IterativeTracking_PHASE1PU70

        if pileup>0 :
            if pileup>100:
                process=customise_trackMon_IterativeTracking_PHASE1PU140(process)
            else:
                process=customise_trackMon_IterativeTracking_PHASE1PU70(process)

    elif phase==2 :
        # We cut down the number of iterative tracking steps [no RECO so far]
        process.dqmoffline_step.remove(process.dedxDQMHarm2SP)
        process.dqmoffline_step.remove(process.dedxDQMHarm2SO)
        process.dqmoffline_step.remove(process.dedxDQMHarm2PO)
        process.dqmoffline_step.remove(process.dEdxMonCommon)
        process.dqmoffline_step.remove(process.TrackMonStep0)
        process.dqmoffline_step.remove(process.TrackMonStep1)
        process.dqmoffline_step.remove(process.TrackMonStep2)
        process.dqmoffline_step.remove(process.TrackMonStep3)
        process.dqmoffline_step.remove(process.TrackMonStep4)
        process.dqmoffline_step.remove(process.TrackMonStep5)
        process.dqmoffline_step.remove(process.TrackMonStep6)
        process.dqmoffline_step.remove(process.TrackMonStep9)
        process.dqmoffline_step.remove(process.TrackMonStep10)

    return process


def trackerValidationCustomise_VALIDATION(process,phase,pileup):

#    process.validation_step.remove(process.trackerHitsValid)
#    process.validation_step.remove(process.pixelDigisValid)
#    process.validation_step.remove(process.stripDigisValid)
#   process.trackValidator.label=cms.VInputTag(cms.InputTag("cutsRecoTracksHp"))
#   process.tracksValidationSelectors = cms.Sequence(process.cutsRecoTracksHp)

   process.validation_step.remove(process.pixRecHitsValid)
   process.validation_step.remove(process.stripRecHitsValid)
   process.validation_step.remove(process.condDataValidation)
   process.validation_step.remove(process.trackingTruthValid)
   process.validation_step.remove(process.PixelTrackingRecHitsValid)
   process.validation_step.remove(process.StripTrackingRecHitsValid)

   if phase==2 :
       process.validation_step.remove(process.trackValidator)

   process.validation_step.remove(process.ecalSimHitsValidation)
   process.validation_step.remove(process.ecalBarrelSimHitsValidation)
   process.validation_step.remove(process.ecalEndcapSimHitsValidation)
   process.validation_step.remove(process.ecalPreshowerSimHitsValidation)
   process.validation_step.remove(process.ecalDigisValidation)
   process.validation_step.remove(process.ecalBarrelDigisValidation)
   process.validation_step.remove(process.ecalEndcapDigisValidation)
   process.validation_step.remove(process.ecalPreshowerDigisValidation)
   process.validation_step.remove(process.ecalSelectiveReadoutValidation)
   process.validation_step.remove(process.ecalRecHitsValidation)
   process.validation_step.remove(process.ecalBarrelRecHitsValidation)
   process.validation_step.remove(process.ecalEndcapRecHitsValidation)
   process.validation_step.remove(process.ecalPreshowerRecHitsValidation)
   process.validation_step.remove(process.egammaBasicClusterAnalyzer)
   process.validation_step.remove(process.egammaSuperClusterAnalyzer)
   process.validation_step.remove(process.AllSimHitsValidation)
   process.validation_step.remove(process.AllHcalDigisValidation)
   process.validation_step.remove(process.hcalSimHitStudy)
   process.validation_step.remove(process.NoiseRatesValidation)
   process.validation_step.remove(process.RecHitsValidation)
   process.validation_step.remove(process.AllCaloTowersValidation)
   process.validation_step.remove(process.validSimHit)
   process.validation_step.remove(process.muondtdigianalyzer)
   process.validation_step.remove(process.cscDigiValidation)
   process.validation_step.remove(process.validationMuonRPCDigis)
   process.validation_step.remove(process.extractedGlobalMuons)
   process.validation_step.remove(process.tpToTkMuonAssociation)
   process.validation_step.remove(process.tpToStaMuonAssociation)
   process.validation_step.remove(process.tpToStaUpdMuonAssociation)
   process.validation_step.remove(process.tpToGlbMuonAssociation)
   process.validation_step.remove(process.tpToTkmuTrackAssociation)
   process.validation_step.remove(process.trkMuonTrackVTrackAssoc)
   process.validation_step.remove(process.staMuonTrackVMuonAssoc)
   process.validation_step.remove(process.staUpdMuonTrackVMuonAssoc)
   process.validation_step.remove(process.glbMuonTrackVMuonAssoc)
   process.validation_step.remove(process.recoMuonVMuAssoc_trk)
   process.validation_step.remove(process.recoMuonVMuAssoc_sta)
   process.validation_step.remove(process.recoMuonVMuAssoc_glb)
   process.validation_step.remove(process.recoMuonVMuAssoc_tgt)
   process.validation_step.remove(process.recoMuonVMuAssoc_trkPF)
   process.validation_step.remove(process.recoMuonVMuAssoc_staPF)
   process.validation_step.remove(process.recoMuonVMuAssoc_glbPF)
   process.validation_step.remove(process.tpToTevFirstMuonAssociation)
   process.validation_step.remove(process.tpToTevPickyMuonAssociation)
   process.validation_step.remove(process.tpToTevDytMuonAssociation)
   process.validation_step.remove(process.tevMuonFirstTrackVMuonAssoc)
   process.validation_step.remove(process.tevMuonPickyTrackVMuonAssoc)
   process.validation_step.remove(process.tevMuonDytTrackVMuonAssoc)
   process.validation_step.remove(process.tpToStaSETMuonAssociation)
   process.validation_step.remove(process.tpToStaSETUpdMuonAssociation)
   process.validation_step.remove(process.tpToGlbSETMuonAssociation)
   process.validation_step.remove(process.staSETMuonTrackVMuonAssoc)
   process.validation_step.remove(process.staSETUpdMuonTrackVMuonAssoc)
   process.validation_step.remove(process.glbSETMuonTrackVMuonAssoc)
   process.validation_step.remove(process.tpToStaRefitMuonAssociation)
   process.validation_step.remove(process.tpToStaRefitUpdMuonAssociation)
   process.validation_step.remove(process.staRefitMuonTrackVMuonAssoc)
   process.validation_step.remove(process.staRefitUpdMuonTrackVMuonAssoc)
   process.validation_step.remove(process.MuIsoValidation_inc)
   process.validation_step.remove(process.MuIsoValidation_global)
   process.validation_step.remove(process.muonIdVal)
   process.validation_step.remove(process.muonIdDQMInVal)
   process.validation_step.remove(process.mixCollectionValidation)
   process.validation_step.remove(process.JetAnalyzerIC5Calo)
   process.validation_step.remove(process.JetAnalyzerIC5PF)
   process.validation_step.remove(process.JetAnalyzerKt4Calo)
   process.validation_step.remove(process.JetAnalyzerKt6Calo)
   process.validation_step.remove(process.JetAnalyzerAk5Calo)
   process.validation_step.remove(process.JetAnalyzerAk7Calo)
   process.validation_step.remove(process.JetAnalyzerAk5PF)
   process.validation_step.remove(process.JetAnalyzerAk5JPT)
   process.validation_step.remove(process.JetAnalyzerIC5JPT)
   process.validation_step.remove(process.metAnalyzer)
   process.validation_step.remove(process.pfMetAnalyzer)
   process.validation_step.remove(process.tcMetAnalyzer)
   process.validation_step.remove(process.genMetTrueAnalyzer)
   process.validation_step.remove(process.trackingParticleRecoTrackAsssociation)
   process.validation_step.remove(process.v0Validator)
   process.validation_step.remove(process.eleIsoDepositTk)
   process.validation_step.remove(process.eleIsoDepositEcalFromHitsFull)
   process.validation_step.remove(process.eleIsoDepositEcalFromHitsReduced)
   process.validation_step.remove(process.eleIsoDepositHcalFromTowers)
   process.validation_step.remove(process.eleIsoFromDepsTk03)
   process.validation_step.remove(process.eleIsoFromDepsTk04)
   process.validation_step.remove(process.eleIsoFromDepsEcalFromHitsByCrystalFull03)
   process.validation_step.remove(process.eleIsoFromDepsEcalFromHitsByCrystalFull04)
   process.validation_step.remove(process.eleIsoFromDepsEcalFromHitsByCrystalReduced03)
   process.validation_step.remove(process.eleIsoFromDepsEcalFromHitsByCrystalReduced04)
   process.validation_step.remove(process.eleIsoFromDepsHcalFromTowers03)
   process.validation_step.remove(process.eleIsoFromDepsHcalFromTowers04)
   process.validation_step.remove(process.electronMcSignalValidator)
   process.validation_step.remove(process.electronMcFakeValidator)
   process.validation_step.remove(process.photonValidation)
   process.validation_step.remove(process.tkConversionValidation)
   process.validation_step.remove(process.pfJetValidation1)
   process.validation_step.remove(process.pfJetValidation2)
   process.validation_step.remove(process.pfMETValidation1)
   process.validation_step.remove(process.pfMETValidation2)
   process.validation_step.remove(process.rpcRecHitV)
   process.validation_step.remove(process.rechivalidation)
   process.validation_step.remove(process.seg2dsuperphivalidation)
   process.validation_step.remove(process.seg4dvalidation)
   process.validation_step.remove(process.RunHPSValidationQCD)
   process.validation_step.remove(process.RunHPSValidationRealData)
   process.validation_step.remove(process.RunHPSValidationRealElectronsData)
   process.validation_step.remove(process.RunHPSValidationRealMuonsData)
   process.validation_step.remove(process.RunHPSValidationZEE)
   process.validation_step.remove(process.RunHPSValidationZMM)
   process.validation_step.remove(process.RunHPSValidationZTT)
   process.validation_step.remove(process.myPartons)
   process.validation_step.remove(process.AK5byRef)
   process.validation_step.remove(process.AK5byValPhys)
   process.validation_step.remove(process.AK5byValAlgo)
   process.validation_step.remove(process.pfbTagValidationNoall)
        
    
   return process

def trackerValidationCustomise_HARVESTING(process):

    process.dqmHarvesting.remove(process.jetMETDQMOfflineClient)
    process.dqmHarvesting.remove(process.dataCertificationJetMET)
    process.dqmHarvesting.remove(process.sipixelEDAClient)
    process.dqmHarvesting.remove(process.sipixelCertification)
    return (process)        

