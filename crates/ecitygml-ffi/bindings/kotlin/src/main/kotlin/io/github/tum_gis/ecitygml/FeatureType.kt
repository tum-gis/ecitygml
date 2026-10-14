package io.github.tum_gis.ecitygml

import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface FeatureTypeLib: Library {
}
/** Type of a CityGML feature.
*/
enum class FeatureType {
    Appearance,
    AuxiliaryTrafficArea,
    AuxiliaryTrafficSpace,
    Bridge,
    BridgeConstructiveElement,
    BridgeFurniture,
    BridgeInstallation,
    BridgePart,
    BridgeRoom,
    Building,
    BuildingConstructiveElement,
    BuildingFurniture,
    BuildingInstallation,
    BuildingPart,
    BuildingRoom,
    BuildingUnit,
    CeilingSurface,
    CityFurniture,
    CityModel,
    CityObjectGroup,
    ClearanceSpace,
    ClosureSurface,
    Door,
    DoorSurface,
    FloorSurface,
    GenericLogicalSpace,
    GenericOccupiedSpace,
    GenericThematicSurface,
    GenericUnoccupiedSpace,
    GeoreferencedTexture,
    GroundSurface,
    Hole,
    HoleSurface,
    HollowSpace,
    InteriorWallSurface,
    Intersection,
    LandUse,
    Marking,
    OtherConstruction,
    OuterCeilingSurface,
    OuterFloorSurface,
    ParameterizedTexture,
    PlantCover,
    PointCloud,
    Railway,
    ReliefFeature,
    Road,
    RoofSurface,
    Section,
    SolitaryVegetationObject,
    Square,
    Storey,
    TinRelief,
    Track,
    TrafficArea,
    TrafficSpace,
    Tunnel,
    TunnelConstructiveElement,
    TunnelFurniture,
    TunnelInstallation,
    TunnelPart,
    WallSurface,
    WaterBody,
    WaterGroundSurface,
    WaterSurface,
    Waterway,
    Window,
    WindowSurface,
    X3DMaterial;

    fun toNative(): Int {
        return this.ordinal
    }


    companion object {
        internal val libClass: Class<FeatureTypeLib> = FeatureTypeLib::class.java
        internal val lib: FeatureTypeLib = Native.load("ecitygml_ffi", libClass) 
        fun fromNative(native: Int): FeatureType {
            return FeatureType.entries[native]
        }

        fun default(): FeatureType {
            return Appearance
        }
    }
}
