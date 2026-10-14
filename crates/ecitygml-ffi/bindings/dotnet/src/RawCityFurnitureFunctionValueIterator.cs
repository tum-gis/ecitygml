using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct CityFurnitureFunctionValueIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurnitureFunctionValueIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CityFurnitureFunctionValue* Next(CityFurnitureFunctionValueIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurnitureFunctionValueIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(CityFurnitureFunctionValueIterator* handle);
}