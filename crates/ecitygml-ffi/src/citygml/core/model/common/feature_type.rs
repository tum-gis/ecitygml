//! `FeatureType`, mirroring `ecitygml::model::common::FeatureType`.

#[diplomat::bridge]
#[diplomat::abi_rename = "ecitygml_{0}"]
#[diplomat::attr(auto, namespace = "ecitygml")]
// Python: classes directly in the `ecitygml` module instead of a nested `ecitygml.ecitygml`.
#[diplomat::attr(nanobind, namespace = "")]
pub mod ffi {
    use diplomat_runtime::DiplomatWrite;

    /// Type of a CityGML feature.
    #[diplomat::enum_convert(ecitygml::model::common::FeatureType)]
    #[derive(Debug, PartialEq, Eq)]
    pub enum FeatureType {
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
        X3DMaterial,
    }

    impl FeatureType {
        /// The type's name, e.g. `Building` (Rust: `Display`). Not in Kotlin, whose enums have `name`;
        /// Diplomat's nanobind backend generates no enum methods (Python: `repr()`).
        #[diplomat::attr(kotlin, disable)]
        pub fn to_string(self, write: &mut DiplomatWrite) {
            use std::fmt::Write;
            // Writing to a DiplomatWrite only fails when out of memory.
            let _ = write!(
                write,
                "{}",
                ecitygml::model::common::FeatureType::from(self)
            );
        }
    }
}

pub use ffi::FeatureType;
