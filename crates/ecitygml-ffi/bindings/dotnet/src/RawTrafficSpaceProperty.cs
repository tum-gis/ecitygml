using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TrafficSpaceProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpaceProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TrafficSpace* Object(TrafficSpaceProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpaceProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(TrafficSpaceProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpaceProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TrafficSpaceProperty* handle);
}