#ifndef ecitygml_FeatureType_HPP
#define ecitygml_FeatureType_HPP

#include "FeatureType.d.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    extern "C" {

    void ecitygml_FeatureType_to_string(ecitygml::capi::FeatureType self, diplomat::capi::DiplomatWrite* write);

    } // extern "C"
} // namespace capi
} // namespace

inline ecitygml::capi::FeatureType ecitygml::FeatureType::AsFFI() const {
    return static_cast<ecitygml::capi::FeatureType>(value);
}

inline ecitygml::FeatureType ecitygml::FeatureType::FromFFI(ecitygml::capi::FeatureType c_enum) {
    switch (c_enum) {
        case ecitygml::capi::FeatureType_Appearance:
        case ecitygml::capi::FeatureType_AuxiliaryTrafficArea:
        case ecitygml::capi::FeatureType_AuxiliaryTrafficSpace:
        case ecitygml::capi::FeatureType_Bridge:
        case ecitygml::capi::FeatureType_BridgeConstructiveElement:
        case ecitygml::capi::FeatureType_BridgeFurniture:
        case ecitygml::capi::FeatureType_BridgeInstallation:
        case ecitygml::capi::FeatureType_BridgePart:
        case ecitygml::capi::FeatureType_BridgeRoom:
        case ecitygml::capi::FeatureType_Building:
        case ecitygml::capi::FeatureType_BuildingConstructiveElement:
        case ecitygml::capi::FeatureType_BuildingFurniture:
        case ecitygml::capi::FeatureType_BuildingInstallation:
        case ecitygml::capi::FeatureType_BuildingPart:
        case ecitygml::capi::FeatureType_BuildingRoom:
        case ecitygml::capi::FeatureType_BuildingUnit:
        case ecitygml::capi::FeatureType_CeilingSurface:
        case ecitygml::capi::FeatureType_CityFurniture:
        case ecitygml::capi::FeatureType_CityModel:
        case ecitygml::capi::FeatureType_CityObjectGroup:
        case ecitygml::capi::FeatureType_ClearanceSpace:
        case ecitygml::capi::FeatureType_ClosureSurface:
        case ecitygml::capi::FeatureType_Door:
        case ecitygml::capi::FeatureType_DoorSurface:
        case ecitygml::capi::FeatureType_FloorSurface:
        case ecitygml::capi::FeatureType_GenericLogicalSpace:
        case ecitygml::capi::FeatureType_GenericOccupiedSpace:
        case ecitygml::capi::FeatureType_GenericThematicSurface:
        case ecitygml::capi::FeatureType_GenericUnoccupiedSpace:
        case ecitygml::capi::FeatureType_GeoreferencedTexture:
        case ecitygml::capi::FeatureType_GroundSurface:
        case ecitygml::capi::FeatureType_Hole:
        case ecitygml::capi::FeatureType_HoleSurface:
        case ecitygml::capi::FeatureType_HollowSpace:
        case ecitygml::capi::FeatureType_InteriorWallSurface:
        case ecitygml::capi::FeatureType_Intersection:
        case ecitygml::capi::FeatureType_LandUse:
        case ecitygml::capi::FeatureType_Marking:
        case ecitygml::capi::FeatureType_OtherConstruction:
        case ecitygml::capi::FeatureType_OuterCeilingSurface:
        case ecitygml::capi::FeatureType_OuterFloorSurface:
        case ecitygml::capi::FeatureType_ParameterizedTexture:
        case ecitygml::capi::FeatureType_PlantCover:
        case ecitygml::capi::FeatureType_PointCloud:
        case ecitygml::capi::FeatureType_Railway:
        case ecitygml::capi::FeatureType_ReliefFeature:
        case ecitygml::capi::FeatureType_Road:
        case ecitygml::capi::FeatureType_RoofSurface:
        case ecitygml::capi::FeatureType_Section:
        case ecitygml::capi::FeatureType_SolitaryVegetationObject:
        case ecitygml::capi::FeatureType_Square:
        case ecitygml::capi::FeatureType_Storey:
        case ecitygml::capi::FeatureType_TinRelief:
        case ecitygml::capi::FeatureType_Track:
        case ecitygml::capi::FeatureType_TrafficArea:
        case ecitygml::capi::FeatureType_TrafficSpace:
        case ecitygml::capi::FeatureType_Tunnel:
        case ecitygml::capi::FeatureType_TunnelConstructiveElement:
        case ecitygml::capi::FeatureType_TunnelFurniture:
        case ecitygml::capi::FeatureType_TunnelInstallation:
        case ecitygml::capi::FeatureType_TunnelPart:
        case ecitygml::capi::FeatureType_WallSurface:
        case ecitygml::capi::FeatureType_WaterBody:
        case ecitygml::capi::FeatureType_WaterGroundSurface:
        case ecitygml::capi::FeatureType_WaterSurface:
        case ecitygml::capi::FeatureType_Waterway:
        case ecitygml::capi::FeatureType_Window:
        case ecitygml::capi::FeatureType_WindowSurface:
        case ecitygml::capi::FeatureType_X3DMaterial:
            return static_cast<ecitygml::FeatureType::Value>(c_enum);
        default:
            std::abort();
    }
}

inline std::string ecitygml::FeatureType::to_string() const {
    std::string output;
    diplomat::capi::DiplomatWrite write = diplomat::WriteFromString(output);
    ecitygml::capi::ecitygml_FeatureType_to_string(this->AsFFI(),
        &write);
    return output;
}
template<typename W>
inline void ecitygml::FeatureType::to_string_write(W& writeable) const {
    diplomat::capi::DiplomatWrite write = diplomat::WriteTrait<W>::Construct(writeable);
    ecitygml::capi::ecitygml_FeatureType_to_string(this->AsFFI(),
        &write);
}
#endif // ecitygml_FeatureType_HPP
