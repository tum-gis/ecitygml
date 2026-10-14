using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Bridge
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_space_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionSpaceType SpaceType(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_lod1_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod1Solid(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_lod2_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod2Solid(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_lod3_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod3Solid(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_lod2_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2MultiCurve(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_lod3_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3MultiCurve(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_lod0_point", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PointProperty* Lod0Point(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_boundaries", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSpaceBoundaryPropertyIterator* Boundaries(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_lod1_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod1TerrainIntersectionCurve(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_lod2_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2TerrainIntersectionCurve(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_lod3_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3TerrainIntersectionCurve(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_lod1_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod1ImplicitRepresentation(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_lod2_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod2ImplicitRepresentation(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_lod3_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod3ImplicitRepresentation(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_date_of_construction", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Date* DateOfConstruction(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_date_of_demolition", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Date* DateOfDemolition(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_heights", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HeightIterator* Heights(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_occupancies", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern OccupancyIterator* Occupancies(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_class", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BridgeClassValue* Class(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_functions", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BridgeFunctionValueIterator* Functions(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_usages", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BridgeUsageValueIterator* Usages(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_is_movable", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionBool IsMovable(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Bridge* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_bridge_parts", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BridgePartPropertyIterator* BridgeParts(Bridge* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Bridge_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Bridge* handle);
}