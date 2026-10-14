using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TunnelClassValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelClassValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(TunnelClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelClassValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(TunnelClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelClassValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TunnelClassValue* handle);
}