using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct MultiCurveProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiCurveProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurve* Object(MultiCurveProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiCurveProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(MultiCurveProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiCurveProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(MultiCurveProperty* handle);
}