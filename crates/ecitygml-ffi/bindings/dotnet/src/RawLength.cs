using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Length
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Length_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern double Value(Length* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Length_uom", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Uom(Length* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Length_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Length* handle);
}