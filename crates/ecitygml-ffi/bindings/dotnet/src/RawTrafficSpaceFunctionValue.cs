using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TrafficSpaceFunctionValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpaceFunctionValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(TrafficSpaceFunctionValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpaceFunctionValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(TrafficSpaceFunctionValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficSpaceFunctionValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TrafficSpaceFunctionValue* handle);
}