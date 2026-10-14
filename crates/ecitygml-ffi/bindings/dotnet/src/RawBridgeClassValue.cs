using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct BridgeClassValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgeClassValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(BridgeClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgeClassValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(BridgeClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_BridgeClassValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(BridgeClassValue* handle);
}