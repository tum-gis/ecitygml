use egml::io::util::XmlElement;
use strum::Display;

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash, Display)]
pub enum CityGmlElement {
    AbstractAppearanceProperty,
    AbstractBuildingSubdivisionProperty,
    AbstractFillingElementProperty,
    AbstractFillingSurfaceProperty,
    AbstractPointCloudProperty,
    AbstractReliefComponentProperty,
    AbstractSurfaceDataProperty,
    /// Serialization only (`Address`) — deliberately absent from `from_local_name` since
    /// `"Address"` already resolves to `XalElement::Address` (`xAL:Address`) in
    /// `CombinedCityGmlElement`; both share the local name `Address`.
    Address,
    AddressProperty,
    AmbientIntensityProperty,
    Appearance,
    AppearanceMemberProperty,
    AreaProperty,
    AuxiliaryTrafficArea,
    AuxiliaryTrafficSpace,
    AuxiliaryTrafficSpaceProperty,
    AverageHeightProperty,
    BorderColorProperty,
    BoundaryProperty,
    Bridge,
    BridgeConstructiveElement,
    BridgeConstructiveElementProperty,
    BridgeInstallation,
    BridgeInstallationProperty,
    BridgePart,
    BridgePartProperty,
    Building,
    BuildingConstructiveElement,
    BuildingConstructiveElementProperty,
    BuildingInstallation,
    BuildingInstallationProperty,
    BuildingPart,
    BuildingPartProperty,
    BuildingRoom,
    BuildingRoomProperty,
    BuildingUnit,
    CeilingSurface,
    CityFurniture,
    CityModel,
    CityObjectGroup,
    CityObjectMemberProperty,
    CityObjectRelation,
    ClassProperty,
    ClearanceSpace,
    ClearanceSpaceProperty,
    ClosureSurface,
    CreationDateProperty,
    CrownDiameterProperty,
    DateOfConstructionProperty,
    DateOfDemolitionProperty,
    DiffuseColorProperty,
    Door,
    DoorSurface,
    DoubleAttribute,
    EmissiveColorProperty,
    ExternalReference,
    ExternalReferenceProperty,
    FloorSurface,
    FunctionProperty,
    GenericAttributeProperty,
    GenericAttributeSet,
    GenericOccupiedSpace,
    GenericThematicSurface,
    GeoreferencedTexture,
    GranularityProperty,
    GroundSurface,
    GroupMemberProperty,
    Height,
    HeightProperty,
    HighReferenceProperty,
    Hole,
    HoleProperty,
    HoleSurface,
    ImageUriProperty,
    ImplicitGeometry,
    InformationSystemProperty,
    IntAttribute,
    InteriorWallSurface,
    Intersection,
    IntersectionProperty,
    IntervalProperty,
    IsFrontProperty,
    IsMovableProperty,
    IsSmoothProperty,
    IsStructuralElementProperty,
    LandUse,
    LibraryObjectProperty,
    Lod0MultiCurveProperty,
    Lod0MultiSurfaceProperty,
    Lod0PointProperty,
    Lod1ImplicitRepresentationProperty,
    Lod1MultiCurveProperty,
    Lod1MultiSurfaceProperty,
    Lod1SolidProperty,
    Lod1TerrainIntersectionCurveProperty,
    Lod2ImplicitRepresentationProperty,
    Lod2MultiCurveProperty,
    Lod2MultiSurfaceProperty,
    Lod2SolidProperty,
    Lod2TerrainIntersectionCurveProperty,
    Lod3ImplicitRepresentationProperty,
    Lod3MultiCurveProperty,
    Lod3MultiSurfaceProperty,
    Lod3SolidProperty,
    Lod3TerrainIntersectionCurveProperty,
    LodProperty,
    LowReferenceProperty,
    Marking,
    MarkingProperty,
    MaxHeightProperty,
    MaxRootBallDepthProperty,
    MeasureAttribute,
    MimeTypeProperty,
    MinHeightProperty,
    MultiPointProperty,
    /// Serialization only (`gen:name`) — deliberately absent from `from_local_name` since
    /// `"name"` already resolves to `GmlElement::NameProperty` in `CombinedCityGmlElement`.
    NameProperty,
    NumberOfOccupantsProperty,
    Occupancy,
    OccupancyProperty,
    OccupantTypeProperty,
    OuterCeilingSurface,
    OuterFloorSurface,
    ParameterizedTexture,
    PlantCover,
    PointCloud,
    PointFileProperty,
    PointFileSrsNameProperty,
    PointsProperty,
    PredecessorProperty,
    PreferWorldFileProperty,
    QualifiedArea,
    QualifiedVolume,
    Railway,
    ReferencePointProperty,
    RelatedToProperty,
    RelationTypeProperty,
    RelativeGeometryProperty,
    RelativeToTerrainProperty,
    RelativeToWaterProperty,
    ReliefFeature,
    Road,
    Role,
    RoleProperty,
    RoofSurface,
    RoofTypeProperty,
    RootBallDiameterProperty,
    Section,
    SectionProperty,
    TargetResourceProperty,
    ShininessProperty,
    SolitaryVegetationObject,
    SpaceTypeProperty,
    SpeciesProperty,
    SpecularColorProperty,
    Square,
    StatusProperty,
    StringAttribute,
    Storey,
    StoreysAboveGroundProperty,
    StoreysBelowGroundProperty,
    SuccessorProperty,
    SurfaceMaterialProperty,
    TINRelief,
    TargetProperty,
    TerminationDateProperty,
    TexCoordList,
    TextureTypeProperty,
    ThemeProperty,
    TinProperty,
    Track,
    TransformationMatrixProperty,
    TrafficArea,
    TrafficDirectionProperty,
    TrafficSpace,
    TrafficSpaceProperty,
    TransparencyProperty,
    TrunkDiameterProperty,
    TypeOfAreaProperty,
    TypeOfVolumeProperty,
    Tunnel,
    TunnelConstructiveElement,
    TunnelConstructiveElementProperty,
    TunnelInstallation,
    TunnelInstallationProperty,
    TunnelPart,
    TunnelPartProperty,
    UsageProperty,
    ValidFromProperty,
    ValidToProperty,
    ValueProperty,
    VolumeProperty,
    WallSurface,
    WaterBody,
    WaterGroundSurface,
    WaterLevelProperty,
    WaterSurface,
    Waterway,
    Window,
    WindowSurface,
    WrapModeProperty,
    X3DMaterial,
    XalAddressProperty,
}

impl XmlElement for CityGmlElement {
    fn from_local_name(local_name: &str) -> Option<Self> {
        match local_name {
            "Appearance" => Some(Self::Appearance),
            "AuxiliaryTrafficArea" => Some(Self::AuxiliaryTrafficArea),
            "AuxiliaryTrafficSpace" => Some(Self::AuxiliaryTrafficSpace),
            "Bridge" => Some(Self::Bridge),
            "BridgeConstructiveElement" => Some(Self::BridgeConstructiveElement),
            "BridgeInstallation" => Some(Self::BridgeInstallation),
            "BridgePart" => Some(Self::BridgePart),
            "Building" => Some(Self::Building),
            "BuildingConstructiveElement" => Some(Self::BuildingConstructiveElement),
            "BuildingInstallation" => Some(Self::BuildingInstallation),
            "BuildingPart" => Some(Self::BuildingPart),
            "BuildingRoom" => Some(Self::BuildingRoom),
            "BuildingUnit" => Some(Self::BuildingUnit),
            "CeilingSurface" => Some(Self::CeilingSurface),
            "CityFurniture" => Some(Self::CityFurniture),
            "CityObjectGroup" => Some(Self::CityObjectGroup),
            "CityObjectRelation" => Some(Self::CityObjectRelation),
            "class" => Some(Self::ClassProperty),
            "ClearanceSpace" => Some(Self::ClearanceSpace),
            "ClosureSurface" => Some(Self::ClosureSurface),
            "creationDate" => Some(Self::CreationDateProperty),
            "dateOfConstruction" => Some(Self::DateOfConstructionProperty),
            "dateOfDemolition" => Some(Self::DateOfDemolitionProperty),
            "Door" => Some(Self::Door),
            "DoorSurface" => Some(Self::DoorSurface),
            "DoubleAttribute" => Some(Self::DoubleAttribute),
            "FloorSurface" => Some(Self::FloorSurface),
            "GenericAttributeSet" => Some(Self::GenericAttributeSet),
            "GenericOccupiedSpace" => Some(Self::GenericOccupiedSpace),
            "GenericThematicSurface" => Some(Self::GenericThematicSurface),
            "GeoreferencedTexture" => Some(Self::GeoreferencedTexture),
            "GroundSurface" => Some(Self::GroundSurface),
            "Height" => Some(Self::Height),
            "Hole" => Some(Self::Hole),
            "HoleSurface" => Some(Self::HoleSurface),
            "ExternalReference" => Some(Self::ExternalReference),
            "ImplicitGeometry" => Some(Self::ImplicitGeometry),
            "informationSystem" => Some(Self::InformationSystemProperty),
            "InteriorWallSurface" => Some(Self::InteriorWallSurface),
            "IntAttribute" => Some(Self::IntAttribute),
            "Intersection" => Some(Self::Intersection),
            "interval" => Some(Self::IntervalProperty),
            "LandUse" => Some(Self::LandUse),
            "Marking" => Some(Self::Marking),
            "MeasureAttribute" => Some(Self::MeasureAttribute),
            "OuterCeilingSurface" => Some(Self::OuterCeilingSurface),
            "OuterFloorSurface" => Some(Self::OuterFloorSurface),
            "ParameterizedTexture" => Some(Self::ParameterizedTexture),
            "PlantCover" => Some(Self::PlantCover),
            "PointCloud" => Some(Self::PointCloud),
            "QualifiedArea" => Some(Self::QualifiedArea),
            "QualifiedVolume" => Some(Self::QualifiedVolume),
            "Railway" => Some(Self::Railway),
            "ReliefFeature" => Some(Self::ReliefFeature),
            "Road" => Some(Self::Road),
            "Role" => Some(Self::Role),
            "RoofSurface" => Some(Self::RoofSurface),
            "Section" => Some(Self::Section),
            "SolitaryVegetationObject" => Some(Self::SolitaryVegetationObject),
            "Square" => Some(Self::Square),
            "Storey" => Some(Self::Storey),
            "StringAttribute" => Some(Self::StringAttribute),
            "TINRelief" => Some(Self::TINRelief),
            "target" => Some(Self::TargetProperty),
            "terminationDate" => Some(Self::TerminationDateProperty),
            "TexCoordList" => Some(Self::TexCoordList),
            "Track" => Some(Self::Track),
            "transformationMatrix" => Some(Self::TransformationMatrixProperty),
            "TrafficArea" => Some(Self::TrafficArea),
            "TrafficSpace" => Some(Self::TrafficSpace),
            "Tunnel" => Some(Self::Tunnel),
            "TunnelConstructiveElement" => Some(Self::TunnelConstructiveElement),
            "TunnelInstallation" => Some(Self::TunnelInstallation),
            "TunnelPart" => Some(Self::TunnelPart),
            "WallSurface" => Some(Self::WallSurface),
            "WaterBody" => Some(Self::WaterBody),
            "WaterGroundSurface" => Some(Self::WaterGroundSurface),
            "WaterSurface" => Some(Self::WaterSurface),
            "Waterway" => Some(Self::Waterway),
            "Window" => Some(Self::Window),
            "WindowSurface" => Some(Self::WindowSurface),
            "X3DMaterial" => Some(Self::X3DMaterial),
            "address" => Some(Self::AddressProperty),
            "ambientIntensity" => Some(Self::AmbientIntensityProperty),
            "appearance" => Some(Self::AbstractAppearanceProperty),
            "appearanceMember" => Some(Self::AppearanceMemberProperty),
            "area" => Some(Self::AreaProperty),
            "auxiliaryTrafficSpace" => Some(Self::AuxiliaryTrafficSpaceProperty),
            "averageHeight" => Some(Self::AverageHeightProperty),
            "borderColor" => Some(Self::BorderColorProperty),
            "boundary" => Some(Self::BoundaryProperty),
            "bridgeConstructiveElement" => Some(Self::BridgeConstructiveElementProperty),
            "bridgeInstallation" => Some(Self::BridgeInstallationProperty),
            "bridgePart" => Some(Self::BridgePartProperty),
            "buildingConstructiveElement" => Some(Self::BuildingConstructiveElementProperty),
            "buildingInstallation" => Some(Self::BuildingInstallationProperty),
            "buildingPart" => Some(Self::BuildingPartProperty),
            "buildingRoom" => Some(Self::BuildingRoomProperty),
            "buildingSubdivision" => Some(Self::AbstractBuildingSubdivisionProperty),
            "cityObjectMember" => Some(Self::CityObjectMemberProperty),
            "clearanceSpace" => Some(Self::ClearanceSpaceProperty),
            "crownDiameter" => Some(Self::CrownDiameterProperty),
            "diffuseColor" => Some(Self::DiffuseColorProperty),
            "emissiveColor" => Some(Self::EmissiveColorProperty),
            "externalReference" => Some(Self::ExternalReferenceProperty),
            "filling" => Some(Self::AbstractFillingElementProperty),
            "fillingSurface" => Some(Self::AbstractFillingSurfaceProperty),
            "function" => Some(Self::FunctionProperty),
            "genericAttribute" => Some(Self::GenericAttributeProperty),
            "granularity" => Some(Self::GranularityProperty),
            "groupMember" => Some(Self::GroupMemberProperty),
            "height" => Some(Self::HeightProperty),
            "highReference" => Some(Self::HighReferenceProperty),
            "hole" => Some(Self::HoleProperty),
            "imageURI" => Some(Self::ImageUriProperty),
            "intersection" => Some(Self::IntersectionProperty),
            "isFront" => Some(Self::IsFrontProperty),
            "isMovable" => Some(Self::IsMovableProperty),
            "isSmooth" => Some(Self::IsSmoothProperty),
            "isStructuralElement" => Some(Self::IsStructuralElementProperty),
            "libraryObject" => Some(Self::LibraryObjectProperty),
            "lod" => Some(Self::LodProperty),
            "lod0MultiCurve" => Some(Self::Lod0MultiCurveProperty),
            "lod0MultiSurface" => Some(Self::Lod0MultiSurfaceProperty),
            "lod0Point" => Some(Self::Lod0PointProperty),
            "lod1ImplicitRepresentation" => Some(Self::Lod1ImplicitRepresentationProperty),
            "lod1MultiCurve" => Some(Self::Lod1MultiCurveProperty),
            "lod1MultiSurface" => Some(Self::Lod1MultiSurfaceProperty),
            "lod1Solid" => Some(Self::Lod1SolidProperty),
            "lod1TerrainIntersectionCurve" => Some(Self::Lod1TerrainIntersectionCurveProperty),
            "lod2ImplicitRepresentation" => Some(Self::Lod2ImplicitRepresentationProperty),
            "lod2MultiCurve" => Some(Self::Lod2MultiCurveProperty),
            "lod2MultiSurface" => Some(Self::Lod2MultiSurfaceProperty),
            "lod2Solid" => Some(Self::Lod2SolidProperty),
            "lod2TerrainIntersectionCurve" => Some(Self::Lod2TerrainIntersectionCurveProperty),
            "lod3ImplicitRepresentation" => Some(Self::Lod3ImplicitRepresentationProperty),
            "lod3MultiCurve" => Some(Self::Lod3MultiCurveProperty),
            "lod3MultiSurface" => Some(Self::Lod3MultiSurfaceProperty),
            "lod3Solid" => Some(Self::Lod3SolidProperty),
            "lod3TerrainIntersectionCurve" => Some(Self::Lod3TerrainIntersectionCurveProperty),
            "lowReference" => Some(Self::LowReferenceProperty),
            "marking" => Some(Self::MarkingProperty),
            "maxHeight" => Some(Self::MaxHeightProperty),
            "maxRootBallDepth" => Some(Self::MaxRootBallDepthProperty),
            "mimeType" => Some(Self::MimeTypeProperty),
            "minHeight" => Some(Self::MinHeightProperty),
            "multiPoint" => Some(Self::MultiPointProperty),
            "numberOfOccupants" => Some(Self::NumberOfOccupantsProperty),
            "Occupancy" => Some(Self::Occupancy),
            "occupancy" => Some(Self::OccupancyProperty),
            "occupantType" => Some(Self::OccupantTypeProperty),
            "pointCloud" => Some(Self::AbstractPointCloudProperty),
            "pointFile" => Some(Self::PointFileProperty),
            "pointFileSrsName" => Some(Self::PointFileSrsNameProperty),
            "points" => Some(Self::PointsProperty),
            "preferWorldFile" => Some(Self::PreferWorldFileProperty),
            "referencePoint" => Some(Self::ReferencePointProperty),
            "relativeGeometry" => Some(Self::RelativeGeometryProperty),
            "relativeToTerrain" => Some(Self::RelativeToTerrainProperty),
            "relativeToWater" => Some(Self::RelativeToWaterProperty),
            "reliefComponent" => Some(Self::AbstractReliefComponentProperty),
            "role" => Some(Self::RoleProperty),
            "roofType" => Some(Self::RoofTypeProperty),
            "rootBallDiameter" => Some(Self::RootBallDiameterProperty),
            "section" => Some(Self::SectionProperty),
            "shininess" => Some(Self::ShininessProperty),
            "spaceType" => Some(Self::SpaceTypeProperty),
            "species" => Some(Self::SpeciesProperty),
            "specularColor" => Some(Self::SpecularColorProperty),
            "status" => Some(Self::StatusProperty),
            "storeysAboveGround" => Some(Self::StoreysAboveGroundProperty),
            "storeysBelowGround" => Some(Self::StoreysBelowGroundProperty),
            "surfaceData" => Some(Self::AbstractSurfaceDataProperty),
            "textureType" => Some(Self::TextureTypeProperty),
            "theme" => Some(Self::ThemeProperty),
            "tin" => Some(Self::TinProperty),
            "trafficDirection" => Some(Self::TrafficDirectionProperty),
            "trafficSpace" => Some(Self::TrafficSpaceProperty),
            "transparency" => Some(Self::TransparencyProperty),
            "trunkDiameter" => Some(Self::TrunkDiameterProperty),
            "typeOfArea" => Some(Self::TypeOfAreaProperty),
            "typeOfVolume" => Some(Self::TypeOfVolumeProperty),
            "tunnelConstructiveElement" => Some(Self::TunnelConstructiveElementProperty),
            "tunnelInstallation" => Some(Self::TunnelInstallationProperty),
            "tunnelPart" => Some(Self::TunnelPartProperty),
            "usage" => Some(Self::UsageProperty),
            "validFrom" => Some(Self::ValidFromProperty),
            "validTo" => Some(Self::ValidToProperty),
            "value" => Some(Self::ValueProperty),
            "volume" => Some(Self::VolumeProperty),
            "waterLevel" => Some(Self::WaterLevelProperty),
            "wrapMode" => Some(Self::WrapModeProperty),
            "relatedTo" => Some(Self::RelatedToProperty),
            "relationType" => Some(Self::RelationTypeProperty),
            "targetResource" => Some(Self::TargetResourceProperty),
            "predecessor" => Some(Self::PredecessorProperty),
            "successor" => Some(Self::SuccessorProperty),
            "surfaceMaterial" => Some(Self::SurfaceMaterialProperty),
            "xalAddress" => Some(Self::XalAddressProperty),
            _ => {
                tracing::debug!("unknown XML element: {}", local_name);
                None
            }
        }
    }

    fn local_name(&self) -> &'static str {
        match self {
            CityGmlElement::AbstractAppearanceProperty => "appearance",
            CityGmlElement::AbstractBuildingSubdivisionProperty => "buildingSubdivision",
            CityGmlElement::AbstractFillingElementProperty => "filling",
            CityGmlElement::AbstractFillingSurfaceProperty => "fillingSurface",
            CityGmlElement::AbstractPointCloudProperty => "pointCloud",
            CityGmlElement::AbstractReliefComponentProperty => "reliefComponent",
            CityGmlElement::AbstractSurfaceDataProperty => "surfaceData",
            CityGmlElement::Address => "Address",
            CityGmlElement::AddressProperty => "address",
            CityGmlElement::AmbientIntensityProperty => "ambientIntensity",
            CityGmlElement::Appearance => "Appearance",
            CityGmlElement::AppearanceMemberProperty => "appearanceMember",
            CityGmlElement::AreaProperty => "area",
            CityGmlElement::AuxiliaryTrafficArea => "AuxiliaryTrafficArea",
            CityGmlElement::AuxiliaryTrafficSpace => "AuxiliaryTrafficSpace",
            CityGmlElement::AuxiliaryTrafficSpaceProperty => "auxiliaryTrafficSpace",
            CityGmlElement::AverageHeightProperty => "averageHeight",
            CityGmlElement::BorderColorProperty => "borderColor",
            CityGmlElement::BoundaryProperty => "boundary",
            CityGmlElement::Bridge => "Bridge",
            CityGmlElement::BridgeConstructiveElement => "BridgeConstructiveElement",
            CityGmlElement::BridgeConstructiveElementProperty => "bridgeConstructiveElement",
            CityGmlElement::BridgeInstallation => "BridgeInstallation",
            CityGmlElement::BridgeInstallationProperty => "bridgeInstallation",
            CityGmlElement::BridgePart => "BridgePart",
            CityGmlElement::BridgePartProperty => "bridgePart",
            CityGmlElement::Building => "Building",
            CityGmlElement::BuildingConstructiveElement => "BuildingConstructiveElement",
            CityGmlElement::BuildingConstructiveElementProperty => "buildingConstructiveElement",
            CityGmlElement::BuildingInstallation => "BuildingInstallation",
            CityGmlElement::BuildingInstallationProperty => "buildingInstallation",
            CityGmlElement::BuildingPart => "BuildingPart",
            CityGmlElement::BuildingPartProperty => "buildingPart",
            CityGmlElement::BuildingRoom => "BuildingRoom",
            CityGmlElement::BuildingRoomProperty => "buildingRoom",
            CityGmlElement::BuildingUnit => "BuildingUnit",
            CityGmlElement::CeilingSurface => "CeilingSurface",
            CityGmlElement::CityFurniture => "CityFurniture",
            CityGmlElement::CityModel => "CityModel",
            CityGmlElement::CityObjectGroup => "CityObjectGroup",
            CityGmlElement::CityObjectMemberProperty => "cityObjectMember",
            CityGmlElement::CityObjectRelation => "CityObjectRelation",
            CityGmlElement::ClassProperty => "class",
            CityGmlElement::ClearanceSpace => "ClearanceSpace",
            CityGmlElement::ClearanceSpaceProperty => "clearanceSpace",
            CityGmlElement::ClosureSurface => "ClosureSurface",
            CityGmlElement::CreationDateProperty => "creationDate",
            CityGmlElement::CrownDiameterProperty => "crownDiameter",
            CityGmlElement::DateOfConstructionProperty => "dateOfConstruction",
            CityGmlElement::DateOfDemolitionProperty => "dateOfDemolition",
            CityGmlElement::DiffuseColorProperty => "diffuseColor",
            CityGmlElement::Door => "Door",
            CityGmlElement::DoorSurface => "DoorSurface",
            CityGmlElement::DoubleAttribute => "DoubleAttribute",
            CityGmlElement::EmissiveColorProperty => "emissiveColor",
            CityGmlElement::ExternalReference => "ExternalReference",
            CityGmlElement::ExternalReferenceProperty => "externalReference",
            CityGmlElement::FloorSurface => "FloorSurface",
            CityGmlElement::FunctionProperty => "function",
            CityGmlElement::GenericAttributeProperty => "genericAttribute",
            CityGmlElement::GenericAttributeSet => "GenericAttributeSet",
            CityGmlElement::GenericOccupiedSpace => "GenericOccupiedSpace",
            CityGmlElement::GenericThematicSurface => "GenericThematicSurface",
            CityGmlElement::GeoreferencedTexture => "GeoreferencedTexture",
            CityGmlElement::GranularityProperty => "granularity",
            CityGmlElement::GroundSurface => "GroundSurface",
            CityGmlElement::GroupMemberProperty => "groupMember",
            CityGmlElement::Height => "Height",
            CityGmlElement::HeightProperty => "height",
            CityGmlElement::HighReferenceProperty => "highReference",
            CityGmlElement::Hole => "Hole",
            CityGmlElement::HoleProperty => "hole",
            CityGmlElement::HoleSurface => "HoleSurface",
            CityGmlElement::ImageUriProperty => "imageURI",
            CityGmlElement::ImplicitGeometry => "ImplicitGeometry",
            CityGmlElement::InformationSystemProperty => "informationSystem",
            CityGmlElement::IntAttribute => "IntAttribute",
            CityGmlElement::InteriorWallSurface => "InteriorWallSurface",
            CityGmlElement::Intersection => "Intersection",
            CityGmlElement::IntersectionProperty => "intersection",
            CityGmlElement::IntervalProperty => "interval",
            CityGmlElement::IsFrontProperty => "isFront",
            CityGmlElement::IsMovableProperty => "isMovable",
            CityGmlElement::IsSmoothProperty => "isSmooth",
            CityGmlElement::IsStructuralElementProperty => "isStructuralElement",
            CityGmlElement::LandUse => "LandUse",
            CityGmlElement::LibraryObjectProperty => "libraryObject",
            CityGmlElement::Lod0MultiCurveProperty => "lod0MultiCurve",
            CityGmlElement::Lod0MultiSurfaceProperty => "lod0MultiSurface",
            CityGmlElement::Lod0PointProperty => "lod0Point",
            CityGmlElement::Lod1ImplicitRepresentationProperty => "lod1ImplicitRepresentation",
            CityGmlElement::Lod1MultiCurveProperty => "lod1MultiCurve",
            CityGmlElement::Lod1MultiSurfaceProperty => "lod1MultiSurface",
            CityGmlElement::Lod1SolidProperty => "lod1Solid",
            CityGmlElement::Lod1TerrainIntersectionCurveProperty => "lod1TerrainIntersectionCurve",
            CityGmlElement::Lod2ImplicitRepresentationProperty => "lod2ImplicitRepresentation",
            CityGmlElement::Lod2MultiCurveProperty => "lod2MultiCurve",
            CityGmlElement::Lod2MultiSurfaceProperty => "lod2MultiSurface",
            CityGmlElement::Lod2SolidProperty => "lod2Solid",
            CityGmlElement::Lod2TerrainIntersectionCurveProperty => "lod2TerrainIntersectionCurve",
            CityGmlElement::Lod3ImplicitRepresentationProperty => "lod3ImplicitRepresentation",
            CityGmlElement::Lod3MultiCurveProperty => "lod3MultiCurve",
            CityGmlElement::Lod3MultiSurfaceProperty => "lod3MultiSurface",
            CityGmlElement::Lod3SolidProperty => "lod3Solid",
            CityGmlElement::Lod3TerrainIntersectionCurveProperty => "lod3TerrainIntersectionCurve",
            CityGmlElement::LodProperty => "lod",
            CityGmlElement::LowReferenceProperty => "lowReference",
            CityGmlElement::Marking => "Marking",
            CityGmlElement::MarkingProperty => "marking",
            CityGmlElement::MaxHeightProperty => "maxHeight",
            CityGmlElement::MaxRootBallDepthProperty => "maxRootBallDepth",
            CityGmlElement::MeasureAttribute => "MeasureAttribute",
            CityGmlElement::MimeTypeProperty => "mimeType",
            CityGmlElement::MinHeightProperty => "minHeight",
            CityGmlElement::MultiPointProperty => "multiPoint",
            CityGmlElement::NameProperty => "name",
            CityGmlElement::NumberOfOccupantsProperty => "numberOfOccupants",
            CityGmlElement::Occupancy => "Occupancy",
            CityGmlElement::OccupancyProperty => "occupancy",
            CityGmlElement::OccupantTypeProperty => "occupantType",
            CityGmlElement::OuterCeilingSurface => "OuterCeilingSurface",
            CityGmlElement::OuterFloorSurface => "OuterFloorSurface",
            CityGmlElement::ParameterizedTexture => "ParameterizedTexture",
            CityGmlElement::PlantCover => "PlantCover",
            CityGmlElement::PointCloud => "PointCloud",
            CityGmlElement::PointFileProperty => "pointFile",
            CityGmlElement::PointFileSrsNameProperty => "pointFileSrsName",
            CityGmlElement::PointsProperty => "points",
            CityGmlElement::PredecessorProperty => "predecessor",
            CityGmlElement::PreferWorldFileProperty => "preferWorldFile",
            CityGmlElement::QualifiedArea => "QualifiedArea",
            CityGmlElement::QualifiedVolume => "QualifiedVolume",
            CityGmlElement::Railway => "Railway",
            CityGmlElement::ReferencePointProperty => "referencePoint",
            CityGmlElement::RelatedToProperty => "relatedTo",
            CityGmlElement::RelationTypeProperty => "relationType",
            CityGmlElement::RelativeGeometryProperty => "relativeGeometry",
            CityGmlElement::RelativeToTerrainProperty => "relativeToTerrain",
            CityGmlElement::RelativeToWaterProperty => "relativeToWater",
            CityGmlElement::ReliefFeature => "ReliefFeature",
            CityGmlElement::Road => "Road",
            CityGmlElement::Role => "Role",
            CityGmlElement::RoleProperty => "role",
            CityGmlElement::RoofSurface => "RoofSurface",
            CityGmlElement::RoofTypeProperty => "roofType",
            CityGmlElement::RootBallDiameterProperty => "rootBallDiameter",
            CityGmlElement::Section => "Section",
            CityGmlElement::SectionProperty => "section",
            CityGmlElement::ShininessProperty => "shininess",
            CityGmlElement::SolitaryVegetationObject => "SolitaryVegetationObject",
            CityGmlElement::SpaceTypeProperty => "spaceType",
            CityGmlElement::SpeciesProperty => "species",
            CityGmlElement::SpecularColorProperty => "specularColor",
            CityGmlElement::Square => "Square",
            CityGmlElement::StatusProperty => "status",
            CityGmlElement::Storey => "Storey",
            CityGmlElement::StringAttribute => "StringAttribute",
            CityGmlElement::StoreysAboveGroundProperty => "storeysAboveGround",
            CityGmlElement::StoreysBelowGroundProperty => "storeysBelowGround",
            CityGmlElement::SuccessorProperty => "successor",
            CityGmlElement::SurfaceMaterialProperty => "surfaceMaterial",
            CityGmlElement::TargetResourceProperty => "targetResource",
            CityGmlElement::TINRelief => "TINRelief",
            CityGmlElement::TargetProperty => "target",
            CityGmlElement::TerminationDateProperty => "terminationDate",
            CityGmlElement::TexCoordList => "TexCoordList",
            CityGmlElement::TextureTypeProperty => "textureType",
            CityGmlElement::ThemeProperty => "theme",
            CityGmlElement::TinProperty => "tin",
            CityGmlElement::Track => "Track",
            CityGmlElement::TransformationMatrixProperty => "transformationMatrix",
            CityGmlElement::TrafficArea => "TrafficArea",
            CityGmlElement::TrafficDirectionProperty => "trafficDirection",
            CityGmlElement::TrafficSpace => "TrafficSpace",
            CityGmlElement::TrafficSpaceProperty => "trafficSpace",
            CityGmlElement::TransparencyProperty => "transparency",
            CityGmlElement::TrunkDiameterProperty => "trunkDiameter",
            CityGmlElement::TypeOfAreaProperty => "typeOfArea",
            CityGmlElement::TypeOfVolumeProperty => "typeOfVolume",
            CityGmlElement::Tunnel => "Tunnel",
            CityGmlElement::TunnelConstructiveElement => "TunnelConstructiveElement",
            CityGmlElement::TunnelConstructiveElementProperty => "tunnelConstructiveElement",
            CityGmlElement::TunnelInstallation => "TunnelInstallation",
            CityGmlElement::TunnelInstallationProperty => "tunnelInstallation",
            CityGmlElement::TunnelPart => "TunnelPart",
            CityGmlElement::TunnelPartProperty => "tunnelPart",
            CityGmlElement::UsageProperty => "usage",
            CityGmlElement::ValidFromProperty => "validFrom",
            CityGmlElement::ValidToProperty => "validTo",
            CityGmlElement::ValueProperty => "value",
            CityGmlElement::VolumeProperty => "volume",
            CityGmlElement::WallSurface => "WallSurface",
            CityGmlElement::WaterBody => "WaterBody",
            CityGmlElement::WaterGroundSurface => "WaterGroundSurface",
            CityGmlElement::WaterLevelProperty => "waterLevel",
            CityGmlElement::WaterSurface => "WaterSurface",
            CityGmlElement::Waterway => "Waterway",
            CityGmlElement::Window => "Window",
            CityGmlElement::WindowSurface => "WindowSurface",
            CityGmlElement::WrapModeProperty => "wrapMode",
            CityGmlElement::X3DMaterial => "X3DMaterial",
            CityGmlElement::XalAddressProperty => "xalAddress",
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use egml::io::util::XmlDocumentIndex;

    /// The CityGML 3.0 schema (core.xsd, `AbstractPhysicalSpaceType`) names these
    /// properties without a `Property` suffix.
    #[test]
    fn test_terrain_intersection_curve_names_follow_schema() {
        let cases = [
            (
                "lod1TerrainIntersectionCurve",
                CityGmlElement::Lod1TerrainIntersectionCurveProperty,
            ),
            (
                "lod2TerrainIntersectionCurve",
                CityGmlElement::Lod2TerrainIntersectionCurveProperty,
            ),
            (
                "lod3TerrainIntersectionCurve",
                CityGmlElement::Lod3TerrainIntersectionCurveProperty,
            ),
        ];
        for (name, element) in cases {
            assert_eq!(CityGmlElement::from_local_name(name), Some(element));
            assert_eq!(element.local_name(), name);
        }
        assert_eq!(
            CityGmlElement::from_local_name("lod2TerrainIntersectionCurveProperty"),
            None
        );
    }

    #[test]
    fn test_deserialize_basic_abstract_thematic_surface() {
        let xml_document = b"<bldg:Building gml:id=\"DEBY_LOD2_59772\">
      <creationDate >2023-06-05T00:00:00+02:00</creationDate>
      <externalReference>
        <ExternalReference>
          <targetResource>DEBYvAAAAABTy70E</targetResource>
          <informationSystem>http://repository.gdi-de.org/schemas/adv/citygml/fdv/art.htm#_9100</informationSystem>
        </ExternalReference>
      </externalReference>
      <boundary>
        <con:WallSurface gml:id=\"DEBY_LOD2_59772_4becb506-d53b-44ca-a483-e6a3d238b4c2_2\">
          <lod2MultiSurface>
            <gml:MultiSurface srsDimension=\"3\">
              <gml:surfaceMember>
                <gml:Polygon gml:id=\"DEBY_LOD2_59772_4becb506-d53b-44ca-a483-e6a3d238b4c2_2_poly\">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:posList>691478.01 5334825.81 516.71 691478.01 5334825.81 528.425 691473.38 5334813.05 528.425 691473.38 5334813.05 516.71 691478.01 5334825.81 516.71</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </lod2MultiSurface>
        </con:WallSurface>
      </boundary>
      <boundary>
        <con:WallSurface gml:id=\"DEBY_LOD2_59772_be3462c3-9865-467b-829d-76e6b9b692e7_2\">
          <lod2MultiSurface>
            <gml:MultiSurface srsDimension=\"3\">
              <gml:surfaceMember>
                <gml:Polygon gml:id=\"DEBY_LOD2_59772_be3462c3-9865-467b-829d-76e6b9b692e7_2_poly\">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:posList>691474.24 5334826.79 516.71 691474.24 5334826.79 528.425 691475.29 5334827.01 528.425 691475.29 5334827.01 516.71 691474.24 5334826.79 516.71</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </lod2MultiSurface>
        </con:WallSurface>
      </boundary>
      <boundary>
        <con:WallSurface gml:id=\"DEBY_LOD2_59772_c0aae462-3f4b-4062-80bb-8cd04768ab1a_2\">
          <lod2MultiSurface>
            <gml:MultiSurface srsDimension=\"3\">
              <gml:surfaceMember>
                <gml:Polygon gml:id=\"DEBY_LOD2_59772_c0aae462-3f4b-4062-80bb-8cd04768ab1a_2_poly\">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:posList>691472.46 5334820.87 516.71 691472.46 5334820.87 528.425 691472.6 5334821.26 528.425 691472.6 5334821.26 516.71 691472.46 5334820.87 516.71</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </lod2MultiSurface>
        </con:WallSurface>
      </boundary>
      <boundary>
        <con:RoofSurface gml:id=\"DEBY_LOD2_59772_a13e523a-7269-4637-88fa-e57eed6d9265_2\">
          <lod2MultiSurface>
            <gml:MultiSurface srsDimension=\"3\">
              <gml:surfaceMember>
                <gml:Polygon gml:id=\"DEBY_LOD2_59772_a13e523a-7269-4637-88fa-e57eed6d9265_2_poly\">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:posList>691470.72 5334813.99 528.425 691473.38 5334813.05 528.425 691478.01 5334825.81 528.425 691475.29 5334827.01 528.425 691474.24 5334826.79 528.425 691472.6 5334821.26 528.425 691472.46 5334820.87 528.425 691470.53 5334815.81 528.425 691470.29 5334815.2 528.425 691470.72 5334813.99 528.425</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </lod2MultiSurface>
        </con:RoofSurface>
      </boundary>
      <boundary>
        <con:WallSurface gml:id=\"DEBY_LOD2_59772_bacdfeda-2181-42c2-ac94-bf086ec95291_2\">
          <lod2MultiSurface>
            <gml:MultiSurface srsDimension=\"3\">
              <gml:surfaceMember>
                <gml:Polygon gml:id=\"DEBY_LOD2_59772_bacdfeda-2181-42c2-ac94-bf086ec95291_2_poly\">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:posList>691470.72 5334813.99 516.71 691470.72 5334813.99 528.425 691470.29 5334815.2 528.425 691470.29 5334815.2 516.71 691470.72 5334813.99 516.71</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </lod2MultiSurface>
        </con:WallSurface>
      </boundary>
      <boundary>
        <con:WallSurface gml:id=\"DEBY_LOD2_59772_e76604b3-3834-4420-a1e5-c660f32ab045_2\">
          <lod2MultiSurface>
            <gml:MultiSurface srsDimension=\"3\">
              <gml:surfaceMember>
                <gml:Polygon gml:id=\"DEBY_LOD2_59772_e76604b3-3834-4420-a1e5-c660f32ab045_2_poly\">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:posList>691470.29 5334815.2 516.71 691470.29 5334815.2 528.425 691470.53 5334815.81 528.425 691470.53 5334815.81 516.71 691470.29 5334815.2 516.71</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </lod2MultiSurface>
        </con:WallSurface>
      </boundary>
      <boundary>
        <con:WallSurface gml:id=\"DEBY_LOD2_59772_c8be8650-e40d-4c7d-b491-d892085763aa_2\">
          <lod2MultiSurface>
            <gml:MultiSurface srsDimension=\"3\">
              <gml:surfaceMember>
                <gml:Polygon gml:id=\"DEBY_LOD2_59772_c8be8650-e40d-4c7d-b491-d892085763aa_2_poly\">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:posList>691473.38 5334813.05 516.71 691473.38 5334813.05 528.425 691470.72 5334813.99 528.425 691470.72 5334813.99 516.71 691473.38 5334813.05 516.71</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </lod2MultiSurface>
        </con:WallSurface>
      </boundary>
      <boundary>
        <con:WallSurface gml:id=\"DEBY_LOD2_59772_30ce7949-9c18-4a98-bdae-afeb9a0b6252_2\">
          <lod2MultiSurface>
            <gml:MultiSurface srsDimension=\"3\">
              <gml:surfaceMember>
                <gml:Polygon gml:id=\"DEBY_LOD2_59772_30ce7949-9c18-4a98-bdae-afeb9a0b6252_2_poly\">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:posList>691472.6 5334821.26 516.71 691472.6 5334821.26 528.425 691474.24 5334826.79 528.425 691474.24 5334826.79 516.71 691472.6 5334821.26 516.71</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </lod2MultiSurface>
        </con:WallSurface>
      </boundary>
      <boundary>
        <con:WallSurface gml:id=\"DEBY_LOD2_59772_27c754d1-d65b-4b5e-a17a-8a24080009e1_2\">
          <lod2MultiSurface>
            <gml:MultiSurface srsDimension=\"3\">
              <gml:surfaceMember>
                <gml:Polygon gml:id=\"DEBY_LOD2_59772_27c754d1-d65b-4b5e-a17a-8a24080009e1_2_poly\">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:posList>691475.29 5334827.01 516.71 691475.29 5334827.01 528.425 691478.01 5334825.81 528.425 691478.01 5334825.81 516.71 691475.29 5334827.01 516.71</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </lod2MultiSurface>
        </con:WallSurface>
      </boundary>
      <boundary>
        <con:GroundSurface gml:id=\"DEBY_LOD2_59772_bae63dbe-80b8-4e3a-a78e-755230366512_2\">
          <lod2MultiSurface>
            <gml:MultiSurface srsDimension=\"3\">
              <gml:surfaceMember>
                <gml:Polygon gml:id=\"DEBY_LOD2_59772_bae63dbe-80b8-4e3a-a78e-755230366512_2_poly\">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:posList>691470.29 5334815.2 516.71 691470.53 5334815.81 516.71 691472.46 5334820.87 516.71 691472.6 5334821.26 516.71 691474.24 5334826.79 516.71 691475.29 5334827.01 516.71 691478.01 5334825.81 516.71 691473.38 5334813.05 516.71 691470.72 5334813.99 516.71 691470.29 5334815.2 516.71</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </lod2MultiSurface>
        </con:GroundSurface>
      </boundary>
      <boundary>
        <con:WallSurface gml:id=\"DEBY_LOD2_59772_c21df86c-d952-4aa9-a5e2-42418b07a2a9_2\">
          <lod2MultiSurface>
            <gml:MultiSurface srsDimension=\"3\">
              <gml:surfaceMember>
                <gml:Polygon gml:id=\"DEBY_LOD2_59772_c21df86c-d952-4aa9-a5e2-42418b07a2a9_2_poly\">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:posList>691470.53 5334815.81 516.71 691470.53 5334815.81 528.425 691472.46 5334820.87 528.425 691472.46 5334820.87 516.71 691470.53 5334815.81 516.71</gml:posList>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </lod2MultiSurface>
        </con:WallSurface>
      </boundary>
      <bldg:function>31001_9998</bldg:function>
      <bldg:roofType>1000</bldg:roofType>
      <bldg:storeysAboveGround>3</bldg:storeysAboveGround>
    </bldg:Building>";

        let xml_element_index =
            XmlDocumentIndex::from_scan(xml_document, None).expect("should work");

        let boundary_index = xml_element_index.get(CityGmlElement::BoundaryProperty);
        assert_eq!(boundary_index.len(), 11);

        /*for (gml_element, index) in gml_element_index {
            for current_index in index {
                let snippet = &xml_document[current_index.range()];
                let a = String::from_utf8_lossy(snippet);

                println!("abc: {:?}", a);
            }
        }*/
    }

    #[test]
    fn test_deserialize_basic() {
        let xml_document = b"<bldg:Building gml:id=\"DEBY_LOD2_59772\">
      <creationDate >2023-06-05T00:00:00+02:00</creationDate>
      <externalReference>
        <ExternalReference>
          <targetResource>DEBYvAAAAABTy70E</targetResource>
          <informationSystem>http://repository.gdi-de.org/schemas/adv/citygml/fdv/art.htm#_9100</informationSystem>
        </ExternalReference>
      </externalReference>
      <boundary xlink:href=\"#DEBY_LOD2_59772_4becb506-d53b-44ca-a483-e6a3d238b4c2_2\"></boundary>
    </bldg:Building>";

        let xml_element_index =
            XmlDocumentIndex::from_scan(xml_document, None).expect("should work");

        let boundary_index = xml_element_index
            .first(CityGmlElement::BoundaryProperty)
            .unwrap();
        let xml_snippet = &xml_document[boundary_index.range()];
        let xml_snippet_utf = String::from_utf8_lossy(xml_snippet);

        assert_eq!(
            xml_snippet_utf,
            "<boundary xlink:href=\"#DEBY_LOD2_59772_4becb506-d53b-44ca-a483-e6a3d238b4c2_2\"></boundary>"
        );
    }

    #[test]
    fn test_deserialize_with_tw() {
        let xml_document = b"<cityObjectMember>
        <bldg:Building gml:id=\"DEBY_LOD2_59772\">
        <creationDate >2023-06-05T00:00:00+02:00</creationDate>
        <boundary xlink:href=\"#DEBY_LOD2_59772_4becb506-d53b-44ca-a483-e6a3d238b4c2_2\"></boundary>
    </bldg:Building>
    </cityObjectMember>";

        let xml_element_index =
            XmlDocumentIndex::from_scan(xml_document, None).expect("should work");

        assert_eq!(
            xml_element_index
                .get(CityGmlElement::BoundaryProperty)
                .len(),
            0
        );
    }
}
