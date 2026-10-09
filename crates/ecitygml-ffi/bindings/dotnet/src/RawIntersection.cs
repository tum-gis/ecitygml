using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Intersection
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_space_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionSpaceType SpaceType(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_lod1_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod1Solid(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_lod2_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod2Solid(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_lod3_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod3Solid(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_lod2_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2MultiCurve(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_lod3_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3MultiCurve(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_lod0_point", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PointProperty* Lod0Point(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_boundaries", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSpaceBoundaryPropertyIterator* Boundaries(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_lod1_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod1TerrainIntersectionCurve(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_lod2_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2TerrainIntersectionCurve(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_lod3_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3TerrainIntersectionCurve(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_traffic_direction", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionTrafficDirectionValue TrafficDirection(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_occupancies", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern OccupancyIterator* Occupancies(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_traffic_spaces", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TrafficSpacePropertyIterator* TrafficSpaces(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_auxiliary_traffic_spaces", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AuxiliaryTrafficSpacePropertyIterator* AuxiliaryTrafficSpaces(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_markings", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MarkingPropertyIterator* Markings(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_holes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HolePropertyIterator* Holes(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Intersection* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_class", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern IntersectionClassValue* Class(Intersection* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Intersection_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Intersection* handle);
}