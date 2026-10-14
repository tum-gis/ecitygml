package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface HeightLib: Library {
    fun ecitygml_Height_destroy(handle: Pointer)
    fun ecitygml_Height_high_reference(handle: Pointer): Pointer
    fun ecitygml_Height_low_reference(handle: Pointer): Pointer
    fun ecitygml_Height_status(handle: Pointer): Int
    fun ecitygml_Height_length(handle: Pointer): Pointer
}
/** A height of a construction between two reference levels, borrowed from a city model.
*/
class Height internal constructor (
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

    private class HeightCleaner(val handle: Pointer, val lib: HeightLib) : Runnable {
        override fun run() {
            lib.ecitygml_Height_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Height.HeightCleaner(handle, Height.lib));
    }

    companion object {
        internal val libClass: Class<HeightLib> = HeightLib::class.java
        internal val lib: HeightLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun highReference(): ElevationReferenceValue {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Height_high_reference(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = ElevationReferenceValue(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun lowReference(): ElevationReferenceValue {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Height_low_reference(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = ElevationReferenceValue(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun status(): HeightStatusValue {
        
        val returnVal = lib.ecitygml_Height_status(handle);
        return (HeightStatusValue.fromNative(returnVal))
    }
    
    /** The height value (`con:value`).
    */
    fun length(): Length {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Height_length(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Length(handle, selfEdges, false)
        return returnOpaque
    }

}