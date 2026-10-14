using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct PlantCoverUsageValueIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCoverUsageValueIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PlantCoverUsageValue* Next(PlantCoverUsageValueIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PlantCoverUsageValueIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(PlantCoverUsageValueIterator* handle);
}