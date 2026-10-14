using System.Runtime.InteropServices;

namespace Ecitygml.Diplomat;

[StructLayout(LayoutKind.Sequential)]
internal unsafe struct DiplomatSliceU32
{
    public uint* Ptr;
    public nuint Len;
}