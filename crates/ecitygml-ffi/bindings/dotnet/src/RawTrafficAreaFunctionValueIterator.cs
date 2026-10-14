using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TrafficAreaFunctionValueIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficAreaFunctionValueIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TrafficAreaFunctionValue* Next(TrafficAreaFunctionValueIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TrafficAreaFunctionValueIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TrafficAreaFunctionValueIterator* handle);
}