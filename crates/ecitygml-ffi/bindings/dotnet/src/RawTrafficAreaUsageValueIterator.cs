using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TrafficAreaUsageValueIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficAreaUsageValueIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TrafficAreaUsageValue* Next(TrafficAreaUsageValueIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficAreaUsageValueIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TrafficAreaUsageValueIterator* handle);
}