#ifndef SiStripRecHitsValid_h
#define SiStripRecHitsValid_h

/* \class SiStripRecHitsValid
 *
 * Analyzer to validate RecHits in the Strip tracker
 *
 * \author Patrizia Azzi, INFN PD
 *
 * \version   1st version May 2006
 *
 ************************************************************/

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
//only mine
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

//DQM services for histogram
#include "DQMServices/Core/interface/DQMStore.h"

#include "FWCore/ServiceRegistry/interface/Service.h"

//--- for SimHit association
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"  
#include "SimTracker/TrackerHitAssociation/interface/TrackerHitAssociator.h" 

#include "Geometry/CommonTopologies/interface/PixelTopology.h"
#include "Geometry/CommonTopologies/interface/StripTopology.h"
#include "Geometry/TrackerGeometryBuilder/interface/StripGeomDetUnit.h"
#include "Geometry/CommonDetUnit/interface/GeomDetType.h" 
#include "Geometry/CommonDetUnit/interface/GeomDetUnit.h" 
#include "Geometry/TrackerGeometryBuilder/interface/GluedGeomDet.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerNumberingBuilder/interface/GeometricDet.h"
#include "Geometry/TrackerGeometryBuilder/interface/PixelGeomDetType.h"
#include "Geometry/TrackerGeometryBuilder/interface/StripGeomDetType.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include <string>
#include "DQMServices/Core/interface/MonitorElement.h"
//For RecHit
#include "DataFormats/TrackerRecHit2D/interface/SiStripRecHit2DCollection.h" 
#include "DataFormats/TrackerRecHit2D/interface/SiStripMatchedRecHit2DCollection.h" 

class SiStripDetCabling;
class SiStripDCSStatus;

class SiStripRecHitsValid : public edm::EDAnalyzer {

 public:
  
  SiStripRecHitsValid(const edm::ParameterSet& conf);
  
  ~SiStripRecHitsValid();
 
  struct TotalMEs{ // MEs for total detector Level
    MonitorElement*  meNumTotrphi;
    MonitorElement*  meNumTotSas;
    MonitorElement*  meNumTotMatched;
  };
 
  struct SubDetMEs{ // MEs for Subdetector Level
    MonitorElement*  meNumrphi;
    MonitorElement*  meNumSas;
    MonitorElement*  meNumMatched;
  };

  struct LayerMEs{ // MEs for Layer Level
    MonitorElement* meNstprphi;
    MonitorElement* meAdcrphi;
    MonitorElement* mePosxrphi;
    MonitorElement* meErrxrphi;
    MonitorElement* meResrphi;
    MonitorElement* mePullLFrphi;
    MonitorElement* mePullMFrphi;
    MonitorElement* meChi2rphi;
    
  };

  struct StereoAndMatchedMEs{ // MEs for Layer Level
    MonitorElement* meNstpSas;
    MonitorElement* meAdcSas;
    MonitorElement* mePosxSas;
    MonitorElement* meErrxSas;
    MonitorElement* meResSas;
    MonitorElement* mePullLFSas;
    MonitorElement* mePullMFSas;
    MonitorElement* meChi2Sas;
    MonitorElement* mePosxMatched;
    MonitorElement* mePosyMatched;
    MonitorElement* meErrxMatched;
    MonitorElement* meErryMatched;
    MonitorElement* meResxMatched;
    MonitorElement* meResyMatched;
    MonitorElement* meChi2Matched;

  };

 protected:

  virtual void analyze(const edm::Event& e, const edm::EventSetup& c);
  void beginJob(const edm::EventSetup& es);
  virtual void beginRun(const edm::Run&, const edm::EventSetup&);
  void endJob();
    
 private: 
  //Back-End Interface
  DQMStore* dbe_;
  std::string outputFile_;

  TotalMEs totalMEs;

  bool switchNumTotrphi;
  bool switchNumTotSas;
  bool switchNumTotMatched;


  bool switchNumrphi;
  bool switchNumSas;
  bool switchNumMatched;


  bool switchNstprphi;
  bool switchAdcrphi;
  bool switchPosxrphi;
  bool switchErrxrphi;
  bool switchResrphi;
  bool switchPullLFrphi;
  bool switchPullMFrphi;
  bool switchChi2rphi;
  bool switchNstpSas;
  bool switchAdcSas;
  bool switchPosxSas;
  bool switchErrxSas;
  bool switchResSas;
  bool switchPullLFSas;
  bool switchPullMFSas;
  bool switchChi2Sas;
  bool switchPosxMatched;
  bool switchPosyMatched;
  bool switchErrxMatched;
  bool switchErryMatched;
  bool switchResxMatched;
  bool switchResyMatched;
  bool switchChi2Matched;
  
  std::string topFolderName_;
  std::vector<std::string> SubDetList_;
  
  std::vector<PSimHit> matched;
  std::map<std::string, LayerMEs> LayerMEsMap;
  std::map<std::string, StereoAndMatchedMEs> StereoAndMatchedMEsMap;
  std::map<std::string, SubDetMEs> SubDetMEsMap;
  std::map<std::string, std::vector< uint32_t > > LayerDetMap;
  std::map<std::string, std::vector< uint32_t > > StereoAndMatchedDetMap;

  edm::ESHandle<SiStripDetCabling> SiStripDetCabling_;

  std::pair<LocalPoint,LocalVector> projectHit( const PSimHit& hit, const StripGeomDetUnit* stripDet,
							const BoundPlane& plane);
  void createMEs(const edm::EventSetup& es);
  void createTotalMEs(); 
  void createLayerMEs(std::string label);
  void createSubDetMEs(std::string label);
  void createStereoAndMatchedMEs(std::string label);
  
  MonitorElement* bookME1D(const char* ParameterSetLabel, const char* HistoName, const char* HistoTitle);

  inline void fillME(MonitorElement* ME,float value1){if (ME!=0)ME->Fill(value1);}
  inline void fillME(MonitorElement* ME,float value1,float value2){if (ME!=0)ME->Fill(value1,value2);}
  inline void fillME(MonitorElement* ME,float value1,float value2,float value3){if (ME!=0)ME->Fill(value1,value2,value3);}
  inline void fillME(MonitorElement* ME,float value1,float value2,float value3,float value4){if (ME!=0)ME->Fill(value1,value2,value3,value4);}

  edm::ParameterSet conf_;
  unsigned long long m_cacheID_;
  edm::ParameterSet Parameters;
  //const StripTopology* topol;

  static const int MAXHIT = 1000;
  float rechitrphix[MAXHIT];
  float rechitrphierrx[MAXHIT];
  float rechitrphiy[MAXHIT];
  float rechitrphiz[MAXHIT];
  float rechitrphiphi[MAXHIT];
  float rechitrphires[MAXHIT];
  float rechitrphipullMF[MAXHIT];
  int   clusizrphi[MAXHIT];
  float cluchgrphi[MAXHIT];
  float rechitsasx[MAXHIT];
  float rechitsaserrx[MAXHIT];
  float rechitsasy[MAXHIT];
  float rechitsasz[MAXHIT];
  float rechitsasphi[MAXHIT];
  float rechitsasres[MAXHIT];
  float rechitsaspullMF[MAXHIT];
  int   clusizsas[MAXHIT];
  float cluchgsas[MAXHIT];
  float chi2rphi[MAXHIT];
  float chi2sas[MAXHIT];
  float chi2matched[MAXHIT];
  float rechitmatchedx[MAXHIT];
  float rechitmatchedy[MAXHIT];
  float rechitmatchedz[MAXHIT];
  float rechitmatchederrxx[MAXHIT];
  float rechitmatchederrxy[MAXHIT];
  float rechitmatchederryy[MAXHIT];
  float rechitmatchedphi[MAXHIT];
  float rechitmatchedresx[MAXHIT];
  float rechitmatchedresy[MAXHIT];
  float rechitmatchedchi2[MAXHIT];

  //edm::InputTag matchedRecHits_, rphiRecHits_, stereoRecHits_; 
  edm::EDGetTokenT<SiStripMatchedRecHit2DCollection> matchedRecHitsToken_;
  edm::EDGetTokenT<SiStripRecHit2DCollection> rphiRecHitsToken_;
  edm::EDGetTokenT<SiStripRecHit2DCollection> stereoRecHitsToken_;

};

#endif
