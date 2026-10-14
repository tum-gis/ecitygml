using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct BridgePart
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_space_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionSpaceType SpaceType(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_lod1_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod1Solid(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_lod2_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod2Solid(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_lod3_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod3Solid(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_lod2_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2MultiCurve(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_lod3_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3MultiCurve(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_lod0_point", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PointProperty* Lod0Point(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_boundaries", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSpaceBoundaryPropertyIterator* Boundaries(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_lod1_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod1TerrainIntersectionCurve(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_lod2_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2TerrainIntersectionCurve(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_lod3_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3TerrainIntersectionCurve(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_lod1_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod1ImplicitRepresentation(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_lod2_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod2ImplicitRepresentation(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_lod3_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod3ImplicitRepresentation(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_date_of_construction", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Date* DateOfConstruction(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_date_of_demolition", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Date* DateOfDemolition(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_heights", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HeightIterator* Heights(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_occupancies", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern OccupancyIterator* Occupancies(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_class", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BridgeClassValue* Class(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_functions", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BridgeFunctionValueIterator* Functions(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_usages", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BridgeUsageValueIterator* Usages(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_is_movable", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionBool IsMovable(BridgePart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BridgePart* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePart_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(BridgePart* handle);
}