using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AuxiliaryTrafficSpaceFunctionValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AuxiliaryTrafficSpaceFunctionValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(AuxiliaryTrafficSpaceFunctionValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AuxiliaryTrafficSpaceFunctionValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(AuxiliaryTrafficSpaceFunctionValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AuxiliaryTrafficSpaceFunctionValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AuxiliaryTrafficSpaceFunctionValue* handle);
}