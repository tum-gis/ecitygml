using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractCityObjectKindRef
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKindRef_from_city_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractCityObjectKindRef* FromCityObject(AbstractCityObjectKind* cityObject);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKindRef_feature_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern FeatureType FeatureType(AbstractCityObjectKindRef* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCityObjectKindRef_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractCityObjectKindRef* handle);
}