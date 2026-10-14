using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Building
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_space_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionSpaceType SpaceType(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_lod1_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod1Solid(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_lod2_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod2Solid(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_lod3_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod3Solid(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_lod2_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2MultiCurve(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_lod3_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3MultiCurve(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_lod0_point", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PointProperty* Lod0Point(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_boundaries", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSpaceBoundaryPropertyIterator* Boundaries(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_lod1_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod1TerrainIntersectionCurve(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_lod2_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2TerrainIntersectionCurve(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_lod3_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3TerrainIntersectionCurve(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_lod1_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod1ImplicitRepresentation(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_lod2_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod2ImplicitRepresentation(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_lod3_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod3ImplicitRepresentation(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_date_of_construction", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Date* DateOfConstruction(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_date_of_demolition", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Date* DateOfDemolition(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_heights", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HeightIterator* Heights(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_occupancies", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern OccupancyIterator* Occupancies(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_class", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingClassValue* Class(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_functions", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingFunctionValueIterator* Functions(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_usages", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingUsageValueIterator* Usages(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_roof_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern RoofTypeValue* RoofType(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_storeys_above_ground", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionLong StoreysAboveGround(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_storeys_below_ground", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionLong StoreysBelowGround(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_building_subdivisions", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractBuildingSubdivisionPropertyIterator* BuildingSubdivisions(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Building* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_building_parts", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingPartPropertyIterator* BuildingParts(Building* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Building_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Building* handle);
}