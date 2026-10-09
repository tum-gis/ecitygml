using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct CompositeSurface
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CompositeSurface_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(CompositeSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CompositeSurface_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(CompositeSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CompositeSurface_triangulate", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultTriangulationError Triangulate(CompositeSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CompositeSurface_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CompositeSurface* TryFrom(AbstractSurfaceKind* surface);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CompositeSurface_surface_member", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSurfacePropertyIterator* SurfaceMember(CompositeSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CompositeSurface_area_3d", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultDoubleError Area3d(CompositeSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CompositeSurface_points", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPositionIterator* Points(CompositeSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CompositeSurface_compute_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* ComputeEnvelope(CompositeSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_CompositeSurface_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(CompositeSurface* handle);
}