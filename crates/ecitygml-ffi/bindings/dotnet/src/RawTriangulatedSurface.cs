using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TriangulatedSurface
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TriangulatedSurface_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(TriangulatedSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TriangulatedSurface_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(TriangulatedSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TriangulatedSurface_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TriangulatedSurface* TryFrom(AbstractSurfaceKind* surface);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TriangulatedSurface_triangles", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TriangleIterator* Triangles(TriangulatedSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TriangulatedSurface_surface", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Surface* Surface(TriangulatedSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TriangulatedSurface_points", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPositionIterator* Points(TriangulatedSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TriangulatedSurface_area_3d", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultDoubleError Area3d(TriangulatedSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TriangulatedSurface_compute_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* ComputeEnvelope(TriangulatedSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TriangulatedSurface_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TriangulatedSurface* handle);
}