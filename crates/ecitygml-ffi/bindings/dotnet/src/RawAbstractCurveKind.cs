using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct AbstractCurveKind
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCurveKind_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(AbstractCurveKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCurveKind_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(AbstractCurveKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCurveKind_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractCurveKind* TryFrom(AbstractGeometryKind* geometry);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCurveKind_geometry_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GeometryType GeometryType(AbstractCurveKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCurveKind_length_3d", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern double Length3d(AbstractCurveKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCurveKind_compute_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* ComputeEnvelope(AbstractCurveKind* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_AbstractCurveKind_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(AbstractCurveKind* handle);
}