using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct SpeciesValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SpeciesValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(SpeciesValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SpeciesValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(SpeciesValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SpeciesValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(SpeciesValue* handle);
}