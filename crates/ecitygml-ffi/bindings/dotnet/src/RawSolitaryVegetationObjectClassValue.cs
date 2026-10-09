using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct SolitaryVegetationObjectClassValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SolitaryVegetationObjectClassValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(SolitaryVegetationObjectClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SolitaryVegetationObjectClassValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(SolitaryVegetationObjectClassValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SolitaryVegetationObjectClassValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(SolitaryVegetationObjectClassValue* handle);
}