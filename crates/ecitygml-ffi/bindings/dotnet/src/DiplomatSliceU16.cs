using System.Runtime.InteropServices;

namespace Envis.Ecitygml.Diplomat;

[StructLayout(LayoutKind.Sequential)]
internal unsafe struct DiplomatSliceU16
{
    public char* Ptr;
    public nuint Len;
}