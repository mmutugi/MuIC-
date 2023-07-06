//
// Created by om15 on 5/24/23.
//

#include <G4ios.hh>
#include <G4SIunits.hh>
#include "muic/analysis/EnergyDepositCollector.h"

EnergyDepositCollector::EnergyDepositCollector() {
    // Do Nothing
}

EnergyDepositCollector::~EnergyDepositCollector() {
    // Do Nothing
}

void EnergyDepositCollector::onEventStart() {
    // Reset collection
    before_nozzle_collection_.clear();
    after_nozzle_collection_.clear();
    energy_deposit_collection_.clear();
    phi_before_nozzle_collection_.clear();
    phi_after_nozzle_collection_.clear();
    phi_scatter_.clear();
    eta_before_nozzle_collection_.clear();
    eta_after_nozzle_collection_.clear();
    eta_scatter_.clear();
    position_phi_before_nozzle_collection_.clear();
    position_phi_after_nozzle_collection_.clear();
    position_eta_before_nozzle_collection_.clear();
    position_eta_before_nozzle_collection_.clear();
    position_eta_scatter_.clear();
    position_phi_scatter_.clear();
    theta_before_nozzle_.clear();
    theta_after_nozzle_.clear();
    position_theta_before_nozzle_.clear();
    position_theta_after_nozzle_.clear();
    theta_scatter_.clear();
    position_theta_scatter_.clear();
    
}

void EnergyDepositCollector::onEventEnd() {
	for(auto& [track_id, initial_phi] : phi_before_nozzle_collection_){
	G4cout << "Track Id: " << track_id
		<<" angle before the nozzle collection: " << initial_phi / degree
		<< " angle after the nozzle collection " << phi_after_nozzle_collection_[track_id] / degree
		<< "phi scatter"<< (phi_after_nozzle_collection_[track_id] - initial_phi)
		<< G4endl;
	
	
	}

	for (auto& [track_id, initial_eta] : eta_before_nozzle_collection_){
	G4cout << "Track Id: " << track_id
	       << " eta before the nozzle collection: " << initial_eta
               <<" eta after the nozzle collection: "	<< eta_after_nozzle_collection_[track_id]
	       << "eta_scatter"<< (eta_after_nozzle_collection_[track_id] - initial_eta)
	       << G4endl;

	}	
     for (auto& [track_id, position_initial_phi]: position_phi_before_nozzle_collection_){
	     G4cout <<"Track Id:" <<track_id
		     <<"Position Phi before Nozzle Collection:"<< position_initial_phi
		     <<"Position Phi after nozzle collection"<< position_phi_after_nozzle_collection_[track_id]
		     <<"position Phi Scatter"<< (position_phi_after_nozzle_collection_[track_id] - position_initial_phi)
		     <<G4endl;
	
	}
     for (auto& [track_id, position_initial_eta]: position_eta_before_nozzle_collection_){
              G4cout<< "Track Id:" << track_id
		     <<"Position eta before Nozzle Collection:"<< position_initial_eta
		     << "Position Initial Eta after Nozzle collection"<< position_eta_after_nozzle_collection_[track_id]
		     <<"position Eta scattering"<< (position_eta_after_nozzle_collection_[track_id] - position_initial_eta)
	             <<G4endl;
	 
		     }

     for (auto& [track_id,initial_theta]:theta_before_nozzle_) {
          G4cout << "Track ID:" <<track_id
		  <<"theta before nozzle collection" << initial_theta
		  <<"theta after nozzle collection "<< theta_after_nozzle_[track_id]
		  <<"theta scattering"<<(theta_after_nozzle_[track_id] - theta_before_nozzle_[track_id]) / degree
		  <<G4endl;

     
     
     }
	
   for(auto&[track_id, position_initial_theta] : position_theta_before_nozzle_){
     G4cout <<"Track ID" << track_id
	     <<"position theta before nozzle collection"<< position_initial_theta
	     <<"position theta after nozzle collection"<< position_theta_after_nozzle_[track_id]
	     <<"positiom theta scattering"<<(position_theta_after_nozzle_[track_id] - position_theta_before_nozzle_[track_id]) /degree
	     <<G4endl;

}	

    for (auto& [track_id, deposit] : energy_deposit_collection_) {
        G4cout << "Track Id: " << track_id
        << " Deposit: " << deposit / GeV
        << " Before: " << before_nozzle_collection_[track_id] / GeV
        << " After: " << after_nozzle_collection_[track_id] / GeV
        << " Loss: " << (before_nozzle_collection_[track_id] - after_nozzle_collection_[track_id]) / GeV
        << G4endl;
    }
}

void EnergyDepositCollector::setEtaBeforeNozzle(const unsigned int & track_id, const G4double & eta) {
    eta_before_nozzle_collection_[track_id] = eta;
}

void EnergyDepositCollector::setEtaAfterNozzle(const unsigned int & track_id, const G4double & eta) {
    eta_after_nozzle_collection_[track_id] = eta;
}
void EnergyDepositCollector::setPhiBeforeNozzle(const unsigned int & track_id, const G4double & phi) {
    phi_before_nozzle_collection_[track_id] = phi;
}

void EnergyDepositCollector::setPhiAfterNozzle(const unsigned int & track_id, const G4double & phi) {
    phi_after_nozzle_collection_[track_id] = phi;
}
void EnergyDepositCollector::setEnergyBeforeNozzle(const unsigned int & track_id, const G4double & energy) {
    before_nozzle_collection_[track_id] = energy;
}

void EnergyDepositCollector::setEnergyAfterNozzle(const unsigned int & track_id, const G4double & energy) {
    after_nozzle_collection_[track_id] = energy;
}

void EnergyDepositCollector::addEnergyDeposit(const unsigned int & track_id, const G4double & energy) {
    auto energy_deposit_it = energy_deposit_collection_.find(track_id); 

 // Fetch previous energy deposit
    G4double deposit = 0.;

    if (energy_deposit_it != energy_deposit_collection_.end()) {
        deposit += energy_deposit_it->second;
    } 

    // Accumulate energy
    deposit += energy;

    // Record new energy deposit
    energy_deposit_collection_[track_id] = deposit;

}

 /*void EnergyDepositCollector::addPhiBending (const unsigned int & track_id, const G4double &energy) {
	 auto phi_bending = energy_deposit_collection_.find(track_id);
 }
void EnergyDepositCollector::addEtaBending (const unsigned int & track_id, const G4double &energy) {
	auto eta_bending = energy_deposit_collection_.find(track_id);


}*/
void EnergyDepositCollector::setPositionPhiBeforeNozzle(const unsigned int & track_id, const G4double &phi){
	position_phi_before_nozzle_collection_[track_id] = phi;}

void EnergyDepositCollector::setPositionPhiAfterNozzle(const unsigned int & track_id, const G4double &phi){
	position_phi_after_nozzle_collection_[track_id]=phi ;}

void EnergyDepositCollector::setPositionEtaBeforeNozzle(const unsigned int &track_id, const G4double & eta){
	position_eta_before_nozzle_collection_[track_id] = eta;}

void EnergyDepositCollector::setPositionEtaAfterNozzle(const unsigned int & track_id, const G4double &eta){
	position_eta_after_nozzle_collection_[track_id] =eta ;}
void EnergyDepositCollector::setThetaBeforeNozzle(const unsigned int &track_id, const G4double &theta){
	theta_before_nozzle_[track_id] = theta ;
}
void EnergyDepositCollector::setThetaAfterNozzle (const unsigned int &track_id, const G4double &theta){
	theta_after_nozzle_[track_id] = theta;
}
void EnergyDepositCollector::setPositionThetaBeforeNozzle(const unsigned int &track_id ,const G4double &theta){
	position_theta_before_nozzle_[track_id] = theta;
}
void EnergyDepositCollector::setPositionThetaAfterNozzle( const unsigned int &track_id,const  G4double &theta){
	position_theta_after_nozzle_[track_id] = theta;
}
	

  

