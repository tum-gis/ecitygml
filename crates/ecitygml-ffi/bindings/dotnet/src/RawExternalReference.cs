using System;
using System.Runtime.InteropServices;
using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

namespace Envis.Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct ExternalReference
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ExternalReference_target_resource", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatSliceU8 TargetResource(ExternalReference* handle);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_ExternalReference_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(ExternalReference* handle);
}