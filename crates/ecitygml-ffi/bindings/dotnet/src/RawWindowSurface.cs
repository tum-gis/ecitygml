using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct WindowSurface
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(WindowSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(WindowSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(WindowSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(WindowSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(WindowSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(WindowSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(WindowSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(WindowSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(WindowSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(WindowSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(WindowSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(WindowSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(WindowSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(WindowSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(WindowSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_lod1_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod1MultiSurface(WindowSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(WindowSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(WindowSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern WindowSurface* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WindowSurface_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(WindowSurface* handle);
}