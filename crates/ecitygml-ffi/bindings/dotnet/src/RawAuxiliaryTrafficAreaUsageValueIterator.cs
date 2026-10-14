using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AuxiliaryTrafficAreaUsageValueIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AuxiliaryTrafficAreaUsageValueIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AuxiliaryTrafficAreaUsageValue* Next(AuxiliaryTrafficAreaUsageValueIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AuxiliaryTrafficAreaUsageValueIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AuxiliaryTrafficAreaUsageValueIterator* handle);
}