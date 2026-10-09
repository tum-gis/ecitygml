using System;
using System.Runtime.InteropServices;

namespace Envis.Ecitygml.Raw;

using Envis.Ecitygml;
using Envis.Ecitygml.Diplomat;

[StructLayout(LayoutKind.Sequential)]
internal partial struct DiplomatResultVoidError
{
    [StructLayout(LayoutKind.Explicit)]
    private unsafe struct InnerUnion
    {
        [FieldOffset(0)] internal Error* err;
    }

    private InnerUnion _inner;

    public DiplomatBool IsOk;
    public unsafe Error* Err => !IsOk ? _inner.err : throw new InvalidOperationException("Result does not contain Err value");
}