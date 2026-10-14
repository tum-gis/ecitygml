using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct CityFurnitureFunctionValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurnitureFunctionValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(CityFurnitureFunctionValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurnitureFunctionValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(CityFurnitureFunctionValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurnitureFunctionValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(CityFurnitureFunctionValue* handle);
}