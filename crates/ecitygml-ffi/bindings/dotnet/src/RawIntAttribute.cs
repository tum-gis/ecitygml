using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct IntAttribute
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_IntAttribute_name", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Name(IntAttribute* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_IntAttribute_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern long Value(IntAttribute* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_IntAttribute_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(IntAttribute* handle);
}