using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct PlantCoverUsageValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCoverUsageValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(PlantCoverUsageValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCoverUsageValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(PlantCoverUsageValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCoverUsageValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(PlantCoverUsageValue* handle);
}