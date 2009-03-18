import FWCore.ParameterSet.Config as cms

KFactorProducer = cms.EDProducer("HWWKFactorProducer",
                                 inputFilename = cms.untracked.string('HiggsAnalysis/HiggsToWW2Leptons/data/test.dat'),
                                 # PYTHIA Process to apply KFactor
                                 ProcessID = cms.untracked.int32(102),
                                 Debug =cms.untracked.bool(False)
                                 )
