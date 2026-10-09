using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TunnelPartProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPartProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TunnelPart* Object(TunnelPartProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPartProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(TunnelPartProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelPartProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TunnelPartProperty* handle);
}