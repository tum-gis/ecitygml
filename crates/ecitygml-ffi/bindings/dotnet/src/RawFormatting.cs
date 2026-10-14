using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Formatting
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Formatting_compact", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Formatting* Compact();

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Formatting_new_line", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Formatting* NewLine();

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Formatting_indent", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Formatting* Indent(byte @char, nuint size);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Formatting_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Formatting* handle);
}