using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Shell
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Shell_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(Shell* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Shell_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(Shell* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Shell_triangulate", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultTriangulationError Triangulate(Shell* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Shell_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Shell* TryFrom(AbstractSurfaceKind* surface);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Shell_members", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractSurfacePropertyIterator* Members(Shell* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Shell_points", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPositionIterator* Points(Shell* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Shell_area_3d", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultDoubleError Area3d(Shell* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Shell_volume_3d", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultDoubleError Volume3d(Shell* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Shell_compute_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* ComputeEnvelope(Shell* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Shell_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Shell* handle);
}