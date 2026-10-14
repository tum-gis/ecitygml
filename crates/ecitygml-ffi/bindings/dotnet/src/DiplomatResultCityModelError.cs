using System;
using System.Runtime.InteropServices;

namespace Ecitygml.Raw;

using Ecitygml;
using Ecitygml.Diplomat;

[StructLayout(LayoutKind.Sequential)]
internal partial struct DiplomatResultCityModelError
{
    [StructLayout(LayoutKind.Explicit)]
    private unsafe struct InnerUnion
    {
        [FieldOffset(0)] internal CityModel* ok;
        [FieldOffset(0)] internal Error* err;
    }

    private InnerUnion _inner;

    public DiplomatBool IsOk;
    public unsafe CityModel* Ok => IsOk ? _inner.ok : throw new InvalidOperationException("Result does not contain Ok value");
    public unsafe Error* Err => !IsOk ? _inner.err : throw new InvalidOperationException("Result does not contain Err value");
}