#include "Validation/TrackerRecHits/interface/SiStripRecHitsValid.h"
#include "SimTracker/TrackerHitAssociation/interface/TrackerHitAssociator.h" 

//needed for the geometry: 
#include "CalibTracker/Records/interface/SiStripDetCablingRcd.h"
#include "CalibFormats/SiStripObjects/interface/SiStripDetCabling.h"
#include "DataFormats/DetId/interface/DetId.h" 
#include "DataFormats/SiStripDetId/interface/StripSubdetector.h" 
#include "DataFormats/SiStripDetId/interface/SiStripSubStructure.h"
#include "DQM/SiStripCommon/interface/SiStripFolderOrganizer.h"
#include "DataFormats/SiStripDetId/interface/TECDetId.h" 
#include "DataFormats/SiStripDetId/interface/TIBDetId.h" 
#include "DataFormats/SiStripDetId/interface/TIDDetId.h"
#include "DataFormats/SiStripDetId/interface/TOBDetId.h" 
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DQM/SiStripCommon/interface/SiStripHistoId.h"


//--- for RecHit
#include "DataFormats/SiStripCluster/interface/SiStripCluster.h" 
#include "DataFormats/SiStripCluster/interface/SiStripClusterCollection.h" 
#include "DataFormats/Common/interface/OwnVector.h" 
#include "DQMServices/Core/interface/DQMStore.h"

#include "CommonTools/TriggerUtils/interface/GenericTriggerEventFlag.h"

using namespace std;
using namespace edm;

namespace helper { 
    struct GetDetId { 
        template<typename X> 
        DetId operator()(const X &x) { return DetId(x.detId()); }
    };

    template<typename T>
    std::pair<typename T::DetSet::const_iterator, typename T::DetSet::const_iterator> 
    getRange(const T &detset, const DetId &id) {
        typedef std::pair<typename T::DetSet::const_iterator, typename T::DetSet::const_iterator> return_type;
        typename T::const_iterator match = detset.find(id);
        if (match == detset.end()) return return_type();
        typename T::DetSet hits = *match;
        return return_type(hits.begin(), hits.end());
    } 
}



//Constructor
SiStripRecHitsValid::SiStripRecHitsValid(const ParameterSet& ps) :
  dbe_(edm::Service<DQMStore>().operator->()),	
  conf_(ps),
  m_cacheID_(0)
  // matchedRecHits_( ps.getParameter<edm::InputTag>("matchedRecHits") ),
  // rphiRecHits_( ps.getParameter<edm::InputTag>("rphiRecHits") ),
  // stereoRecHits_( ps.getParameter<edm::InputTag>("stereoRecHits") ) 
{
  matchedRecHitsToken_ = consumes<SiStripMatchedRecHit2DCollection>( ps.getParameter<edm::InputTag>("matchedRecHits") );
    
  rphiRecHitsToken_ = consumes<SiStripRecHit2DCollection>( ps.getParameter<edm::InputTag>("rphiRecHits") );
    
  stereoRecHitsToken_ = consumes<SiStripRecHit2DCollection>( ps.getParameter<edm::InputTag>("stereoRecHits") ); 

  topFolderName_ = conf_.getParameter<std::string>("TopFolderName");

  SubDetList_ = conf_.getParameter<std::vector<std::string> >("SubDetList");

  edm::ParameterSet ParametersNumTotRphi =  conf_.getParameter<edm::ParameterSet>("TH1NumTotRphi");
  switchNumTotRphi = ParametersNumTotRphi.getParameter<bool>("switchon");

  edm::ParameterSet ParametersNumTotSas =  conf_.getParameter<edm::ParameterSet>("TH1NumTotSas");
  switchNumTotSas = ParametersNumTotSas.getParameter<bool>("switchon");

  edm::ParameterSet ParametersNumTotMatched =  conf_.getParameter<edm::ParameterSet>("TH1NumTotMatched");
  switchNumTotMatched = ParametersNumTotMatched.getParameter<bool>("switchon");

  edm::ParameterSet ParametersNumRphi =  conf_.getParameter<edm::ParameterSet>("TH1NumRphi");
  switchNumRphi = ParametersNumRphi.getParameter<bool>("switchon");

  edm::ParameterSet ParametersNumSas =  conf_.getParameter<edm::ParameterSet>("TH1NumSas");
  switchNumSas = ParametersNumSas.getParameter<bool>("switchon");

  edm::ParameterSet ParametersNumMatched =  conf_.getParameter<edm::ParameterSet>("TH1NumMatched");
  switchNumMatched = ParametersNumMatched.getParameter<bool>("switchon");

  edm::ParameterSet ParametersNstpRphi =  conf_.getParameter<edm::ParameterSet>("TH1NstpRphi");
  switchNstpRphi = ParametersNstpRphi.getParameter<bool>("switchon");

  edm::ParameterSet ParametersAdcRphi =  conf_.getParameter<edm::ParameterSet>("TH1AdcRphi");
  switchAdcRphi = ParametersAdcRphi.getParameter<bool>("switchon");

  edm::ParameterSet ParametersPosxRphi =  conf_.getParameter<edm::ParameterSet>("TH1PosxRphi");
  switchPosxRphi = ParametersPosxRphi.getParameter<bool>("switchon");

  edm::ParameterSet ParametersErrxRphi =  conf_.getParameter<edm::ParameterSet>("TH1ErrxRphi");
  switchErrxRphi = ParametersErrxRphi.getParameter<bool>("switchon");

  edm::ParameterSet ParametersResRphi =  conf_.getParameter<edm::ParameterSet>("TH1ResRphi");
  switchResRphi = ParametersResRphi.getParameter<bool>("switchon");

  edm::ParameterSet ParametersPullLFRphi =  conf_.getParameter<edm::ParameterSet>("TH1PullLFRphi");
  switchPullLFRphi = ParametersPullLFRphi.getParameter<bool>("switchon");

  edm::ParameterSet ParametersPullMFRphi =  conf_.getParameter<edm::ParameterSet>("TH1PullMFRphi");
  switchPullMFRphi = ParametersPullMFRphi.getParameter<bool>("switchon");

  edm::ParameterSet ParametersChi2Rphi =  conf_.getParameter<edm::ParameterSet>("TH1Chi2Rphi");
  switchChi2Rphi = ParametersChi2Rphi.getParameter<bool>("switchon");

  edm::ParameterSet ParametersNstpSas =  conf_.getParameter<edm::ParameterSet>("TH1NstpSas");
  switchNstpSas = ParametersNstpSas.getParameter<bool>("switchon");

  edm::ParameterSet ParametersAdcSas =  conf_.getParameter<edm::ParameterSet>("TH1AdcSas");
  switchAdcSas = ParametersAdcSas.getParameter<bool>("switchon");

  edm::ParameterSet ParametersPosxSas =  conf_.getParameter<edm::ParameterSet>("TH1PosxSas");
  switchPosxSas = ParametersPosxSas.getParameter<bool>("switchon");

  edm::ParameterSet ParametersErrxSas =  conf_.getParameter<edm::ParameterSet>("TH1ErrxSas");
  switchErrxSas = ParametersErrxSas.getParameter<bool>("switchon");

  edm::ParameterSet ParametersResSas =  conf_.getParameter<edm::ParameterSet>("TH1ResSas");
  switchResSas = ParametersResSas.getParameter<bool>("switchon");

  edm::ParameterSet ParametersPullLFSas =  conf_.getParameter<edm::ParameterSet>("TH1PullLFSas");
  switchPullLFSas = ParametersPullLFSas.getParameter<bool>("switchon");

  edm::ParameterSet ParametersPullMFSas =  conf_.getParameter<edm::ParameterSet>("TH1PullMFSas");
  switchPullMFSas = ParametersPullMFSas.getParameter<bool>("switchon");

  edm::ParameterSet ParametersChi2Sas =  conf_.getParameter<edm::ParameterSet>("TH1Chi2Sas");
  switchChi2Sas = ParametersChi2Sas.getParameter<bool>("switchon");

  edm::ParameterSet ParametersPosxMatched =  conf_.getParameter<edm::ParameterSet>("TH1PosxMatched");
  switchPosxMatched = ParametersPosxMatched.getParameter<bool>("switchon");

  edm::ParameterSet ParametersPosyMatched =  conf_.getParameter<edm::ParameterSet>("TH1PosyMatched");
  switchPosyMatched = ParametersPosyMatched.getParameter<bool>("switchon");

  edm::ParameterSet ParametersErrxMatched =  conf_.getParameter<edm::ParameterSet>("TH1ErrxMatched");
  switchErrxMatched = ParametersErrxMatched.getParameter<bool>("switchon");

  edm::ParameterSet ParametersErryMatched =  conf_.getParameter<edm::ParameterSet>("TH1ErryMatched");
  switchErryMatched = ParametersErryMatched.getParameter<bool>("switchon");

  edm::ParameterSet ParametersResxMatched =  conf_.getParameter<edm::ParameterSet>("TH1ResxMatched");
  switchResxMatched = ParametersResxMatched.getParameter<bool>("switchon");

  edm::ParameterSet ParametersResyMatched =  conf_.getParameter<edm::ParameterSet>("TH1ResyMatched");
  switchResyMatched = ParametersResyMatched.getParameter<bool>("switchon");

  edm::ParameterSet ParametersChi2Matched =  conf_.getParameter<edm::ParameterSet>("TH1Chi2Matched");
  switchChi2Matched = ParametersChi2Matched.getParameter<bool>("switchon");

}

SiStripRecHitsValid::~SiStripRecHitsValid(){
  // if ( outputFile_.size() != 0 && dbe_ ) dbe_->save(outputFile_);
}

//--------------------------------------------------------------------------------------------
void SiStripRecHitsValid::beginRun(const edm::Run& run, const edm::EventSetup& es){

  unsigned long long cacheID = es.get<SiStripDetCablingRcd>().cacheIdentifier();
  if (m_cacheID_ != cacheID) {
    m_cacheID_ = cacheID;       
    edm::LogInfo("SiStripRecHitsValid") <<"SiStripRecHitsValid::beginRun: " 
					  << " Creating MEs for new Cabling ";     
    
    createMEs(es);
  }
}


void SiStripRecHitsValid::beginJob(const edm::EventSetup& es){
  
}

void SiStripRecHitsValid::endJob() {

  bool outputMEsInRootFile = conf_.getParameter<bool>("OutputMEsInRootFile");
  std::string outputFileName = conf_.getParameter<std::string>("outputFile");
 
  // save histos in a file
  if(outputMEsInRootFile) dbe_->save(outputFileName);

}


void SiStripRecHitsValid::analyze(const edm::Event& e, const edm::EventSetup& es) {

  LogInfo("EventInfo") << " Run = " << e.id().run() << " Event = " << e.id().event();  
  //cout  << " Run = " << e.id().run() << " Event = " << e.id().event() << endl;  
  
  //Retrieve tracker topology from geometry
  edm::ESHandle<TrackerTopology> tTopoHandle;
  es.get<IdealGeometryRecord>().get(tTopoHandle);
  const TrackerTopology* const tTopo = tTopoHandle.product();
    
  //--- get RecHits
  
  std::string rechitProducer = "SiStripRecHits2D";
  
  // Step A: Get Inputs 
  edm::Handle<SiStripMatchedRecHit2DCollection> rechitsmatched;
  edm::Handle<SiStripRecHit2DCollection> rechitsrphi;
  edm::Handle<SiStripRecHit2DCollection> rechitsstereo;
  // e.getByLabel(matchedRecHits_, rechitsmatched);
  // e.getByLabel(rphiRecHits_, rechitsrphi);
  // e.getByLabel(stereoRecHits_, rechitsstereo);
  e.getByToken(matchedRecHitsToken_, rechitsmatched);
  e.getByToken(rphiRecHitsToken_, rechitsrphi);
  e.getByToken(stereoRecHitsToken_, rechitsstereo);

  int numrechitrphi   =0;
  int numrechitsas    =0;
  int numrechitmatched=0;

  //Variables in order to count total num of rechitrphi,rechitsas, rechitmatched in subdetectors
  std::map<std::string, std::vector<int> > totnumrechitrphi;
  std::map<std::string, std::vector<int> > totnumrechitsas;
  std::map<std::string, std::vector<int> > totnumrechitmatched;
  totnumrechitrphi.clear();
  totnumrechitsas.clear();
  totnumrechitmatched.clear();
  int totrechitrphi =0;
  int totrechitsas =0;
  int totrechitmatched =0;

  TrackerHitAssociator associate(e, conf_);
  
  edm::ESHandle<TrackerGeometry> pDD;
  es.get<TrackerDigiGeometryRecord> ().get (pDD);
  const TrackerGeometry &tracker(*pDD);
  // FIXME: this using of vector<DetId> is suboptimal, but I don't want to re-write the full class now
  std::vector<DetId> IDs; 
  IDs.reserve(rechitsrphi->size() + rechitsmatched->size() + rechitsstereo->size());
  std::transform(rechitsrphi->begin(), rechitsrphi->end(), std::back_inserter(IDs), helper::GetDetId() );
  std::transform(rechitsstereo->begin(), rechitsstereo->end(), std::back_inserter(IDs), helper::GetDetId() );
  std::transform(rechitsmatched->begin(), rechitsmatched->end(), std::back_inserter(IDs), helper::GetDetId() );
  // loop over detunits
  //  for(TrackerGeometry::DetContainer::const_iterator it = pDD->dets().begin(); it != pDD->dets().end(); it++){
  for(std::vector<DetId>::const_iterator it = IDs.begin(); it != IDs.end(); ++it ){//loop on rphi detector with hits
    uint32_t myid=((*it).rawId());       
    DetId detid = ((*it));
    
    // initialize here
    for(int i=0; i<MAXHIT; i++){
      rechitrphix[i] =0;
      rechitrphierrx[i] =0;
      rechitrphiy[i] =0;
      rechitrphiz[i] =0;
      rechitsasx[i] =0;
      rechitsaserrx[i] =0;
      rechitsasy[i] =0;
      rechitsasz[i] =0;
      clusizrphi[i] =0;
      clusizsas[i] =0;
      cluchgrphi[i] =0;
      cluchgsas[i] =0;
      rechitrphires[i]=-999.;
      rechitsasres[i]=-999.;
      rechitrphipullMF[i]=-999.;
      rechitsaspullMF[i]=-999.;
      chi2rphi[i] =0;
      chi2sas[i]=0;
      rechitmatchedx[i] =0;
      rechitmatchedy[i] =0;
      rechitmatchedz[i] =0;
      rechitmatchederrxx[i] =0;
      rechitmatchederrxy[i] =0;
      rechitmatchederryy[i] =0;
      rechitmatchedresx[i]=-999;
      rechitmatchedresy[i]=-999;
      chi2matched[i]=0;
    }
    
    numrechitrphi =0;
    //loop over rechits-rphi in the same subdetector
    std::pair<SiStripRecHit2DCollection::DetSet::const_iterator,SiStripRecHit2DCollection::DetSet::const_iterator> rechitrphiRange = helper::getRange(*rechitsrphi, detid);
    SiStripRecHit2DCollection::DetSet::const_iterator rechitrphiRangeIteratorBegin = rechitrphiRange.first;
    SiStripRecHit2DCollection::DetSet::const_iterator rechitrphiRangeIteratorEnd   = rechitrphiRange.second;
    SiStripRecHit2DCollection::DetSet::const_iterator iterrphi=rechitrphiRangeIteratorBegin;
    
    numrechitrphi = rechitrphiRangeIteratorEnd - rechitrphiRangeIteratorBegin;   
         

    int i=0;
    int i2=0;

    if(numrechitrphi > 0 ){
      totrechitrphi+=numrechitrphi;
      for(iterrphi=rechitrphiRangeIteratorBegin; iterrphi!=rechitrphiRangeIteratorEnd;++iterrphi){
	const GeomDetUnit *  det = tracker.idToDetUnit(detid);
	const StripGeomDetUnit * stripdet=(const StripGeomDetUnit*)(det);
	const StripTopology &topol=(StripTopology&)stripdet->topology();
	SiStripRecHit2D const rechit=*iterrphi;
	LocalPoint position=rechit.localPosition();
	LocalError error=rechit.localPositionError();
	MeasurementPoint Mposition;
	MeasurementError Merror;
	Mposition = topol.measurementPosition(position);
	Merror = topol.measurementError(position,error);
	SiStripRecHit2D::ClusterRef clust=rechit.cluster();
	int clusiz=0;
	int totcharge=0;
	clusiz = clust->amplitudes().size();
	const std::vector<uint8_t> amplitudes=clust->amplitudes();
	  for(size_t ia=0; ia<amplitudes.size();ia++){
	    totcharge+=amplitudes[ia];
	  }
	rechitrphix[i] = position.x();
	rechitrphiy[i] = position.y();
	rechitrphiz[i] = position.z();
	rechitrphierrx[i] = error.xx();
	clusizrphi[i] = clusiz;
	cluchgrphi[i] = totcharge;

	matched.clear();
	matched = associate.associateHit(rechit);
	double mindist = 999999;
	double dist = 999999;
	PSimHit closest;
	if(!matched.empty()){
	  for(vector<PSimHit>::const_iterator m=matched.begin(); m<matched.end(); m++){
	    dist = fabs(rechitrphix[i] - (*m).localPosition().x());
	    if(dist<mindist){
	      mindist = dist;
	      closest = (*m);
	    }
	    rechitrphires[i] = rechitrphix[i] - closest.localPosition().x();
	  }  
	  rechitrphipullMF[i] = (Mposition.x() - (topol.measurementPosition(closest.localPosition())).x())/sqrt(Merror.uu());

	  //chi2test compare rechit errors with the simhit position ( using null matrix for the simhit). 
	  //Can spot problems in the geometry better than a simple residual. (thanks to BorisM)
	  AlgebraicVector  rhparameters(2);//= rechit.parameters();
	  rhparameters[0] = position.x(); 
	  rhparameters[1] = position.y();
	  AlgebraicVector shparameters(2);
	  shparameters[0] = closest.localPosition().x();
	  shparameters[1] = closest.localPosition().y();
	  AlgebraicVector r(rhparameters - shparameters);
	  AlgebraicSymMatrix R(2);//  = rechit.parametersError();
	  R[0][0] = error.xx();
	  R[0][1] = error.xy();
	  R[1][1] = error.yy();
	  int ierr; 
	  R.invert(ierr); // if (ierr != 0) throw exception;
	  double est = R.similarity(r);
	  // 	  std::cout << " ====== Chi2 test rphi hits ====== " << std::endl;
	  // 	  std::cout << "RecHit param. = " << rhparameters << std::endl;
	  // 	  std::cout << "RecHit errors = " << R << std::endl;
	  //	  std::cout << "SimHit param. = " << shparameters << std::endl;
	  //	  std::cout << " chi2  = " << est << std::endl;
	  //	  std::cout << "DEBUG BORIS,filling chi2rphi[i],i: " << i << std::endl;
	  chi2rphi[i2] = est;
	  i2++;
	}
	i++;
      }
    }
    
    //loop over rechits-sas in the same subdetector
    int j=0;
    int j2=0;
    numrechitsas=0;
    std::pair<SiStripRecHit2DCollection::DetSet::const_iterator,SiStripRecHit2DCollection::DetSet::const_iterator> rechitsasRange = helper::getRange(*rechitsstereo, detid);
    SiStripRecHit2DCollection::DetSet::const_iterator rechitsasRangeIteratorBegin = rechitsasRange.first;
    SiStripRecHit2DCollection::DetSet::const_iterator rechitsasRangeIteratorEnd   = rechitsasRange.second;
    SiStripRecHit2DCollection::DetSet::const_iterator itersas=rechitsasRangeIteratorBegin;
    numrechitsas = rechitsasRangeIteratorEnd - rechitsasRangeIteratorBegin;   
    if(numrechitsas > 0){
      totrechitsas+=numrechitsas;
      for(itersas=rechitsasRangeIteratorBegin; itersas!=rechitsasRangeIteratorEnd;++itersas){
	const GeomDetUnit *  det = tracker.idToDetUnit(detid);
	const StripGeomDetUnit * stripdet=(const StripGeomDetUnit*)(det);
	const StripTopology &topol=(StripTopology&)stripdet->topology();
	SiStripRecHit2D const rechit=*itersas;
	LocalPoint position=rechit.localPosition();
	LocalError error=rechit.localPositionError();
	MeasurementPoint Mposition;
	MeasurementError Merror;
	Mposition = topol.measurementPosition(position);
	Merror = topol.measurementError(position,error);
	SiStripRecHit2D::ClusterRef clust=rechit.cluster();	int clusiz=0;
	int totcharge=0;
	clusiz = clust->amplitudes().size();
	const std::vector<uint8_t> amplitudes=clust->amplitudes();
	for(size_t ia=0; ia<amplitudes.size();ia++){
	  totcharge+=amplitudes[ia];
	}
	
	rechitsasx[j] = position.x();
	rechitsasy[j] = position.y();
	rechitsasz[j] = position.z();
	rechitsaserrx[j] = error.xx();
	clusizsas[j] = clusiz;
	cluchgsas[j] = totcharge;
	
	double mindist = 999999;
	double dist = 999999;
	PSimHit closest;
	matched.clear();
	matched = associate.associateHit(rechit);
	if(!matched.empty()){
	  for(vector<PSimHit>::const_iterator m=matched.begin(); m<matched.end(); m++){
	    dist = fabs(rechitsasx[j] - (*m).localPosition().x());
	    if(dist<mindist){
	      mindist = dist;
	      closest = (*m);
	    }
	    rechitsasres[j] = rechitsasx[j] - closest.localPosition().x();
	  }  
	  rechitsaspullMF[j] = (Mposition.x() - (topol.measurementPosition(closest.localPosition())).x())/sqrt(Merror.uu());
	  //chi2test compare rechit errors with the simhit position ( using null matrix for the simhit). 
	  //Can spot problems in the geometry better than a simple residual. (thanks to BorisM)
// 	  AlgebraicVector rhparameters = rechit.parameters();
	  AlgebraicVector  rhparameters(2);//= rechit.parameters();
	  rhparameters[0] = position.x(); 
	  rhparameters[1] = position.y();
	  AlgebraicVector shparameters(2);
	  shparameters[0] = closest.localPosition().x();
	  shparameters[1] = closest.localPosition().y();
	  AlgebraicVector r(rhparameters - shparameters);
// 	  AlgebraicSymMatrix R  = rechit.parametersError();
	  AlgebraicSymMatrix R(2);//  = rechit.parametersError();
	  R[0][0] = error.xx();
	  R[0][1] = error.xy();
	  R[1][1] = error.yy();
	  int ierr; 
	  R.invert(ierr); // if (ierr != 0) throw exception;
	  double est = R.similarity(r);
	  // 	  std::cout << " ====== Chi2 test sas hits ====== " << std::endl;
	  //	  std::cout << "RecHit param. = " << rhparameters << std::endl;
	  // 	  std::cout << "RecHit errors = " << R << std::endl;
	  // 	  std::cout << "SimHit param. = " << shparameters << std::endl;
	  // 	  std::cout << " chi2  = " << est << std::endl;
	  //	  std::cout << "DEBUG BORIS,filling chi2sas[j],j: " << i << std::endl;
	  chi2sas[j2] = est;
	  j2++;
	}
	j++;
      }
    }
    
    //now matched hits

    int k=0;
    int k2=0;
    
    //loop over rechits-matched in the same subdetector
    numrechitmatched=0;
    std::pair<SiStripMatchedRecHit2DCollection::DetSet::const_iterator,SiStripMatchedRecHit2DCollection::DetSet::const_iterator> rechitmatchedRange = helper::getRange(*rechitsmatched, detid);
    SiStripMatchedRecHit2DCollection::DetSet::const_iterator rechitmatchedRangeIteratorBegin = rechitmatchedRange.first;
    SiStripMatchedRecHit2DCollection::DetSet::const_iterator rechitmatchedRangeIteratorEnd   = rechitmatchedRange.second;
    SiStripMatchedRecHit2DCollection::DetSet::const_iterator itermatched=rechitmatchedRangeIteratorBegin;
    numrechitmatched = rechitmatchedRangeIteratorEnd - rechitmatchedRangeIteratorBegin;   
    if(numrechitmatched > 0){
      totrechitmatched +=numrechitmatched;

      for(itermatched=rechitmatchedRangeIteratorBegin; itermatched!=rechitmatchedRangeIteratorEnd;++itermatched){
	SiStripMatchedRecHit2D const rechit=*itermatched;
	LocalPoint position=rechit.localPosition();
	LocalError error=rechit.localPositionError();
	
	double mindist = 999999;
	double distx = 999999;
	double disty = 999999;
	double dist = 999999;
	std::pair<LocalPoint,LocalVector> closestPair;
	matched.clear();
	//	const SiStripRecHit2D *mono = rechit.monoHit();
	//	const SiStripRecHit2D *st = rechit.stereoHit();
	//	LocalPoint monopos = mono->localPosition();
	//	LocalPoint stpos   = st->localPosition();
	
	rechitmatchedx[k] = position.x();
	rechitmatchedy[k] = position.y();
	rechitmatchedz[k] = position.z();
	rechitmatchederrxx[k] = error.xx();
	rechitmatchederrxy[k] = error.xy();
	rechitmatchederryy[k] = error.yy();

	//	std::cout << " before association " << std::endl;
	matched = associate.associateHit(rechit);
	//std::cout << " after association size = " << matched.size() << std::endl;

	if(!matched.empty()){
	  //project simhit;
	  const GluedGeomDet* gluedDet = (const GluedGeomDet*)tracker.idToDet(rechit.geographicalId());
	  const StripGeomDetUnit* partnerstripdet =(StripGeomDetUnit*) gluedDet->stereoDet();
	  std::pair<LocalPoint,LocalVector> hitPair;

	  //std::cout << " RECHIT position = " << position << std::endl;	  
	  
	  for(vector<PSimHit>::const_iterator m=matched.begin(); m<matched.end(); m++){
	    //project simhit;
	    hitPair= projectHit((*m),partnerstripdet,gluedDet->surface());
	    distx = fabs(rechitmatchedx[k] - hitPair.first.x());
	    disty = fabs(rechitmatchedy[k] - hitPair.first.y());
	    dist = sqrt(distx*distx+disty*disty);
	    // std::cout << " Simhit position x = " << hitPair.first.x() 
	    //      << " y = " << hitPair.first.y() << " dist = " << dist << std::endl;	  
	    if(dist<mindist){
	      mindist = dist;
	      closestPair = hitPair;
	    }
	  }
	  //std::cout << " Closest position x = " << closestPair.first.x() 
	  //      << " y = " << closestPair.first.y() << " dist = " << dist << std::endl;	  
	  rechitmatchedresx[k] = rechitmatchedx[k] - closestPair.first.x();
	  rechitmatchedresy[k] = rechitmatchedy[k] - closestPair.first.y();

 	  //chi2test compare rechit errors with the simhit position ( using null matrix for the simhit). 
 	  //Can spot problems in the geometry better than a simple residual. (thanks to BorisM)

	  AlgebraicVector  rhparameters(2);//= rechit.parameters();
	  rhparameters[0] = position.x(); 
	  rhparameters[1] = position.y();
 	  LocalPoint sh = closestPair.first;
 	  AlgebraicVector shparameters(2);
 	  shparameters[0] = sh.x();
 	  shparameters[1] = sh.y();
 	  AlgebraicVector r(rhparameters - shparameters);
	  AlgebraicSymMatrix R(2);//  = rechit.parametersError();
	  R[0][0] = error.xx();
	  R[0][1] = error.xy();
	  R[1][1] = error.yy();
	  int ierr; 
	  R.invert(ierr); // if (ierr != 0) throw exception;
	  double est = R.similarity(r);
	  // 	  std::cout << " ====== Chi2 test matched ====== " << std::endl;
	  // 	  std::cout << "RecHit param. = " << rhparameters << std::endl;
	  // 	  std::cout << "RecHit errors = " << R << std::endl;
	  // 	  std::cout << "SimHit param. = " << shparameters << std::endl;
	  // 	  std::cout << " chi2  = " << est << std::endl;
	  chi2matched[k2] = est;
	  k2++;
	}
	
	k++;
      }
    }
    
    SiStripHistoId hidmanager;
    std::string label = hidmanager.getSubdetid(myid,tTopo,true);
    std::map<std::string, LayerMEs>::iterator iLayerME  = LayerMEsMap.find(label);
    std::map<std::string, StereoAndMatchedMEs>::iterator iStereoAndMatchedME  = StereoAndMatchedMEsMap.find(label);
    // std::cout << "label " << label << endl;
    SiStripFolderOrganizer fold_organ;
    std::pair<std::string,int32_t> det_lay_pair = fold_organ.GetSubDetAndLayer(myid,tTopo,true);
  
    if(numrechitrphi>0 || numrechitsas>0 || numrechitmatched){

      totnumrechitrphi[det_lay_pair.first].push_back(numrechitrphi);
      totnumrechitsas[det_lay_pair.first].push_back(numrechitsas);
      totnumrechitmatched[det_lay_pair.first].push_back(numrechitmatched);

      //Auxillary variables for the loops
      int numrechitrphi1    = numrechitrphi;
      int numrechitsas1     = numrechitsas;
      int numrechitmatched1 = numrechitmatched;
      int numrechitrphi2    = i2;
      int numrechitsas2     = j2;
      int numrechitmatched2 = k2;

      std::map<std::string, LayerMEs>::iterator iLayerME  = LayerMEsMap.find(label);

      for(int k = 0; k<numrechitrphi1; k++){
	if(iLayerME != LayerMEsMap.end()){
	  fillME(iLayerME->second.meNstpRphi,clusizrphi[k]);
	  fillME(iLayerME->second.meAdcRphi,cluchgrphi[k]);
	  fillME(iLayerME->second.mePosxRphi,rechitrphix[k]);
	  fillME(iLayerME->second.meErrxRphi,rechitrphierrx[k]);
	  fillME(iLayerME->second.meResRphi,rechitrphires[k]);
	  fillME(iLayerME->second.mePullLFRphi,rechitrphires[k]/sqrt(rechitrphierrx[k]));
	  fillME(iLayerME->second.mePullMFRphi,rechitrphipullMF[k]);
	}

      }

      for(int k = 0; k<numrechitrphi2; k++){
	if(iLayerME != LayerMEsMap.end()){
	  fillME(iLayerME->second.meChi2Rphi,chi2rphi[k]);
	}
      }

      for(int kk = 0; kk < numrechitsas1; kk++)	    
	{
	  if(iStereoAndMatchedME != StereoAndMatchedMEsMap.end()){
	    fillME(iStereoAndMatchedME->second.meNstpSas,clusizsas[kk]);
	    fillME(iStereoAndMatchedME->second.meAdcSas,cluchgsas[kk]);
	    fillME(iStereoAndMatchedME->second.mePosxSas,rechitsasx[kk]);
	    fillME(iStereoAndMatchedME->second.meErrxSas,sqrt(rechitsaserrx[kk]));
	    fillME(iStereoAndMatchedME->second.meResSas,rechitsasres[kk]);
	    fillME(iStereoAndMatchedME->second.mePullLFSas,rechitsasres[kk]/sqrt(rechitsaserrx[kk]));
	    fillME(iStereoAndMatchedME->second.mePullMFSas,rechitsaspullMF[kk]);
	  }
	}	  
      for(int l = 0; l<numrechitsas2; l++){
	if(iStereoAndMatchedME != StereoAndMatchedMEsMap.end()){
	  fillME(iStereoAndMatchedME->second.meChi2Sas,chi2sas[l]);
	}
      }

      // }
      if(numrechitmatched1>0){
	for(int kkk = 0; kkk<numrechitmatched1; kkk++)
	  {
	    if(iStereoAndMatchedME != StereoAndMatchedMEsMap.end()){
	      fillME(iStereoAndMatchedME->second.mePosxMatched,rechitmatchedx[kkk]);
	      fillME(iStereoAndMatchedME->second.mePosyMatched,rechitmatchedy[kkk]);
	      fillME(iStereoAndMatchedME->second.meErrxMatched,sqrt(rechitmatchederrxx[kkk]));
	      fillME(iStereoAndMatchedME->second.meErryMatched,sqrt(rechitmatchederryy[kkk]));
	      fillME(iStereoAndMatchedME->second.meResxMatched,rechitmatchedresx[kkk]);
	      fillME(iStereoAndMatchedME->second.meResyMatched,rechitmatchedresy[kkk]);
	    }
	  }	  
	for(int l = 0; l<numrechitmatched2; l++){
	  if(iStereoAndMatchedME != StereoAndMatchedMEsMap.end()){
	    fillME(iStereoAndMatchedME->second.meChi2Matched,chi2matched[l]);
	  }
	}

      }
    }

  }//End of loop over detectors
  

  //now fill the cumulative histograms of the hits
  std::vector<std::string> SubDetList_; 
  for (std::vector<std::string>::iterator iSubdet  = SubDetList_.begin(); iSubdet != SubDetList_.end(); iSubdet++){
    std::map<std::string, SubDetMEs>::iterator iSubDetME  = SubDetMEsMap.find((*iSubdet));
    fillME(iSubDetME->second.meNumRphi,std::accumulate(totnumrechitrphi[(*iSubdet)].rbegin(), totnumrechitrphi[(*iSubdet)].rend(), 0));
    fillME(iSubDetME->second.meNumSas,std::accumulate(totnumrechitsas[(*iSubdet)].rbegin(), totnumrechitsas[(*iSubdet)].rend(), 0));
    fillME(iSubDetME->second.meNumMatched,std::accumulate(totnumrechitmatched[(*iSubdet)].rbegin(), totnumrechitmatched[(*iSubdet)].rend(), 0));
  }

  fillME(totalMEs.meNumTotRphi,totrechitrphi);
  fillME(totalMEs.meNumTotSas,totrechitsas);
  fillME(totalMEs.meNumTotMatched,totrechitmatched);
 
}

  
//needed by to do the residual for matched hits
std::pair<LocalPoint,LocalVector> SiStripRecHitsValid::projectHit( const PSimHit& hit, const StripGeomDetUnit* stripDet,
								   const BoundPlane& plane) 
{
  //  const StripGeomDetUnit* stripDet = dynamic_cast<const StripGeomDetUnit*>(hit.det());
  //if (stripDet == 0) throw MeasurementDetException("HitMatcher hit is not on StripGeomDetUnit");
  
  const StripTopology& topol = stripDet->specificTopology();
  GlobalPoint globalpos= stripDet->surface().toGlobal(hit.localPosition());
  LocalPoint localHit = plane.toLocal(globalpos);
  //track direction
  LocalVector locdir=hit.localDirection();
  //rotate track in new frame
  
  GlobalVector globaldir= stripDet->surface().toGlobal(locdir);
  LocalVector dir=plane.toLocal(globaldir);
  double scale = -localHit.z() / dir.z();
  
  LocalPoint projectedPos = localHit + scale*dir;
  
  //  std::cout << "projectedPos " << projectedPos << std::endl;
  
  double selfAngle = topol.stripAngle( topol.strip( hit.localPosition()));
  
  LocalVector stripDir( sin(selfAngle), cos(selfAngle), 0); // vector along strip in hit frame
  
  LocalVector localStripDir( plane.toLocal(stripDet->surface().toGlobal( stripDir)));
  
  return std::pair<LocalPoint,LocalVector>( projectedPos, localStripDir);
}

//--------------------------------------------------------------------------------------------
void SiStripRecHitsValid::createMEs(const edm::EventSetup& es){

  //Retrieve tracker topology from geometry
  edm::ESHandle<TrackerTopology> tTopoHandle;
  es.get<IdealGeometryRecord>().get(tTopoHandle);
  const TrackerTopology* const tTopo = tTopoHandle.product();
  
  // take from eventSetup the SiStripDetCabling object - here will use SiStripDetControl later on
  es.get<SiStripDetCablingRcd>().get(SiStripDetCabling_);
    
  // get list of active detectors from SiStripDetCabling 
  std::vector<uint32_t> activeDets;
  SiStripDetCabling_->addActiveDetectorsRawIds(activeDets);
    
  SiStripSubStructure substructure;

  SiStripFolderOrganizer folder_organizer;
  // folder_organizer.setSiStripFolderName(topFolderName_);
  std::string curfold = topFolderName_;
  folder_organizer.setSiStripFolderName(curfold);
  folder_organizer.setSiStripFolder();

  // std::cout << "curfold " << curfold << std::endl;

  createTotalMEs();

  // loop over detectors and book MEs
  edm::LogInfo("SiStripTkRecHits|SiStripRecHitsValid")<<"nr. of activeDets:  "<<activeDets.size();
  for(std::vector<uint32_t>::iterator detid_iterator = activeDets.begin(); detid_iterator!=activeDets.end(); detid_iterator++){
    uint32_t detid = (*detid_iterator);
    // remove any eventual zero elements - there should be none, but just in case
    if(detid == 0) {
      activeDets.erase(detid_iterator);
      continue;
    }
    
    // Create Layer Level MEs
    std::pair<std::string,int32_t> det_layer_pair = folder_organizer.GetSubDetAndLayer(detid,tTopo,true);
    SiStripHistoId hidmanager;
    std::string label = hidmanager.getSubdetid(detid,tTopo,true);
    // std::cout << "label " << label << endl;
      
    std::map<std::string, LayerMEs>::iterator iLayerME  = LayerMEsMap.find(label);
    if(iLayerME==LayerMEsMap.end()) {
	
      // get detids for the layer
      // Keep in mind that when we are on the TID or TEC we deal with rings not wheel 
      int32_t lnumber = det_layer_pair.second;
      std::vector<uint32_t> layerDetIds;        
      if (det_layer_pair.first == "TIB") {
	substructure.getTIBDetectors(activeDets,layerDetIds,lnumber,0,0,0);
      } else if (det_layer_pair.first == "TOB") {
	substructure.getTOBDetectors(activeDets,layerDetIds,lnumber,0,0);
      } else if (det_layer_pair.first == "TID" && lnumber > 0) {
	substructure.getTIDDetectors(activeDets,layerDetIds,2,0,abs(lnumber),0);
      } else if (det_layer_pair.first == "TID" && lnumber < 0) {
	substructure.getTIDDetectors(activeDets,layerDetIds,1,0,abs(lnumber),0);
      } else if (det_layer_pair.first == "TEC" && lnumber > 0) {
	substructure.getTECDetectors(activeDets,layerDetIds,2,0,0,0,abs(lnumber),0);
      } else if (det_layer_pair.first == "TEC" && lnumber < 0) {
	substructure.getTECDetectors(activeDets,layerDetIds,1,0,0,0,abs(lnumber),0);
      }
      LayerDetMap[label] = layerDetIds;

      // book Layer MEs 
      // folder_organizer.setLayerFolder(detid,det_layer_pair.second,true);
      curfold = topFolderName_ + det_layer_pair.first;
      folder_organizer.setSiStripFolderName(curfold);
      folder_organizer.setSiStripFolder();
      // std::cout << "curfold " << curfold << std::endl;
      createLayerMEs(label);
    }
    // book sub-detector plots in the same folder for now
    if (SubDetMEsMap.find(det_layer_pair.first) == SubDetMEsMap.end()){
      createSubDetMEs(det_layer_pair.first);        
    }
    //Create StereoAndMatchedMEs
    std::map<std::string, StereoAndMatchedMEs>::iterator iStereoAndMatchedME  = StereoAndMatchedMEsMap.find(label);
    if(iStereoAndMatchedME==StereoAndMatchedMEsMap.end()) {
	
      // get detids for the stereo and matched layer. We are going to need a bool for these layers
      bool isStereo = false;
      // Keep in mind that when we are on the TID or TEC we deal with rings not wheel 
      int32_t stereolnumber = det_layer_pair.second;
      std::vector<uint32_t> stereoandmatchedDetIds;        
      if ( (det_layer_pair.first == "TIB") &&  (TIBDetId(detid).stereo()== 1) ) {
	substructure.getTIBDetectors(activeDets,stereoandmatchedDetIds,stereolnumber,0,0,0);
	isStereo = true;
      } else if ( (det_layer_pair.first == "TOB") &&  (TOBDetId(detid).stereo()== 1) ) {
	substructure.getTOBDetectors(activeDets,stereoandmatchedDetIds,stereolnumber,0,0);
	isStereo = true;
      } else if ( (det_layer_pair.first == "TID") && (stereolnumber > 0) && (TIDDetId(detid).stereo()== 1) ) {
	substructure.getTIDDetectors(activeDets,stereoandmatchedDetIds,2,0,abs(stereolnumber),1);
	isStereo = true;
      } else if ( (det_layer_pair.first == "TID") && (stereolnumber < 0) && (TIDDetId(detid).stereo()== 1) ) {
	substructure.getTIDDetectors(activeDets,stereoandmatchedDetIds,1,0,abs(stereolnumber),1);
	isStereo = true;
      } else if ( (det_layer_pair.first == "TEC") && (stereolnumber > 0) && (TECDetId(detid).stereo()== 1) ) {
	substructure.getTECDetectors(activeDets,stereoandmatchedDetIds,2,0,0,0,abs(stereolnumber),1);
	isStereo = true;
      } else if ( (det_layer_pair.first == "TEC") && (stereolnumber < 0) && (TECDetId(detid).stereo()== 1) ) {
	substructure.getTECDetectors(activeDets,stereoandmatchedDetIds,1,0,0,0,abs(stereolnumber),1);
	isStereo = true;
      }
      StereoAndMatchedDetMap[label] = stereoandmatchedDetIds;

      // book StereoAndMatched MEs 
      // folder_organizer.setLayerFolder(detid,det_layer_pair.second,true);
      curfold = topFolderName_ + det_layer_pair.first;
      folder_organizer.setSiStripFolderName(curfold);
      folder_organizer.setSiStripFolder();
      // std::cout << "curfold " << curfold << std::endl;
      //Create the Monitor Elements only when we have a stereo module
      if(isStereo){
	createStereoAndMatchedMEs(label);
      }
    }
 

  }//end of loop over detectors
}
//------------------------------------------------------------------------------------------
void SiStripRecHitsValid::createTotalMEs() 
{
  totalMEs.meNumTotRphi = 0;
  totalMEs.meNumTotSas = 0;
  totalMEs.meNumTotMatched = 0;

  //NumTotRphi
  if(switchNumTotRphi) {
    totalMEs.meNumTotRphi = bookME1D("TH1NumTotRphi", "TH1NumTotRphi" ,"Num of RecHits");
    totalMEs.meNumTotRphi->setAxisTitle("Total number of RecHits");
  }
  //NumTotSas
  if(switchNumTotSas) {
    totalMEs.meNumTotSas = bookME1D("TH1NumTotSas", "TH1NumTotSas","Num of RecHits sas");
    totalMEs.meNumTotSas ->setAxisTitle("Total number of RecHits in stereo modules");
  }
  //NumTotMatched
  if(switchNumTotMatched) {
    totalMEs.meNumTotMatched = bookME1D("TH1NumTotMatched","TH1NumTotMatched","Num of RecHits rmatched"); 
    totalMEs.meNumTotMatched->setAxisTitle("Total number of matched RecHits");
  }
       
}
//------------------------------------------------------------------------------------------
void SiStripRecHitsValid::createLayerMEs(std::string label) 
{
  SiStripHistoId hidmanager;
  LayerMEs layerMEs; 

  layerMEs.meNstpRphi = 0;
  layerMEs.meAdcRphi = 0;
  layerMEs.mePosxRphi = 0;
  layerMEs.meErrxRphi = 0;
  layerMEs.meResRphi = 0;
  layerMEs.mePullLFRphi = 0;
  layerMEs.mePullMFRphi = 0;
  layerMEs.meChi2Rphi = 0;

  //NstpRphi
  if(switchNstpRphi) {
    layerMEs.meNstpRphi = bookME1D("TH1NstpRphi", hidmanager.createHistoLayer("Nstp_rphi","layer",label,"").c_str() ,"Cluster Width - Number of strips that belong to the RecHit cluster"); 
    layerMEs.meNstpRphi->setAxisTitle(("Cluster Width [nr strips] in "+ label).c_str());
  }
  //AdcRphi
  if(switchAdcRphi) {
    layerMEs.meAdcRphi = bookME1D("TH1AdcRphi", hidmanager.createHistoLayer("Adc_rphi","layer",label,"").c_str() ,"RecHit Cluster Charge");
    layerMEs.meAdcRphi->setAxisTitle(("cluster charge [ADC] in " + label).c_str());
  }
  //PosxRphi
  if(switchPosxRphi) {
    layerMEs.mePosxRphi = bookME1D("TH1PosxRphi", hidmanager.createHistoLayer("Posx_rphi","layer",label,"").c_str() ,"RecHit x coord."); 
    layerMEs.mePosxRphi->setAxisTitle(("x RecHit coord. (local frame) in " + label).c_str());
  }
  //ErrxRphi
  if(switchErrxRphi) {
    layerMEs.meErrxRphi = bookME1D("TH1ErrxRphi", hidmanager.createHistoLayer("Errx_rphi","layer",label,"").c_str() ,"RecHit err(x) coord.");   //<error>~20micron  
    layerMEs.meErrxRphi->setAxisTitle(("err(x) RecHit coord. (local frame) in " + label).c_str());
  }
  //ResRphi
  if(switchResRphi) {
    layerMEs.meResRphi = bookME1D("TH1ResRphi", hidmanager.createHistoLayer("Res_rphi","layer",label,"").c_str() ,"Residuals of the hit x coordinate"); 
    layerMEs.meResRphi->setAxisTitle(("RecHit Res(x) in " + label).c_str());
  }
  //PullLFRphi
  if(switchPullLFRphi) {
    layerMEs.mePullLFRphi = bookME1D("TH1PullLFRphi", hidmanager.createHistoLayer("Pull_LF_rphi","layer",label,"").c_str() ,"Pull distribution");  
    layerMEs.mePullLFRphi->setAxisTitle(("Pull distribution (local frame) in " + label).c_str());
  }
  //PullMFRphi
  if(switchPullMFRphi) {
    layerMEs.mePullMFRphi = bookME1D("TH1PullMFRphi", hidmanager.createHistoLayer("Pull_MF_rphi","layer",label,"").c_str() ,"Pull distribution");  
    layerMEs.mePullMFRphi->setAxisTitle(("Pull distribution (measurement frame) in " + label).c_str());
  }
  //Chi2Rphi
  if(switchChi2Rphi) {
    layerMEs.meChi2Rphi = bookME1D("TH1Chi2Rphi", hidmanager.createHistoLayer("Chi2_rphi","layer",label,"").c_str() ,"RecHit Chi2 test"); 
    layerMEs.meChi2Rphi->setAxisTitle(("RecHit Chi2 test in " + label).c_str()); 
  }

  LayerMEsMap[label]=layerMEs;
 
}
//------------------------------------------------------------------------------------------
void SiStripRecHitsValid::createStereoAndMatchedMEs(std::string label) 
{
  SiStripHistoId hidmanager;
  StereoAndMatchedMEs stereoandmatchedMEs; 

  stereoandmatchedMEs.meNstpSas = 0;
  stereoandmatchedMEs.meAdcSas = 0;
  stereoandmatchedMEs.mePosxSas = 0;
  stereoandmatchedMEs.meErrxSas = 0;
  stereoandmatchedMEs.meResSas = 0;
  stereoandmatchedMEs.mePullLFSas = 0;
  stereoandmatchedMEs.mePullMFSas = 0;
  stereoandmatchedMEs.meChi2Sas = 0;
  stereoandmatchedMEs.mePosxMatched = 0;
  stereoandmatchedMEs.mePosyMatched = 0;
  stereoandmatchedMEs.meErrxMatched = 0;
  stereoandmatchedMEs.meErryMatched = 0;
  stereoandmatchedMEs.meResxMatched = 0;
  stereoandmatchedMEs.meResyMatched = 0;
  stereoandmatchedMEs.meChi2Matched = 0;

  //NstpSas
  if(switchNstpSas) {
    stereoandmatchedMEs.meNstpSas = bookME1D("TH1NstpSas", hidmanager.createHistoLayer("Nstp_sas","layer",label,"").c_str() ,"Cluster Width - Number of strips that belong to the RecHit cluster");  
    stereoandmatchedMEs.meNstpSas->setAxisTitle(("Cluster Width [nr strips] in stereo modules in "+ label).c_str());
  }
  //AdcSas
  if(switchAdcSas) {
    stereoandmatchedMEs.meAdcSas = bookME1D("TH1AdcSas", hidmanager.createHistoLayer("Adc_sas","layer",label,"").c_str() ,"RecHit Cluster Charge"); 
    stereoandmatchedMEs.meAdcSas->setAxisTitle(("cluster charge [ADC] in stereo modules in " + label).c_str());
  }
  //PosxSas
  if(switchPosxSas) {
    stereoandmatchedMEs.mePosxSas = bookME1D("TH1PosxSas", hidmanager.createHistoLayer("Posx_sas","layer",label,"").c_str() ,"RecHit x coord."); 
    stereoandmatchedMEs.mePosxSas->setAxisTitle(("x RecHit coord. (local frame) in stereo modules in " + label).c_str());
  }
  //ErrxSas
  if(switchErrxSas) {
    stereoandmatchedMEs.meErrxSas = bookME1D("TH1ErrxSas", hidmanager.createHistoLayer("Errx_sas","layer",label,"").c_str() ,"RecHit err(x) coord.");  
    stereoandmatchedMEs.meErrxSas->setAxisTitle(("err(x) RecHit coord. (local frame) in stereo modules in " + label).c_str());
  }
  //ResSas
  if(switchResSas) {
    stereoandmatchedMEs.meResSas = bookME1D("TH1ResSas", hidmanager.createHistoLayer("Res_sas","layer",label,"").c_str() ,"Residuals of the hit x coordinate"); 
    stereoandmatchedMEs.meResSas->setAxisTitle(("RecHit Res(x) in stereo modules in " + label).c_str());
  }
  //PullLFSas
  if(switchPullLFSas) {
    stereoandmatchedMEs.mePullLFSas = bookME1D("TH1PullLFSas", hidmanager.createHistoLayer("Pull_LF_sas","layer",label,"").c_str() ,"Pull distribution");  
    stereoandmatchedMEs.mePullLFSas->setAxisTitle(("Pull distribution (local frame) in stereo modules in " + label).c_str());
  }
  //PullMFSas
  if(switchPullMFSas) {
    stereoandmatchedMEs.mePullMFSas = bookME1D("TH1PullMFSas", hidmanager.createHistoLayer("Pull_MF_sas","layer",label,"").c_str() ,"Pull distribution");  
    stereoandmatchedMEs.mePullMFSas->setAxisTitle(("Pull distribution (measurement frame) in stereo modules in " + label).c_str());
  }
  //Chi2Sas
  if(switchChi2Sas) {
    stereoandmatchedMEs.meChi2Sas = bookME1D("TH1Chi2Sas", hidmanager.createHistoLayer("Chi2_sas","layer",label,"").c_str() ,"RecHit Chi2 test");  
    stereoandmatchedMEs.meChi2Sas->setAxisTitle(("RecHit Chi2 test in stereo modules in " + label).c_str()); 
  }
  //PosxMatched
  if(switchPosxMatched) {
    stereoandmatchedMEs.mePosxMatched = bookME1D("TH1PosxMatched", hidmanager.createHistoLayer("Posx_matched","layer",label,"").c_str() ,"RecHit x coord.");  
    stereoandmatchedMEs.mePosxMatched->setAxisTitle(("x coord. matched RecHit (local frame) in " + label).c_str());
  }
  //PosyMatched
  if(switchPosyMatched) {
    stereoandmatchedMEs.mePosyMatched = bookME1D("TH1PosyMatched", hidmanager.createHistoLayer("Posy_matched","layer",label,"").c_str() ,"RecHit y coord."); 
    stereoandmatchedMEs.mePosyMatched->setAxisTitle(("y coord. matched RecHit (local frame) in " + label).c_str());
  }
  //ErrxMatched
  if(switchErrxMatched) {
    stereoandmatchedMEs.meErrxMatched = bookME1D("TH1ErrxMatched", hidmanager.createHistoLayer("Errx_matched","layer",label,"").c_str() ,"RecHit err(x) coord.");  
    stereoandmatchedMEs.meErrxMatched->setAxisTitle(("err(x) coord. matched RecHit (local frame) in " + label).c_str());
  }
  //ErryMatched
  if(switchErryMatched) {
    stereoandmatchedMEs.meErryMatched = bookME1D("TH1ErryMatched", hidmanager.createHistoLayer("Erry_matched","layer",label,"").c_str() ,"RecHit err(y) coord."); 
    stereoandmatchedMEs.meErryMatched->setAxisTitle(("err(y) coord. matched RecHit (local frame) in " + label).c_str());
  }
  //ResxMatched
  if(switchResxMatched) {
    stereoandmatchedMEs.meResxMatched = bookME1D("TH1ResxMatched", hidmanager.createHistoLayer("Resx_matched","layer",label,"").c_str() ,"Residuals of the hit x coord."); 
    stereoandmatchedMEs.meResxMatched->setAxisTitle(("Res(x) in matched RecHit in " + label).c_str());
  }
  //ResyMatched
  if(switchResyMatched) {
    stereoandmatchedMEs.meResyMatched = bookME1D("TH1ResyMatched", hidmanager.createHistoLayer("Resy_matched","layer",label,"").c_str() ,"Residuals of the hit y coord."); 
    stereoandmatchedMEs.meResyMatched->setAxisTitle(("Res(y) in matched RecHit in " + label).c_str());
  }
  //Chi2Matched
  if(switchChi2Matched) {
    stereoandmatchedMEs.meChi2Matched = bookME1D("TH1Chi2Matched", hidmanager.createHistoLayer("Chi2_matched","layer",label,"").c_str() ,"RecHit Chi2 test"); 
    stereoandmatchedMEs.meChi2Matched->setAxisTitle(("Matched RecHit Chi2 test in " + label).c_str()); 
  }

  StereoAndMatchedMEsMap[label]=stereoandmatchedMEs;
 
}
//------------------------------------------------------------------------------------------
void SiStripRecHitsValid::createSubDetMEs(std::string label) {

  SubDetMEs subdetMEs;
  subdetMEs.meNumRphi = 0;
  subdetMEs.meNumSas = 0;
  subdetMEs.meNumMatched = 0;

  std::string HistoName;
  //NumRphi
  if (switchNumRphi){
    HistoName = "TH1NumRphi__" + label;
    subdetMEs.meNumRphi = bookME1D("TH1NumRphi",HistoName.c_str(),"Num of RecHits");
    subdetMEs.meNumRphi->setAxisTitle(("Total number of RecHits in "+ label).c_str());
  }  
  //NumSas
  if (switchNumSas){
    HistoName = "TH1NumSas__" + label;
    subdetMEs.meNumSas = bookME1D("TH1NumSas",HistoName.c_str(),"Num of RecHits in stereo modules");
    subdetMEs.meNumSas->setAxisTitle(("Total number of RecHits in stereo modules in "+ label).c_str());
  }  
  //NumMatched
  if (switchNumMatched){
    HistoName = "TH1NumMatched__" + label;
    subdetMEs.meNumMatched = bookME1D("TH1NumMatched",HistoName.c_str(),"Num of matched RecHits" );
    subdetMEs.meNumMatched->setAxisTitle(("Total number of matched RecHits in "+ label).c_str());
  }  

  SubDetMEsMap[label]=subdetMEs;
}
//------------------------------------------------------------------------------------------
MonitorElement* SiStripRecHitsValid::bookME1D(const char* ParameterSetLabel, const char* HistoName, const char* HistoTitle)
{
  Parameters =  conf_.getParameter<edm::ParameterSet>(ParameterSetLabel);
  return dbe_->book1D(HistoName,HistoTitle,
			   Parameters.getParameter<int32_t>("Nbinx"),
			   Parameters.getParameter<double>("xmin"),
			   Parameters.getParameter<double>("xmax")
			   );
}

//define this as a plug-in
DEFINE_FWK_MODULE(SiStripRecHitsValid);

