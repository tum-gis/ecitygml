using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct DoubleAttribute
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoubleAttribute_name", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Name(DoubleAttribute* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoubleAttribute_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern double Value(DoubleAttribute* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_DoubleAttribute_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(DoubleAttribute* handle);
}