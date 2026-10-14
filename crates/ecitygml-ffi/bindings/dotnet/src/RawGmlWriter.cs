using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct GmlWriter
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GmlWriter_new", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern GmlWriter* create(CitygmlFormat format);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GmlWriter_from_path", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultGmlWriterError FromPath(DiplomatSliceU8 path);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GmlWriter_from_base_path_with_format", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultGmlWriterError FromBasePathWithFormat(DiplomatSliceU8 basePath, CitygmlFormat format);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GmlWriter_with_formatting", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void WithFormatting(GmlWriter* handle, Formatting* formatting);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GmlWriter_finish", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultVoidError Finish(GmlWriter* handle, CityModel* cityModel);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GmlWriter_data", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 Data(GmlWriter* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_GmlWriter_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(GmlWriter* handle);
}