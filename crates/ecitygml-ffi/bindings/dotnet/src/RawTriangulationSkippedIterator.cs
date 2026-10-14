using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TriangulationSkippedIterator
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TriangulationSkippedIterator_next", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Error* Next(TriangulationSkippedIterator* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TriangulationSkippedIterator_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TriangulationSkippedIterator* handle);
}