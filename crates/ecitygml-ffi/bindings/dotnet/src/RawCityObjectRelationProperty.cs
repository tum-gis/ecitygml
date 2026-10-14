using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct CityObjectRelationProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityObjectRelationProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityObjectRelation* Object(CityObjectRelationProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityObjectRelationProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(CityObjectRelationProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityObjectRelationProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(CityObjectRelationProperty* handle);
}