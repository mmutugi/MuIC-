#include "muic/detector/World.h"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Colour.hh"
#include "G4FieldManager.hh"
#include "G4GenericMessenger.hh"
#include "G4Orb.hh"
#include "G4Polyline.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4Sphere.hh"
#include "G4SubtractionSolid.hh"
#include "G4TransportationManager.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"

#include "muic/setup/DetectorConstruction.h"
#include "muic/detector/Nozzle.h"
#include "muic/detector/IronShielding.h"

using namespace muic;

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {
    // Do Nothing
}

DetectorConstruction::~DetectorConstruction() {
    // Do Nothing
}

G4VPhysicalVolume *DetectorConstruction::Construct() {
    auto *world = muic::create_world();
    muic::create_nozzle(world);
    muic::create_shielding(world);

    return world;
}

void DetectorConstruction::ConstructSDandField() {
    // Get Sensitive Detector Manager
    auto *sd_manager = G4SDManager::GetSDMpointer();
    sd_manager->SetVerboseLevel(0);
}

