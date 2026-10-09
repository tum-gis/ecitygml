using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct HeightIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_HeightIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Height* Next(HeightIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_HeightIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(HeightIterator* handle);
}