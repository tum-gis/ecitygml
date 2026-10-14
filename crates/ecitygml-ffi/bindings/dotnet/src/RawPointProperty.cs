using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct PointProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PointProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Point* Object(PointProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PointProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(PointProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PointProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(PointProperty* handle);
}