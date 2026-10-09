using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Measure
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Measure_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern double Value(Measure* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Measure_uom", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Uom(Measure* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Measure_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Measure* handle);
}