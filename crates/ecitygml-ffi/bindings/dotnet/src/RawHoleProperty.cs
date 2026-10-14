using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct HoleProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_HoleProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Hole* Object(HoleProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_HoleProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(HoleProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_HoleProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(HoleProperty* handle);
}