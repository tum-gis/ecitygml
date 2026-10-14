using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct BuildingPart
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_space_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionSpaceType SpaceType(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_lod1_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod1Solid(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_lod2_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod2Solid(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_lod3_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod3Solid(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_lod2_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2MultiCurve(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_lod3_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3MultiCurve(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_lod0_point", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PointProperty* Lod0Point(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_boundaries", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSpaceBoundaryPropertyIterator* Boundaries(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_lod1_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod1TerrainIntersectionCurve(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_lod2_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2TerrainIntersectionCurve(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_lod3_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3TerrainIntersectionCurve(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_lod1_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod1ImplicitRepresentation(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_lod2_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod2ImplicitRepresentation(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_lod3_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod3ImplicitRepresentation(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_date_of_construction", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Date* DateOfConstruction(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_date_of_demolition", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Date* DateOfDemolition(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_heights", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HeightIterator* Heights(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_occupancies", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern OccupancyIterator* Occupancies(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_class", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingClassValue* Class(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_functions", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingFunctionValueIterator* Functions(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_usages", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingUsageValueIterator* Usages(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_roof_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern RoofTypeValue* RoofType(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_storeys_above_ground", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionLong StoreysAboveGround(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_storeys_below_ground", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionLong StoreysBelowGround(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_building_subdivisions", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractBuildingSubdivisionPropertyIterator* BuildingSubdivisions(BuildingPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BuildingPart* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BuildingPart_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(BuildingPart* handle);
}