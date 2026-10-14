using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct HolePropertyIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_HolePropertyIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern HoleProperty* Next(HolePropertyIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_HolePropertyIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(HolePropertyIterator* handle);
}