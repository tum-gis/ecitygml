using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct GroundSurface
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_lod1_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod1MultiSurface(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_filling_surfaces", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractFillingSurfacePropertyIterator* FillingSurfaces(GroundSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GroundSurface* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GroundSurface_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(GroundSurface* handle);
}