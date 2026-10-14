using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TrafficArea
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_lod1_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod1MultiSurface(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TrafficArea* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_class", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TrafficAreaClassValue* Class(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_functions", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TrafficAreaFunctionValueIterator* Functions(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_usages", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TrafficAreaUsageValueIterator* Usages(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_surface_material", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SurfaceMaterialValue* SurfaceMaterial(TrafficArea* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficArea_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TrafficArea* handle);
}