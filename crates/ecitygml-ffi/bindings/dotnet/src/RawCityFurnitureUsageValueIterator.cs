using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct CityFurnitureUsageValueIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurnitureUsageValueIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityFurnitureUsageValue* Next(CityFurnitureUsageValueIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurnitureUsageValueIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(CityFurnitureUsageValueIterator* handle);
}