using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct BridgePartProperty
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePartProperty_object", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern BridgePart* Object(BridgePartProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePartProperty_href", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HRef* Href(BridgePartProperty* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgePartProperty_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(BridgePartProperty* handle);
}