using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct CityFurniture
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_space_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionSpaceType SpaceType(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_lod1_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod1Solid(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_lod2_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod2Solid(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_lod3_solid", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolidProperty* Lod3Solid(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_lod2_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2MultiCurve(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_lod3_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3MultiCurve(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_lod0_point", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PointProperty* Lod0Point(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_boundaries", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSpaceBoundaryPropertyIterator* Boundaries(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_lod1_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod1TerrainIntersectionCurve(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_lod2_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod2TerrainIntersectionCurve(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_lod3_terrain_intersection_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod3TerrainIntersectionCurve(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_lod1_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod1ImplicitRepresentation(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_lod2_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod2ImplicitRepresentation(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_lod3_implicit_representation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ImplicitGeometryProperty* Lod3ImplicitRepresentation(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityFurniture* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_class", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityFurnitureClassValue* Class(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_functions", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityFurnitureFunctionValueIterator* Functions(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_usages", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityFurnitureUsageValueIterator* Usages(CityFurniture* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurniture_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(CityFurniture* handle);
}