using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Road
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_space_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionSpaceType SpaceType(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_lod1_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod1Solid(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_lod2_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod2Solid(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_lod3_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod3Solid(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_lod2_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2MultiCurve(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_lod3_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3MultiCurve(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_lod0_point", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PointProperty* Lod0Point(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_boundaries", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSpaceBoundaryPropertyIterator* Boundaries(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_lod1_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod1TerrainIntersectionCurve(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_lod2_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2TerrainIntersectionCurve(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_lod3_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3TerrainIntersectionCurve(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_traffic_direction", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionTrafficDirectionValue TrafficDirection(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_occupancies", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern OccupancyIterator* Occupancies(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_traffic_spaces", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TrafficSpacePropertyIterator* TrafficSpaces(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_auxiliary_traffic_spaces", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AuxiliaryTrafficSpacePropertyIterator* AuxiliaryTrafficSpaces(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_markings", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MarkingPropertyIterator* Markings(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_holes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HolePropertyIterator* Holes(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Road* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_class", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern RoadClassValue* Class(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_functions", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern RoadFunctionValueIterator* Functions(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_usages", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern RoadUsageValueIterator* Usages(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_sections", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SectionPropertyIterator* Sections(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_intersections", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern IntersectionPropertyIterator* Intersections(Road* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Road_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Road* handle);
}