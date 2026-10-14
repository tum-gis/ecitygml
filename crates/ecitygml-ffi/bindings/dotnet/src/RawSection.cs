using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Section
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_space_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionSpaceType SpaceType(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_lod1_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod1Solid(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_lod2_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod2Solid(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_lod3_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod3Solid(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_lod2_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2MultiCurve(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_lod3_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3MultiCurve(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_lod0_point", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PointProperty* Lod0Point(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_boundaries", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSpaceBoundaryPropertyIterator* Boundaries(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_lod1_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod1TerrainIntersectionCurve(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_lod2_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2TerrainIntersectionCurve(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_lod3_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3TerrainIntersectionCurve(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_traffic_direction", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionTrafficDirectionValue TrafficDirection(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_occupancies", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern OccupancyIterator* Occupancies(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_traffic_spaces", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TrafficSpacePropertyIterator* TrafficSpaces(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_auxiliary_traffic_spaces", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AuxiliaryTrafficSpacePropertyIterator* AuxiliaryTrafficSpaces(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_markings", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MarkingPropertyIterator* Markings(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_holes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HolePropertyIterator* Holes(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Section* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_class", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SectionClassValue* Class(Section* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Section_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Section* handle);
}