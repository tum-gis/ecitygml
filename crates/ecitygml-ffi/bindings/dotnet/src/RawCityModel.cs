using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct CityModel
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityModel_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(CityModel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityModel_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(CityModel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityModel_bounded_by", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BoundingShape* BoundedBy(CityModel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityModel_feature_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* FeatureId(CityModel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityModel_creation_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* CreationDate(CityModel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityModel_termination_date", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* TerminationDate(CityModel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityModel_valid_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidFrom(CityModel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityModel_valid_to", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DateTime* ValidTo(CityModel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityModel_apply_translation", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void ApplyTranslation(CityModel* handle, Vector3 vector);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityModel_apply_scale", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void ApplyScale(CityModel* handle, Scale3 scale);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityModel_iter_features", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractFeatureKindRefIterator* IterFeatures(CityModel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityModel_iter_city_objects", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractCityObjectKindRefIterator* IterCityObjects(CityModel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityModel_city_object_members", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractCityObjectPropertyIterator* CityObjectMembers(CityModel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityModel_recompute_child_bounding_shapes", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void RecomputeChildBoundingShapes(CityModel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityModel_city_objects_len", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern nuint CityObjectsLen(CityModel* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityModel_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(CityModel* handle);
}