using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Polygon
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Polygon_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(Polygon* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Polygon_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(Polygon* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Polygon_triangulate", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultTriangulationError Triangulate(Polygon* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Polygon_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Polygon* TryFrom(AbstractSurfaceKind* surface);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Polygon_exterior", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractRingKind* Exterior(Polygon* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Polygon_interior", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractRingKindIterator* Interior(Polygon* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Polygon_area_3d", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultDoubleError Area3d(Polygon* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Polygon_points", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPositionIterator* Points(Polygon* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Polygon_compute_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* ComputeEnvelope(Polygon* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Polygon_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Polygon* handle);
}