using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct IntervalValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_IntervalValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(IntervalValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_IntervalValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(IntervalValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_IntervalValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(IntervalValue* handle);
}