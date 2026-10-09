package space.envis.ecitygml

import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface ErrorKindLib: Library {
}
/** Category of an [Error].
*/
enum class ErrorKind {
    InvalidArgument,
    Io,
    Parse,
    UnresolvedReference;

    fun toNative(): Int {
        return this.ordinal
    }


    companion object {
        internal val libClass: Class<ErrorKindLib> = ErrorKindLib::class.java
        internal val lib: ErrorKindLib = Native.load("ecitygml_ffi", libClass) 
        fun fromNative(native: Int): ErrorKind {
            return ErrorKind.entries[native]
        }

        fun default(): ErrorKind {
            return InvalidArgument
        }
    }
}
