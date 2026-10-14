using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TriangleIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TriangleIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Triangle* Next(TriangleIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TriangleIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TriangleIterator* handle);
}