#include "diplomat_nanobind_common.hpp"


#include "FeatureType.hpp"

namespace ecitygml {
void add_FeatureType_binding(nb::module_ mod) {
    nb::class_<ecitygml::FeatureType> e_class(mod, "FeatureType", "Type of a CityGML feature.");
    
        nb::enum_<ecitygml::FeatureType::Value> enumerator(e_class, "FeatureType");
        enumerator
            .value("Appearance", ecitygml::FeatureType::Appearance)
            .value("AuxiliaryTrafficArea", ecitygml::FeatureType::AuxiliaryTrafficArea)
            .value("AuxiliaryTrafficSpace", ecitygml::FeatureType::AuxiliaryTrafficSpace)
            .value("Bridge", ecitygml::FeatureType::Bridge)
            .value("BridgeConstructiveElement", ecitygml::FeatureType::BridgeConstructiveElement)
            .value("BridgeFurniture", ecitygml::FeatureType::BridgeFurniture)
            .value("BridgeInstallation", ecitygml::FeatureType::BridgeInstallation)
            .value("BridgePart", ecitygml::FeatureType::BridgePart)
            .value("BridgeRoom", ecitygml::FeatureType::BridgeRoom)
            .value("Building", ecitygml::FeatureType::Building)
            .value("BuildingConstructiveElement", ecitygml::FeatureType::BuildingConstructiveElement)
            .value("BuildingFurniture", ecitygml::FeatureType::BuildingFurniture)
            .value("BuildingInstallation", ecitygml::FeatureType::BuildingInstallation)
            .value("BuildingPart", ecitygml::FeatureType::BuildingPart)
            .value("BuildingRoom", ecitygml::FeatureType::BuildingRoom)
            .value("BuildingUnit", ecitygml::FeatureType::BuildingUnit)
            .value("CeilingSurface", ecitygml::FeatureType::CeilingSurface)
            .value("CityFurniture", ecitygml::FeatureType::CityFurniture)
            .value("CityModel", ecitygml::FeatureType::CityModel)
            .value("CityObjectGroup", ecitygml::FeatureType::CityObjectGroup)
            .value("ClearanceSpace", ecitygml::FeatureType::ClearanceSpace)
            .value("ClosureSurface", ecitygml::FeatureType::ClosureSurface)
            .value("Door", ecitygml::FeatureType::Door)
            .value("DoorSurface", ecitygml::FeatureType::DoorSurface)
            .value("FloorSurface", ecitygml::FeatureType::FloorSurface)
            .value("GenericLogicalSpace", ecitygml::FeatureType::GenericLogicalSpace)
            .value("GenericOccupiedSpace", ecitygml::FeatureType::GenericOccupiedSpace)
            .value("GenericThematicSurface", ecitygml::FeatureType::GenericThematicSurface)
            .value("GenericUnoccupiedSpace", ecitygml::FeatureType::GenericUnoccupiedSpace)
            .value("GeoreferencedTexture", ecitygml::FeatureType::GeoreferencedTexture)
            .value("GroundSurface", ecitygml::FeatureType::GroundSurface)
            .value("Hole", ecitygml::FeatureType::Hole)
            .value("HoleSurface", ecitygml::FeatureType::HoleSurface)
            .value("HollowSpace", ecitygml::FeatureType::HollowSpace)
            .value("InteriorWallSurface", ecitygml::FeatureType::InteriorWallSurface)
            .value("Intersection", ecitygml::FeatureType::Intersection)
            .value("LandUse", ecitygml::FeatureType::LandUse)
            .value("Marking", ecitygml::FeatureType::Marking)
            .value("OtherConstruction", ecitygml::FeatureType::OtherConstruction)
            .value("OuterCeilingSurface", ecitygml::FeatureType::OuterCeilingSurface)
            .value("OuterFloorSurface", ecitygml::FeatureType::OuterFloorSurface)
            .value("ParameterizedTexture", ecitygml::FeatureType::ParameterizedTexture)
            .value("PlantCover", ecitygml::FeatureType::PlantCover)
            .value("PointCloud", ecitygml::FeatureType::PointCloud)
            .value("Railway", ecitygml::FeatureType::Railway)
            .value("ReliefFeature", ecitygml::FeatureType::ReliefFeature)
            .value("Road", ecitygml::FeatureType::Road)
            .value("RoofSurface", ecitygml::FeatureType::RoofSurface)
            .value("Section", ecitygml::FeatureType::Section)
            .value("SolitaryVegetationObject", ecitygml::FeatureType::SolitaryVegetationObject)
            .value("Square", ecitygml::FeatureType::Square)
            .value("Storey", ecitygml::FeatureType::Storey)
            .value("TinRelief", ecitygml::FeatureType::TinRelief)
            .value("Track", ecitygml::FeatureType::Track)
            .value("TrafficArea", ecitygml::FeatureType::TrafficArea)
            .value("TrafficSpace", ecitygml::FeatureType::TrafficSpace)
            .value("Tunnel", ecitygml::FeatureType::Tunnel)
            .value("TunnelConstructiveElement", ecitygml::FeatureType::TunnelConstructiveElement)
            .value("TunnelFurniture", ecitygml::FeatureType::TunnelFurniture)
            .value("TunnelInstallation", ecitygml::FeatureType::TunnelInstallation)
            .value("TunnelPart", ecitygml::FeatureType::TunnelPart)
            .value("WallSurface", ecitygml::FeatureType::WallSurface)
            .value("WaterBody", ecitygml::FeatureType::WaterBody)
            .value("WaterGroundSurface", ecitygml::FeatureType::WaterGroundSurface)
            .value("WaterSurface", ecitygml::FeatureType::WaterSurface)
            .value("Waterway", ecitygml::FeatureType::Waterway)
            .value("Window", ecitygml::FeatureType::Window)
            .value("WindowSurface", ecitygml::FeatureType::WindowSurface)
            .value("X3DMaterial", ecitygml::FeatureType::X3DMaterial)
            .export_values();
    
        e_class
            .def(nb::init_implicit<ecitygml::FeatureType::Value>())
            .def(nb::self == ecitygml::FeatureType::Value())
            .def("__repr__", [](const ecitygml::FeatureType& self){
                return nb::str(nb::cast(ecitygml::FeatureType::Value(self)));
            });
}

} 