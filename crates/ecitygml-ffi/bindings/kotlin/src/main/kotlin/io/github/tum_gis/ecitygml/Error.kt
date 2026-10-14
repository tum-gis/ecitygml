package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface ErrorLib: Library {
    fun ecitygml_Error_destroy(handle: Pointer)
    fun ecitygml_Error_kind(handle: Pointer): Int
    fun ecitygml_Error_message(handle: Pointer, write: Pointer): Unit
}
/** An error with its kind and a human-readable message.
*/
class Error internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal var owned: Boolean,
): Exception("Rust error result for Error")  {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class ErrorCleaner(val handle: Pointer, val lib: ErrorLib) : Runnable {
        override fun run() {
            lib.ecitygml_Error_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Error.ErrorCleaner(handle, Error.lib));
    }

    companion object {
        internal val libClass: Class<ErrorLib> = ErrorLib::class.java
        internal val lib: ErrorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun kind(): ErrorKind {
        
        val returnVal = lib.ecitygml_Error_kind(handle);
        return (ErrorKind.fromNative(returnVal))
    }
    
    fun message(): String {
        val write = DW.lib.diplomat_buffer_write_create(0)
        val returnVal = lib.ecitygml_Error_message(handle, write);
        
        val returnString = DW.writeToString(write)
        return returnString
    }

}