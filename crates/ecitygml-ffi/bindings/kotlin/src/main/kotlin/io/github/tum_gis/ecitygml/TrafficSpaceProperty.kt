package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TrafficSpacePropertyLib: Library {
    fun ecitygml_TrafficSpaceProperty_destroy(handle: Pointer)
    fun ecitygml_TrafficSpaceProperty_object(handle: Pointer): Pointer?
    fun ecitygml_TrafficSpaceProperty_href(handle: Pointer): Pointer?
}
/** A traffic space property (inline traffic space and/or `xlink:href`), borrowed from a city model.
*/
class TrafficSpaceProperty internal constructor (
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

    private class TrafficSpacePropertyCleaner(val handle: Pointer, val lib: TrafficSpacePropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_TrafficSpaceProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TrafficSpaceProperty.TrafficSpacePropertyCleaner(handle, TrafficSpaceProperty.lib));
    }

    companion object {
        internal val libClass: Class<TrafficSpacePropertyLib> = TrafficSpacePropertyLib::class.java
        internal val lib: TrafficSpacePropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline traffic space; none if the property only references one via `href`.
    */
    fun object_(): TrafficSpace? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficSpaceProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = TrafficSpace(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficSpaceProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}