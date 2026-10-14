using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct Solid
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Solid_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(Solid* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Solid_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(Solid* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Solid_triangulate", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultTriangulationError Triangulate(Solid* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Solid_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Solid* TryFrom(AbstractGeometryKind* geometry);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Solid_exterior", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Shell* Exterior(Solid* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Solid_interior", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern ShellIterator* Interior(Solid* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Solid_volume_3d", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultDoubleError Volume3d(Solid* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Solid_compute_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* ComputeEnvelope(Solid* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Solid_points", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPositionIterator* Points(Solid* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_Solid_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(Solid* handle);
}