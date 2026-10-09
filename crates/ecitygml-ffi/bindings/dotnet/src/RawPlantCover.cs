using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct PlantCover
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_space_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionSpaceType SpaceType(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_lod1_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod1Solid(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_lod2_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod2Solid(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_lod3_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod3Solid(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_lod2_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2MultiCurve(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_lod3_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3MultiCurve(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_lod0_point", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PointProperty* Lod0Point(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_boundaries", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSpaceBoundaryPropertyIterator* Boundaries(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_lod1_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod1TerrainIntersectionCurve(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_lod2_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2TerrainIntersectionCurve(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_lod3_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3TerrainIntersectionCurve(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_lod1_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod1ImplicitRepresentation(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_lod2_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod2ImplicitRepresentation(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_lod3_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod3ImplicitRepresentation(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PlantCover* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_class", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PlantCoverClassValue* Class(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_functions", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PlantCoverFunctionValueIterator* Functions(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_usages", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PlantCoverUsageValueIterator* Usages(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_average_height", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Measure* AverageHeight(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_min_height", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Measure* MinHeight(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_max_height", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Measure* MaxHeight(PlantCover* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCover_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(PlantCover* handle);
}