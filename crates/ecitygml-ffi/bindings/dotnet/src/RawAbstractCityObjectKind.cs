using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractCityObjectKind
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKind_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(AbstractCityObjectKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKind_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(AbstractCityObjectKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKind_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(AbstractCityObjectKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKind_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(AbstractCityObjectKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKind_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(AbstractCityObjectKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKind_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(AbstractCityObjectKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKind_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(AbstractCityObjectKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKind_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(AbstractCityObjectKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKind_relative_to_terrain", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToTerrain RelativeToTerrain(AbstractCityObjectKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKind_relative_to_water", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatOptionRelativeToWater RelativeToWater(AbstractCityObjectKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKind_external_references", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ExternalReferenceIterator* ExternalReferences(AbstractCityObjectKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKind_generic_attributes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GenericAttributeKindIterator* GenericAttributes(AbstractCityObjectKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKind_related_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelationPropertyIterator* RelatedTo(AbstractCityObjectKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKind_feature_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern FeatureType FeatureType(AbstractCityObjectKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKind_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractCityObjectKind* handle);
}