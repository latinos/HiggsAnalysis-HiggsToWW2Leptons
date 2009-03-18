#include "HiggsAnalysis/HiggsToWW2Leptons/plugins/HWWKFactorList.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <stdexcept>

using namespace std;


const unsigned HWWKfactorList::lineSize_ = 10000;


HWWKfactorList::HWWKfactorList(const char* name, unsigned nbinspt,
                               double minpt, double maxpt, double value)
    : TH1D(name, name, nbinspt, minpt, maxpt)
{

  GetXaxis()->SetTitle("#pt");
  GetYaxis()->SetTitle("Kfactor");
  if(value>0)
  {
    for(int ieta=1; ieta<=GetNbinsX(); ieta++)
    {
      SetBinContent(ieta, value);
    }
  }

}

HWWKfactorList::HWWKfactorList(const char* name, const char* mapfile)
{

  SetTitle(mapfile);
  GetXaxis()->SetTitle("#eta");
  GetYaxis()->SetTitle("E");
  if( ! ReadMapFile(mapfile) )
  {
    string err = "HWWKfactorList::HWWKfactorList : cannot read file ";
    err += mapfile;
    throw invalid_argument(err);
  }
}


bool HWWKfactorList::WriteMapFile(const char* mapfile)
{
  // open the file
  ofstream outf(mapfile);
  if( !outf.good() )
  {
    cout<<"HWWKfactorList::Write : cannot open file "<<mapfile<<endl;
    return false;
  }

  outf<<(*this)<<endl;
  if(!outf.good() )
  {
    cerr<<"HWWKfactorList::Write : corrupted file "<<mapfile<<endl;
    return false;
  }
  else
  {
    mapFile_ = mapfile;
    return true;
  }
}



bool HWWKfactorList::ReadMapFile(const char* mapfile)
{
  // open the file
  ifstream inf(mapfile);
  if( !inf.good() )
  {
    return false;
  }
  // first data describes the map: histo bin, max, min
  int nbinspt=0;
  double minpt=0;
  double maxpt=0;
  inf>>nbinspt;
  inf>>minpt;
  inf>>maxpt;
  SetBins(nbinspt, minpt, maxpt);

  char s[lineSize_];
  // get position in stream
  int pos=inf.tellg(); int j=0;
  // parse map data
  do
  {
    inf.seekg(pos);
    inf.getline(s,lineSize_);
    pos = inf.tellg();
    //    cout<<"LINE"<< s<<endl;
    if(string(s).empty())
    {
      continue; // remove empty lines
    }
    istringstream lin(s);
    double dataw;

    if (lin.good())
    {
      lin>>dataw;   lin>>dataw;
      //  cout<<"LINE "<<dataw <<endl;
      SetBinContent(j, dataw);
      j++;
    }

  }
  while(inf.good());

  if(inf.eof())
  {
    mapFile_ = mapfile;
    return true;
  }
  else return false;
  mapFile_ = mapfile;
  return true;
}




ostream& operator<<(ostream& outf, const HWWKfactorList& rm)
{

  if(!outf.good() ) return outf;

  // first data describes the map
  outf<<rm.GetNbinsX()<<endl;
  outf<<rm.GetXaxis()->GetXmin()<<endl;
  outf<<rm.GetXaxis()->GetXmax()<<endl;

  for(int ieta=0; ieta<=rm.GetNbinsX(); ieta++){
    outf<<ieta<<" "<<rm.GetBinContent(ieta)<<"\t";
  }
  outf<<endl;
  return outf;
}
