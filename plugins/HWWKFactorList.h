#ifndef DataFormats_ParticleFlowReco_HWWKfactorList_h
#define DataFormats_ParticleFlowReco_HWWKfactorList_h

#include <iostream>
#include <string>
#include <stdexcept>

#include <TH1.h>



/// \brief Resolution Map (resolution as a function of eta and E)
///
/// Basically just a TH1D with text I/O
/// \author Joanna Weng
/// \todo extrapolation
/// \date January 2006
class HWWKfactorList : public TH1D {

 public:

  /// default constructor
  HWWKfactorList() : TH1D() {}
  
  /// create a map from text file mapfile
  HWWKfactorList(const char* name, const char* mapfile);
  
  /// create an empty map and initialize it 
  HWWKfactorList(const char* name, 
		  unsigned nbinspt, double minpt, double maxpt, double value);
  
  /// create a map from a 1d histogram
  HWWKfactorList(const TH1D& h) : TH1D(h) {}
 

  /// read text file
  bool ReadMapFile(const char* mapfile);

  /// write text file
  /// is not const because mapFile_ will be updated
  bool WriteMapFile(const char* mapfile);

  
  const char* GetMapFile() const {return mapFile_.c_str();}

  /// print this map
  friend std::ostream& operator<<(std::ostream& out, const HWWKfactorList& rm);
  
 private:
  static const unsigned lineSize_;

  std::string           mapFile_;
  
};

#endif


