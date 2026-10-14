using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractCurveProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCurveProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractCurveKind* Object(AbstractCurveProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCurveProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(AbstractCurveProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCurveProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractCurveProperty* handle);
}