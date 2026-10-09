using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractFeatureKindRef
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractFeatureKindRef_from_space_boundary", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractFeatureKindRef* FromSpaceBoundary(AbstractSpaceBoundaryKind* boundary);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractFeatureKindRef_from_city_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractFeatureKindRef* FromCityObject(AbstractCityObjectKindRef* cityObject);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractFeatureKindRef_feature_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern FeatureType FeatureType(AbstractFeatureKindRef* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractFeatureKindRef_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractFeatureKindRef* handle);
}