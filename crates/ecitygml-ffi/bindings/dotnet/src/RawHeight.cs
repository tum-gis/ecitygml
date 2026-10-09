using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Height
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Height_high_reference", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ElevationReferenceValue* HighReference(Height* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Height_low_reference", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ElevationReferenceValue* LowReference(Height* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Height_status", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HeightStatusValue Status(Height* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Height_length", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Length* Length(Height* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Height_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Height* handle);
}