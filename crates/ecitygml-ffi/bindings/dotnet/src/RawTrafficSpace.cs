using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TrafficSpace
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_space_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionSpaceType SpaceType(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_lod1_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod1Solid(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_lod2_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod2Solid(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_lod3_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod3Solid(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_lod2_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2MultiCurve(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_lod3_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3MultiCurve(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_lod0_point", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PointProperty* Lod0Point(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_boundaries", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSpaceBoundaryPropertyIterator* Boundaries(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_lod1_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod1TerrainIntersectionCurve(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_lod2_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2TerrainIntersectionCurve(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_lod3_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3TerrainIntersectionCurve(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TrafficSpace* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_class", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TrafficSpaceClassValue* Class(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_functions", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TrafficSpaceFunctionValueIterator* Functions(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_usages", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TrafficSpaceUsageValueIterator* Usages(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_granularity", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GranularityValue Granularity(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_traffic_direction", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionTrafficDirectionValue TrafficDirection(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_occupancies", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern OccupancyIterator* Occupancies(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_predecessors", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TrafficSpaceReferenceIterator* Predecessors(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_successors", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TrafficSpaceReferenceIterator* Successors(TrafficSpace* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpace_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TrafficSpace* handle);
}