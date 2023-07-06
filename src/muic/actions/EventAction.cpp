#include "G4Event.hh"
#include "G4ios.hh"
#include <G4SDManager.hh>
#include "muic/simulation/CSCSimHit.h"
#include "muic/MuICContext.h"

#include "muic/actions/EventAction.h"

namespace muic {
    EventAction::EventAction(MuICContext *context)
            : G4UserEventAction(), context_(context) {
        print_every_n_events_ = 100;
    }


    EventAction::~EventAction() {
        // Do Nothing
    }


    void EventAction::BeginOfEventAction(const G4Event *evt) {
        G4int event_id = evt->GetEventID();

        if (event_id % print_every_n_events_ == 0) {
            G4cout << "Begin of event: " << event_id << G4endl;
        }

        // Propagate Event Start Signal
        context_->ntuple_maker_.onEventStart();
        context_->energy_deposit_collector_.onEventStart();
    }


    void EventAction::EndOfEventAction(const G4Event *evt) {
        // Save Nozzle Muons
        for (const auto& [track_id, energy_deposited] : context_->energy_deposit_collector_.energy_deposit_collection_) {
            const auto& energy_before = context_->energy_deposit_collector_.before_nozzle_collection_[track_id];
            const auto& energy_after = context_->energy_deposit_collector_.after_nozzle_collection_[track_id];
	    const auto& phi_before = context_->energy_deposit_collector_.phi_before_nozzle_collection_[track_id];
	    const auto& phi_after = context_->energy_deposit_collector_.phi_after_nozzle_collection_[track_id];
	    const auto& eta_before = context_->energy_deposit_collector_.eta_before_nozzle_collection_[track_id];
	    const auto& eta_after = context_->energy_deposit_collector_.eta_after_nozzle_collection_[track_id];
	   
	    const auto& position_phi_before = context_->energy_deposit_collector_.position_phi_before_nozzle_collection_[track_id];
	    const auto& position_phi_after = context_->energy_deposit_collector_.position_phi_after_nozzle_collection_[track_id];
	    const auto& position_eta_before = context_->energy_deposit_collector_.position_eta_before_nozzle_collection_[track_id];
	    const auto& position_eta_after = context_->energy_deposit_collector_. position_eta_after_nozzle_collection_[track_id];
	    const auto& theta_before_nozzle = context_-> energy_deposit_collector_.theta_before_nozzle_[track_id];
	    const auto& theta_after_nozzle = context_-> energy_deposit_collector_. theta_after_nozzle_[track_id];
	    const auto& position_theta_before_nozzle = context_-> energy_deposit_collector_.position_theta_before_nozzle_[track_id];
	    const auto& position_theta_after_nozzle = context_->energy_deposit_collector_.position_theta_after_nozzle_[track_id];
	   




            context_->ntuple_maker_.addGenMuon(
                    energy_before,
                    energy_after,
                    energy_deposited,
		    phi_before,
		    phi_after,
		    eta_before,
		    eta_after,
		   
		    position_phi_before,
		    position_phi_after,
		    position_eta_before,
		    position_eta_after,
		    theta_before_nozzle,
		    theta_after_nozzle,
		    position_theta_before_nozzle,
		    position_theta_after_nozzle
		   

		   

            );
        }

        // Propagate Event End Signal
        context_->energy_deposit_collector_.onEventEnd();
        context_->ntuple_maker_.onEventEnd();
    }
}
