using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct WallSurface
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_lod1_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod1MultiSurface(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_filling_surfaces", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractFillingSurfacePropertyIterator* FillingSurfaces(WallSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern WallSurface* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_WallSurface_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(WallSurface* handle);
}