using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Triangulation
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Triangulation_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TriangulatedSurface* Surface(Triangulation* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Triangulation_has_skipped", CallingConvention = CallingConvention.Cdecl)]
    [return: MarshalAs(UnmanagedType.U1)]
    internal static unsafe extern bool HasSkipped(Triangulation* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Triangulation_skipped", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TriangulationSkippedIterator* Skipped(Triangulation* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Triangulation_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Triangulation* handle);
}