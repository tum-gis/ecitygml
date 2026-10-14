package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TransformationMatrix4x4Lib: Library {
    fun ecitygml_TransformationMatrix4x4_destroy(handle: Pointer)
    fun ecitygml_TransformationMatrix4x4_get(handle: Pointer, row: FFISizet, column: FFISizet): ResultDoublePointer
}
/** A 4x4 transformation matrix, borrowed from a city model.
*/
class TransformationMatrix4x4 internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal var owned: Boolean,
)  {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class TransformationMatrix4x4Cleaner(val handle: Pointer, val lib: TransformationMatrix4x4Lib) : Runnable {
        override fun run() {
            lib.ecitygml_TransformationMatrix4x4_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TransformationMatrix4x4.TransformationMatrix4x4Cleaner(handle, TransformationMatrix4x4.lib));
    }

    companion object {
        internal val libClass: Class<TransformationMatrix4x4Lib> = TransformationMatrix4x4Lib::class.java
        internal val lib: TransformationMatrix4x4Lib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The entry at `row` and `column` (0 to 3), as nalgebra's `matrix()[(row, column)]`; fails
    *with `InvalidArgument` instead of panicking above 3. Rust's `to_row_major()` returns a
    *`Vec`, which the Python backend can only return through NumPy.
    */
    fun get(row: ULong, column: ULong): Result<Double> {
        
        val returnVal = lib.ecitygml_TransformationMatrix4x4_get(handle, FFISizet(row), FFISizet(column));
        val nativeOkVal = returnVal.getNativeOk();
        if (nativeOkVal != null) {
            return (nativeOkVal).ok()
        } else {
            val selfEdges: List<Any> = listOf()
            val handle = returnVal.getNativeErr()!! 
            val returnOpaque = Error(handle, selfEdges, true)
            return returnOpaque.err()
        }
    }

}