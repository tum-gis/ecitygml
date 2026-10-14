using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AuxiliaryTrafficAreaFunctionValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AuxiliaryTrafficAreaFunctionValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(AuxiliaryTrafficAreaFunctionValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AuxiliaryTrafficAreaFunctionValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(AuxiliaryTrafficAreaFunctionValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AuxiliaryTrafficAreaFunctionValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AuxiliaryTrafficAreaFunctionValue* handle);
}