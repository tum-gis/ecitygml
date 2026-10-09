using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct ImplicitGeometry
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ImplicitGeometry_object_id", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Id* ObjectId(ImplicitGeometry* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ImplicitGeometry_transformation_matrix", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern TransformationMatrix4x4* TransformationMatrix(ImplicitGeometry* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ImplicitGeometry_mime_type", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern MimeTypeValue* MimeType(ImplicitGeometry* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ImplicitGeometry_reference_point", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern PointProperty* ReferencePoint(ImplicitGeometry* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ImplicitGeometry_relative_geometry", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern AbstractGeometryProperty* RelativeGeometry(ImplicitGeometry* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ImplicitGeometry_compute_envelope", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern Envelope* ComputeEnvelope(ImplicitGeometry* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ImplicitGeometry_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(ImplicitGeometry* handle);
}