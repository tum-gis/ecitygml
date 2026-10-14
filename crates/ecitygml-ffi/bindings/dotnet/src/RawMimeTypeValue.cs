using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct MimeTypeValue
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MimeTypeValue_code", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Code* Code(MimeTypeValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MimeTypeValue_value", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Value(MimeTypeValue* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MimeTypeValue_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(MimeTypeValue* handle);
}