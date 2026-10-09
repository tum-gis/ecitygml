using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TunnelPart
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_space_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionSpaceType SpaceType(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_lod1_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod1Solid(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_lod2_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod2Solid(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_lod3_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod3Solid(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_lod2_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2MultiCurve(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_lod3_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3MultiCurve(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_lod0_point", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PointProperty* Lod0Point(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_boundaries", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSpaceBoundaryPropertyIterator* Boundaries(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_lod1_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod1TerrainIntersectionCurve(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_lod2_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2TerrainIntersectionCurve(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_lod3_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3TerrainIntersectionCurve(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_lod1_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod1ImplicitRepresentation(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_lod2_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod2ImplicitRepresentation(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_lod3_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod3ImplicitRepresentation(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_date_of_construction", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Date* DateOfConstruction(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_date_of_demolition", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Date* DateOfDemolition(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_heights", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HeightIterator* Heights(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_occupancies", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern OccupancyIterator* Occupancies(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_class", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TunnelClassValue* Class(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_functions", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TunnelFunctionValueIterator* Functions(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_usages", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TunnelUsageValueIterator* Usages(TunnelPart* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TunnelPart* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPart_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TunnelPart* handle);
}