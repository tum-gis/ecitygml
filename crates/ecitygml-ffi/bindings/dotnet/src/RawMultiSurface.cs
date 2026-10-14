using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct MultiSurface
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiSurface_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(MultiSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiSurface_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(MultiSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiSurface_triangulate", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultTriangulationError Triangulate(MultiSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiSurface_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiSurface* TryFrom(AbstractGeometryKind* geometry);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiSurface_surface_member", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSurfacePropertyIterator* SurfaceMember(MultiSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiSurface_area_3d", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultDoubleError Area3d(MultiSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiSurface_points", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPositionIterator* Points(MultiSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiSurface_compute_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* ComputeEnvelope(MultiSurface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiSurface_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(MultiSurface* handle);
}