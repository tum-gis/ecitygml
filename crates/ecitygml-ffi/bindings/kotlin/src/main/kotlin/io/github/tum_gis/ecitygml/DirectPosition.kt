package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface DirectPositionLib: Library {
    fun ecitygml_DirectPosition_destroy(handle: Pointer)
    fun ecitygml_DirectPosition_new(x: Double, y: Double, z: Double): ResultPointerPointer
    fun ecitygml_DirectPosition_x(handle: Pointer): Double
    fun ecitygml_DirectPosition_y(handle: Pointer): Double
    fun ecitygml_DirectPosition_z(handle: Pointer): Double
}
/** A 3D coordinate, created or borrowed from a city model.
*/
class DirectPosition internal constructor (
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

    private class DirectPositionCleaner(val handle: Pointer, val lib: DirectPositionLib) : Runnable {
        override fun run() {
            lib.ecitygml_DirectPosition_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, DirectPosition.DirectPositionCleaner(handle, DirectPosition.lib));
    }

    companion object {
        internal val libClass: Class<DirectPositionLib> = DirectPositionLib::class.java
        internal val lib: DirectPositionLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** Creates a position; fails with `InvalidArgument` if a coordinate is NaN or infinite.
        */
        fun create(x: Double, y: Double, z: Double): Result<DirectPosition> {
            
            val returnVal = lib.ecitygml_DirectPosition_new(x, y, z);
            val nativeOkVal = returnVal.getNativeOk();
            if (nativeOkVal != null) {
                val selfEdges: List<Any> = listOf()
                val handle = nativeOkVal 
                val returnOpaque = DirectPosition(handle, selfEdges, true)
                return returnOpaque.ok()
            } else {
                val selfEdges: List<Any> = listOf()
                val handle = returnVal.getNativeErr()!! 
                val returnOpaque = Error(handle, selfEdges, true)
                return returnOpaque.err()
            }
        }
    }
    
    fun x(): Double {
        
        val returnVal = lib.ecitygml_DirectPosition_x(handle);
        return (returnVal)
    }
    
    fun y(): Double {
        
        val returnVal = lib.ecitygml_DirectPosition_y(handle);
        return (returnVal)
    }
    
    fun z(): Double {
        
        val returnVal = lib.ecitygml_DirectPosition_z(handle);
        return (returnVal)
    }

}