#ifndef MuIC_NtupleMaker_h
#define MuIC_NtupleMaker_h

#include "globals.hh"
#include <vector>


class TFile;

class TTree;

namespace muic {
    class NtupleMaker {
    public:
        NtupleMaker();

        ~NtupleMaker();

        void onRunStart();

        void onRunEnd();

        void onEventStart();

        void addGenMuon(
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
        );

        void onEventEnd();

    private:
        // Metadata
        int n_events_ = 0;

        // Events
        int n_gen_ = 0;
        std::vector<double> gen_e_deposited_nozzle_;
        std::vector<double> gen_e_after_nozzle_;
        std::vector<double> gen_e_before_nozzle_;
	std::vector<double> gen_phi_before_nozzle_;
	std::vector<double> gen_phi_after_nozzle_;
	std::vector<double> gen_phi_scatter_;
	std::vector<double> gen_eta_before_nozzle_;
	std::vector< double> gen_eta_after_nozzle_;
	std::vector <double> gen_eta_scatter_;
	std::vector<double> position_phi_before_nozzle_;
	std::vector<double> position_phi_after_nozzle_;
	std::vector<double>position_eta_before_nozzle_;
	std::vector<double>position_eta_after_nozzle_;
	std::vector<double> position_eta_scatter_;
	std::vector<double>position_phi_scatter_;
	std::vector<double> theta_before_nozzle_;
	std::vector<double>theta_after_nozzle_;
	std::vector <double> position_theta_before_nozzle_;
	std::vector <double> position_theta_after_nozzle_;
	std::vector <double> theta_scatter_;
	std::vector <double> position_theta_scatter_;

    };
}


#endif
