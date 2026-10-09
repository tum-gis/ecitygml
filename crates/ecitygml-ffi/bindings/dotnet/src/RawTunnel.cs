using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Tunnel
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_space_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionSpaceType SpaceType(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_lod1_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod1Solid(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_lod2_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod2Solid(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_lod3_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod3Solid(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_lod2_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2MultiCurve(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_lod3_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3MultiCurve(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_lod0_point", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PointProperty* Lod0Point(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_boundaries", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSpaceBoundaryPropertyIterator* Boundaries(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_lod1_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod1TerrainIntersectionCurve(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_lod2_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2TerrainIntersectionCurve(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_lod3_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3TerrainIntersectionCurve(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_lod1_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod1ImplicitRepresentation(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_lod2_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod2ImplicitRepresentation(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_lod3_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod3ImplicitRepresentation(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_date_of_construction", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Date* DateOfConstruction(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_date_of_demolition", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Date* DateOfDemolition(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_heights", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HeightIterator* Heights(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_occupancies", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern OccupancyIterator* Occupancies(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_class", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TunnelClassValue* Class(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_functions", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TunnelFunctionValueIterator* Functions(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_usages", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TunnelUsageValueIterator* Usages(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Tunnel* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_tunnel_parts", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TunnelPartPropertyIterator* TunnelParts(Tunnel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Tunnel_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Tunnel* handle);
}