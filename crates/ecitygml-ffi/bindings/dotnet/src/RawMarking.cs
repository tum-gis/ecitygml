using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Marking
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_lod0_multi_curve", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurveProperty* Lod0MultiCurve(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_lod0_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod0MultiSurface(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_lod1_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod1MultiSurface(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_lod2_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod2MultiSurface(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_lod3_multi_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurfaceProperty* Lod3MultiSurface(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Marking* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_class", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MarkingClassValue* Class(Marking* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Marking_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Marking* handle);
}