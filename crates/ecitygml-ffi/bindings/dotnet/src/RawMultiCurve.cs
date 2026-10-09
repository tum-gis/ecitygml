using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct MultiCurve
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiCurve_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* Id(MultiCurve* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiCurve_names", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern CodeIterator* Names(MultiCurve* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiCurve_try_from", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MultiCurve* TryFrom(AbstractGeometryKind* geometry);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiCurve_curve_member", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractCurvePropertyIterator* CurveMember(MultiCurve* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiCurve_length_3d", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultDoubleError Length3d(MultiCurve* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiCurve_compute_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* ComputeEnvelope(MultiCurve* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_MultiCurve_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(MultiCurve* handle);
}