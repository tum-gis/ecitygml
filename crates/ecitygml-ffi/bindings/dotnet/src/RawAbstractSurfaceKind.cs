using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractSurfaceKind
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractSurfaceKind_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(AbstractSurfaceKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractSurfaceKind_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(AbstractSurfaceKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractSurfaceKind_triangulate", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultTriangulationError Triangulate(AbstractSurfaceKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractSurfaceKind_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSurfaceKind* TryFrom(AbstractGeometryKind* geometry);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractSurfaceKind_geometry_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GeometryType GeometryType(AbstractSurfaceKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractSurfaceKind_area_3d", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultDoubleError Area3d(AbstractSurfaceKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractSurfaceKind_points", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPositionIterator* Points(AbstractSurfaceKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractSurfaceKind_compute_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* ComputeEnvelope(AbstractSurfaceKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractSurfaceKind_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractSurfaceKind* handle);
}