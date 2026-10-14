using System;
using System.Runtime.InteropServices;
using Ecitygml;
using Ecitygml.Diplomat;

namespace Ecitygml.Raw;

[StructLayout(LayoutKind.Sequential)]
internal partial struct TransformationMatrix4x4
{

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TransformationMatrix4x4_get", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern DiplomatResultDoubleError Get(TransformationMatrix4x4* handle, nuint row, nuint column);

    [DllImport(DiplomatNativeLib.Name, EntryPoint = "ecitygml_TransformationMatrix4x4_destroy", CallingConvention = CallingConvention.Cdecl)]
    internal static unsafe extern void Destroy(TransformationMatrix4x4* handle);
}