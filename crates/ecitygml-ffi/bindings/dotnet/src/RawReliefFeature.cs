using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct ReliefFeature
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ReliefFeature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(ReliefFeature* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ReliefFeature_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(ReliefFeature* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ReliefFeature_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(ReliefFeature* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ReliefFeature_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(ReliefFeature* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ReliefFeature_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(ReliefFeature* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ReliefFeature_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(ReliefFeature* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ReliefFeature_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(ReliefFeature* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ReliefFeature_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(ReliefFeature* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ReliefFeature_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(ReliefFeature* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ReliefFeature_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(ReliefFeature* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ReliefFeature_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(ReliefFeature* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ReliefFeature_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(ReliefFeature* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ReliefFeature_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(ReliefFeature* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ReliefFeature_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ReliefFeature* TryFrom(AbstractFeatureKindRef* feature);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ReliefFeature_lod", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern LevelOfDetail Lod(ReliefFeature* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ReliefFeature_relief_components", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractReliefComponentPropertyIterator* ReliefComponents(ReliefFeature* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ReliefFeature_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(ReliefFeature* handle);
}