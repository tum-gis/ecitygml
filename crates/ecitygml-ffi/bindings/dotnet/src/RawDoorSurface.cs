using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct DoorSurface
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(DoorSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(DoorSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(DoorSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(DoorSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(DoorSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(DoorSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(DoorSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(DoorSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(DoorSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(DoorSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(DoorSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(DoorSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(DoorSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(DoorSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(DoorSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_lod1_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod1MultiSurface(DoorSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(DoorSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(DoorSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DoorSurface* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoorSurface_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(DoorSurface* handle);
}