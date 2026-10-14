using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct SectionPropertyIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SectionPropertyIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern SectionProperty* Next(SectionPropertyIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_SectionPropertyIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(SectionPropertyIterator* handle);
}