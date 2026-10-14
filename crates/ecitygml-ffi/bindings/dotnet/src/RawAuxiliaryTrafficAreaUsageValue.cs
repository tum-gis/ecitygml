using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AuxiliaryTrafficAreaUsageValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AuxiliaryTrafficAreaUsageValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(AuxiliaryTrafficAreaUsageValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AuxiliaryTrafficAreaUsageValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(AuxiliaryTrafficAreaUsageValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AuxiliaryTrafficAreaUsageValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AuxiliaryTrafficAreaUsageValue* handle);
}