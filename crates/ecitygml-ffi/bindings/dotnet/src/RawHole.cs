using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Hole
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_space_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionSpaceType SpaceType(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_lod1_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod1Solid(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_lod2_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod2Solid(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_lod3_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod3Solid(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_lod2_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2MultiCurve(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_lod3_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3MultiCurve(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_lod0_point", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PointProperty* Lod0Point(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_boundaries", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSpaceBoundaryPropertyIterator* Boundaries(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_lod1_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod1TerrainIntersectionCurve(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_lod2_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2TerrainIntersectionCurve(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_lod3_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3TerrainIntersectionCurve(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Hole* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_class", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HoleClassValue* Class(Hole* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Hole_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Hole* handle);
}