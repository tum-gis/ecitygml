using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct MeasureAttribute
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MeasureAttribute_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MeasureAttribute* TryFrom(GenericAttributeKind* attribute);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MeasureAttribute_name", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Name(MeasureAttribute* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MeasureAttribute_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Measure* Value(MeasureAttribute* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MeasureAttribute_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(MeasureAttribute* handle);
}