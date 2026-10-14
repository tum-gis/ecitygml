using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TunnelUsageValueIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelUsageValueIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TunnelUsageValue* Next(TunnelUsageValueIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TunnelUsageValueIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TunnelUsageValueIterator* handle);
}