using System.Runtime.InteropServices;

namespace Envis.Ecitygml.Diplomat;

// Shared native-library name for every `[DllImport]` in the raw layer.
// Emitted once per generation run so the iOS framework-bundle path and the
// bare name aren't duplicated into every `Raw*` struct.
internal static class DiplomatNativeLib
{
#if __IOS__
    internal const string Name = "libecitygml_ffi.framework/libecitygml_ffi";
#else
    internal const string Name = "ecitygml_ffi";
#endif
}