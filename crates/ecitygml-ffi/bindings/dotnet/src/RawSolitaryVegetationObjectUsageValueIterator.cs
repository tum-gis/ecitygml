using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct SolitaryVegetationObjectUsageValueIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SolitaryVegetationObjectUsageValueIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SolitaryVegetationObjectUsageValue* Next(SolitaryVegetationObjectUsageValueIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SolitaryVegetationObjectUsageValueIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(SolitaryVegetationObjectUsageValueIterator* handle);
}