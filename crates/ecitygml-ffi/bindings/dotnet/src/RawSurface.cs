using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Surface
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Surface_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(Surface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Surface_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(Surface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Surface_triangulate", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultTriangulationError Triangulate(Surface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Surface_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Surface* TryFrom(AbstractSurfaceKind* surface);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Surface_patches", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSurfacePatchKindIterator* Patches(Surface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Surface_area_3d", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultDoubleError Area3d(Surface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Surface_points", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPositionIterator* Points(Surface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Surface_compute_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* ComputeEnvelope(Surface* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Surface_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Surface* handle);
}