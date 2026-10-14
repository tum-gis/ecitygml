using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct RoofSurface
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_lod1_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod1MultiSurface(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_filling_surfaces", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractFillingSurfacePropertyIterator* FillingSurfaces(RoofSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern RoofSurface* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_RoofSurface_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(RoofSurface* handle);
}