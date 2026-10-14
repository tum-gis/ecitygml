using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TunnelFunctionValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelFunctionValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(TunnelFunctionValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelFunctionValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(TunnelFunctionValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelFunctionValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TunnelFunctionValue* handle);
}