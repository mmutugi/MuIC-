#include <G4SIunits.hh>
#include "G4ios.hh"
#include <g4root_defs.hh>
#include <G4GenericAnalysisManager.hh>

#include "muic/analysis/NtupleMaker.h"

namespace muic {
    NtupleMaker::NtupleMaker() {
        auto *manager = G4GenericAnalysisManager::Instance();

        //
        manager->SetFirstNtupleId(0);
        manager->SetFirstNtupleColumnId(0);

        // Init metadata tree
        manager->CreateNtuple("metadata", "Metadata");
        manager->CreateNtupleIColumn("vsize_evt");
        manager->FinishNtuple();

        // Init event tree
        manager->CreateNtuple("events", "Events");
        manager->CreateNtupleIColumn("vsize_gen");
        manager->CreateNtupleDColumn("gen_e_before_nozzle", gen_e_before_nozzle_);
        manager->CreateNtupleDColumn("gen_e_after_nozzle", gen_e_after_nozzle_);
        manager->CreateNtupleDColumn("gen_e_deposited_nozzle", gen_e_deposited_nozzle_);
        manager->CreateNtupleDColumn("gen_phi_before_nozzle", gen_phi_before_nozzle_);
	manager->CreateNtupleDColumn("gen_phi_after_nozzle", gen_phi_after_nozzle_);
	manager->CreateNtupleDColumn("gen_phi_scatter",gen_phi_scatter_);
	manager->CreateNtupleDColumn("gen_eta_before_nozzle", gen_eta_before_nozzle_);
	manager->CreateNtupleDColumn("gen_eta_after_nozzle", gen_eta_after_nozzle_);
	manager->CreateNtupleDColumn ("gen_eta_scatter", gen_eta_scatter_);
	manager->CreateNtupleDColumn("gen_position_phi_before_nozzle", position_phi_before_nozzle_);
	manager->CreateNtupleDColumn("gen_position_phi_after_nozzle", position_phi_after_nozzle_);
	manager->CreateNtupleDColumn("gen_position_eta_before_nozzle",position_eta_before_nozzle_);
	manager->CreateNtupleDColumn("gen_position_eta_after_nozzle",position_eta_after_nozzle_);
	manager->CreateNtupleDColumn("gen_position_phi_scattering", position_phi_scatter_);
	manager->CreateNtupleDColumn("gen_position_eta_scattering",position_eta_scatter_);
	manager->CreateNtupleDColumn ("theta_before_nozzle",theta_before_nozzle_);
	manager->CreateNtupleDColumn ("theta_after_nozzle", theta_after_nozzle_);
	manager ->CreateNtupleDColumn("position_theta_before_nozzle", position_theta_before_nozzle_);
	manager->CreateNtupleDColumn( "position theta after nozzle ", position_theta_after_nozzle_);
	manager->CreateNtupleDColumn("theta_scatter",theta_scatter_);
	manager->CreateNtupleDColumn("position_theta_scatter",position_theta_scatter_);

	


        manager->FinishNtuple();

        // Open File
        auto file_open = manager->OpenFile("muic_ntuple.root");

        if (!file_open) {
            G4cout << "Failed to open file." << G4endl;
            return;
        }
    }

    NtupleMaker::~NtupleMaker() {
        // Do Nothing
    }

    void NtupleMaker::onRunStart() {
        // Do Nothing
    }

    void NtupleMaker::onRunEnd() {
        auto *analysis_manager = G4GenericAnalysisManager::Instance();

        G4cout << "Writing Ntuple." << G4endl;
        analysis_manager->Write();

        G4cout << "Closing Root File." << G4endl;
        analysis_manager->CloseFile();
    }

    void NtupleMaker::onEventStart() {
        // Increase number of events
        n_events_ += 1;

        // Nozzle Energy Deposit
        n_gen_ = 0;
        gen_e_before_nozzle_.clear();
        gen_e_after_nozzle_.clear();
        gen_e_deposited_nozzle_.clear();
	gen_phi_before_nozzle_.clear();
	gen_phi_after_nozzle_.clear();
	gen_phi_scatter_.clear();
	gen_eta_before_nozzle_.clear();
	gen_eta_after_nozzle_.clear();
	gen_eta_scatter_.clear();
	
	 position_phi_before_nozzle_.clear();
	 position_phi_after_nozzle_.clear();
	 position_eta_before_nozzle_.clear();
	 position_eta_after_nozzle_.clear();
	 position_eta_scatter_.clear();
	 position_phi_scatter_.clear();
	 theta_before_nozzle_.clear();
	 theta_after_nozzle_.clear();
	 position_theta_before_nozzle_.clear();
	 position_theta_after_nozzle_.clear();

	 theta_scatter_.clear();
	 position_theta_scatter_.clear();
	 

    }

    void NtupleMaker::onEventEnd() {
        auto *manager = G4GenericAnalysisManager::Instance();

        // Fill Metadata Ntuple
        manager->FillNtupleIColumn(0, 0, n_events_);
        manager->AddNtupleRow(0);

        // Fill Event ntuple
        manager->FillNtupleIColumn(1, 0, n_gen_);
        manager->AddNtupleRow(1);
    }

    void NtupleMaker::addGenMuon(
            const G4double &energy_before_nozzle,
            const G4double &energy_after_nozzle,
            const G4double &energy_deposited_nozzle,
	    const G4double &phi_before_nozzle,
	    const G4double &phi_after_nozzle,
	    const G4double &eta_before_nozzle,
	    const G4double &eta_after_nozzle,
	    
	    
	     const G4double &position_phi_before_nozzle,
	     const G4double &position_phi_after_nozzle,
	     const G4double &position_eta_before_nozzle,
	     const G4double &position_eta_after_nozzle,
	     const G4double &theta_before_nozzle,
	     const G4double &theta_after_nozzle,
	     const G4double &position_theta_before_nozzle,
	     const G4double &position_theta_after_nozzle
	     
	      

    ) {
	G4double  phi_scatter = (phi_before_nozzle - phi_after_nozzle);
	if(phi_scatter > 180) 
		phi_scatter += -360.0;
	else if (phi_scatter < -180)
		phi_scatter +=360.0;

         G4double eta_scatter = (eta_before_nozzle - eta_after_nozzle);
	 G4double position_eta_scatter = (position_eta_before_nozzle - position_eta_after_nozzle);
	 G4double position_phi_scatter = (position_phi_before_nozzle - position_phi_after_nozzle);
	 
	if(position_phi_scatter > 180) 
		position_phi_scatter += -360.0;
	else if (position_phi_scatter < -180)
		position_phi_scatter +=360.0;

	G4double theta_scatter = (theta_before_nozzle - theta_after_nozzle);

	if(theta_scatter > 180) 
		theta_scatter += -360.0;
	else if (theta_scatter < -180)
		theta_scatter +=360.0;


	G4double position_theta_scatter = (position_theta_before_nozzle - position_theta_after_nozzle);

	if(position_theta_scatter > 180) 
		position_theta_scatter += -360.0;
	else if (position_theta_scatter < -180)
		position_theta_scatter +=360.0;

        n_gen_ += 1;
        gen_e_before_nozzle_.push_back(energy_before_nozzle / GeV);
        gen_e_after_nozzle_.push_back(energy_after_nozzle / GeV);
        gen_e_deposited_nozzle_.push_back(energy_deposited_nozzle / GeV);
	gen_phi_before_nozzle_.push_back(phi_before_nozzle / degree);
	gen_phi_after_nozzle_.push_back(phi_after_nozzle / degree);
	gen_phi_scatter_.push_back(phi_scatter /degree);
	gen_eta_before_nozzle_.push_back(eta_before_nozzle);
	gen_eta_after_nozzle_.push_back(eta_after_nozzle);
	gen_eta_scatter_.push_back(eta_scatter);
	position_eta_scatter_.push_back(position_eta_scatter);
	position_phi_scatter_.push_back(position_phi_scatter / degree);


	
	position_phi_before_nozzle_.push_back(position_phi_before_nozzle /degree);
	position_phi_after_nozzle_.push_back(position_phi_after_nozzle / degree);
	position_eta_before_nozzle_.push_back(position_eta_before_nozzle);
        position_eta_after_nozzle_.push_back(position_eta_after_nozzle);
	theta_before_nozzle_.push_back(theta_before_nozzle / degree );
	theta_after_nozzle_.push_back(theta_after_nozzle /degree);
	position_theta_before_nozzle_.push_back(position_theta_before_nozzle / degree);
	position_theta_after_nozzle_.push_back(position_theta_after_nozzle / degree);

	theta_scatter_.push_back(theta_scatter /degree);
	position_theta_scatter_.push_back(position_theta_scatter / degree);


	 
    }

}
