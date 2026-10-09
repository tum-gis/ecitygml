#ifndef ecitygml_FeatureType_D_HPP
#define ecitygml_FeatureType_D_HPP

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
    enum FeatureType {
      FeatureType_Appearance = 0,
      FeatureType_AuxiliaryTrafficArea = 1,
      FeatureType_AuxiliaryTrafficSpace = 2,
      FeatureType_Bridge = 3,
      FeatureType_BridgeConstructiveElement = 4,
      FeatureType_BridgeFurniture = 5,
      FeatureType_BridgeInstallation = 6,
      FeatureType_BridgePart = 7,
      FeatureType_BridgeRoom = 8,
      FeatureType_Building = 9,
      FeatureType_BuildingConstructiveElement = 10,
      FeatureType_BuildingFurniture = 11,
      FeatureType_BuildingInstallation = 12,
      FeatureType_BuildingPart = 13,
      FeatureType_BuildingRoom = 14,
      FeatureType_BuildingUnit = 15,
      FeatureType_CeilingSurface = 16,
      FeatureType_CityFurniture = 17,
      FeatureType_CityModel = 18,
      FeatureType_CityObjectGroup = 19,
      FeatureType_ClearanceSpace = 20,
      FeatureType_ClosureSurface = 21,
      FeatureType_Door = 22,
      FeatureType_DoorSurface = 23,
      FeatureType_FloorSurface = 24,
      FeatureType_GenericLogicalSpace = 25,
      FeatureType_GenericOccupiedSpace = 26,
      FeatureType_GenericThematicSurface = 27,
      FeatureType_GenericUnoccupiedSpace = 28,
      FeatureType_GeoreferencedTexture = 29,
      FeatureType_GroundSurface = 30,
      FeatureType_Hole = 31,
      FeatureType_HoleSurface = 32,
      FeatureType_HollowSpace = 33,
      FeatureType_InteriorWallSurface = 34,
      FeatureType_Intersection = 35,
      FeatureType_LandUse = 36,
      FeatureType_Marking = 37,
      FeatureType_OtherConstruction = 38,
      FeatureType_OuterCeilingSurface = 39,
      FeatureType_OuterFloorSurface = 40,
      FeatureType_ParameterizedTexture = 41,
      FeatureType_PlantCover = 42,
      FeatureType_PointCloud = 43,
      FeatureType_Railway = 44,
      FeatureType_ReliefFeature = 45,
      FeatureType_Road = 46,
      FeatureType_RoofSurface = 47,
      FeatureType_Section = 48,
      FeatureType_SolitaryVegetationObject = 49,
      FeatureType_Square = 50,
      FeatureType_Storey = 51,
      FeatureType_TinRelief = 52,
      FeatureType_Track = 53,
      FeatureType_TrafficArea = 54,
      FeatureType_TrafficSpace = 55,
      FeatureType_Tunnel = 56,
      FeatureType_TunnelConstructiveElement = 57,
      FeatureType_TunnelFurniture = 58,
      FeatureType_TunnelInstallation = 59,
      FeatureType_TunnelPart = 60,
      FeatureType_WallSurface = 61,
      FeatureType_WaterBody = 62,
      FeatureType_WaterGroundSurface = 63,
      FeatureType_WaterSurface = 64,
      FeatureType_Waterway = 65,
      FeatureType_Window = 66,
      FeatureType_WindowSurface = 67,
      FeatureType_X3DMaterial = 68,
    };

    typedef struct FeatureType_option {union { FeatureType ok; }; bool is_ok; } FeatureType_option;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Type of a CityGML feature.
 */
class FeatureType {
public:
    enum Value {
        Appearance = 0,
        AuxiliaryTrafficArea = 1,
        AuxiliaryTrafficSpace = 2,
        Bridge = 3,
        BridgeConstructiveElement = 4,
        BridgeFurniture = 5,
        BridgeInstallation = 6,
        BridgePart = 7,
        BridgeRoom = 8,
        Building = 9,
        BuildingConstructiveElement = 10,
        BuildingFurniture = 11,
        BuildingInstallation = 12,
        BuildingPart = 13,
        BuildingRoom = 14,
        BuildingUnit = 15,
        CeilingSurface = 16,
        CityFurniture = 17,
        CityModel = 18,
        CityObjectGroup = 19,
        ClearanceSpace = 20,
        ClosureSurface = 21,
        Door = 22,
        DoorSurface = 23,
        FloorSurface = 24,
        GenericLogicalSpace = 25,
        GenericOccupiedSpace = 26,
        GenericThematicSurface = 27,
        GenericUnoccupiedSpace = 28,
        GeoreferencedTexture = 29,
        GroundSurface = 30,
        Hole = 31,
        HoleSurface = 32,
        HollowSpace = 33,
        InteriorWallSurface = 34,
        Intersection = 35,
        LandUse = 36,
        Marking = 37,
        OtherConstruction = 38,
        OuterCeilingSurface = 39,
        OuterFloorSurface = 40,
        ParameterizedTexture = 41,
        PlantCover = 42,
        PointCloud = 43,
        Railway = 44,
        ReliefFeature = 45,
        Road = 46,
        RoofSurface = 47,
        Section = 48,
        SolitaryVegetationObject = 49,
        Square = 50,
        Storey = 51,
        TinRelief = 52,
        Track = 53,
        TrafficArea = 54,
        TrafficSpace = 55,
        Tunnel = 56,
        TunnelConstructiveElement = 57,
        TunnelFurniture = 58,
        TunnelInstallation = 59,
        TunnelPart = 60,
        WallSurface = 61,
        WaterBody = 62,
        WaterGroundSurface = 63,
        WaterSurface = 64,
        Waterway = 65,
        Window = 66,
        WindowSurface = 67,
        X3DMaterial = 68,
    };

    FeatureType(): value(Value::Appearance) {}

    // Implicit conversions between enum and ::Value
    constexpr FeatureType(Value v) : value(v) {}
    constexpr operator Value() const { return value; }
    // Prevent usage as boolean value
    explicit operator bool() const = delete;

  /**
   * The type's name, e.g. `Building` (Rust: `Display`). Not in Kotlin, whose enums have `name`;
   * Diplomat's nanobind backend generates no enum methods (Python: `repr()`).
   */
  inline std::string to_string() const;
  template<typename W>
  inline void to_string_write(W& writeable_output) const;

    inline ecitygml::capi::FeatureType AsFFI() const;
    inline static ecitygml::FeatureType FromFFI(ecitygml::capi::FeatureType c_enum);
private:
    Value value;
};

} // namespace
#endif // ecitygml_FeatureType_D_HPP
