using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct PolygonPatch
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PolygonPatch_triangulate", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultTriangulationError Triangulate(PolygonPatch* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PolygonPatch_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PolygonPatch* TryFrom(AbstractSurfacePatchKind* patch);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PolygonPatch_exterior", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractRingKind* Exterior(PolygonPatch* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PolygonPatch_interior", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractRingKindIterator* Interior(PolygonPatch* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PolygonPatch_area_3d", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultDoubleError Area3d(PolygonPatch* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PolygonPatch_points", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPositionIterator* Points(PolygonPatch* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PolygonPatch_compute_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* ComputeEnvelope(PolygonPatch* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_PolygonPatch_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(PolygonPatch* handle);
}