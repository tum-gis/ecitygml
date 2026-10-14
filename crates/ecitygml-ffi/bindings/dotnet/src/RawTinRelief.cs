using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TinRelief
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinRelief_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(TinRelief* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinRelief_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(TinRelief* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinRelief_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(TinRelief* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinRelief_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(TinRelief* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinRelief_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(TinRelief* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinRelief_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(TinRelief* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinRelief_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(TinRelief* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinRelief_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(TinRelief* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinRelief_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(TinRelief* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinRelief_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(TinRelief* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinRelief_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(TinRelief* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinRelief_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(TinRelief* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinRelief_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(TinRelief* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinRelief_lod", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern LevelOfDetail Lod(TinRelief* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinRelief_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TinRelief* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinRelief_tin", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TinProperty* Tin(TinRelief* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TinRelief_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TinRelief* handle);
}