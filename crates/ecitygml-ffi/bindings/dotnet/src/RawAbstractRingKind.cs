using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractRingKind
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractRingKind_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(AbstractRingKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractRingKind_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(AbstractRingKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractRingKind_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractRingKind* TryFrom(AbstractCurveKind* curve);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractRingKind_geometry_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GeometryType GeometryType(AbstractRingKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractRingKind_points", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DirectPositionIterator* Points(AbstractRingKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractRingKind_length_3d", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern double Length3d(AbstractRingKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractRingKind_area_3d", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern double Area3d(AbstractRingKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractRingKind_compute_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* ComputeEnvelope(AbstractRingKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractRingKind_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractRingKind* handle);
}