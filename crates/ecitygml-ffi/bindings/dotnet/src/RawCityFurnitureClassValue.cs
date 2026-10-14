using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct CityFurnitureClassValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurnitureClassValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(CityFurnitureClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurnitureClassValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(CityFurnitureClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CityFurnitureClassValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(CityFurnitureClassValue* handle);
}