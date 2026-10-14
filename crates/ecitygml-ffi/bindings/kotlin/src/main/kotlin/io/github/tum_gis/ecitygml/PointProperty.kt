package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface PointPropertyLib: Library {
    fun ecitygml_PointProperty_destroy(handle: Pointer)
    fun ecitygml_PointProperty_object(handle: Pointer): Pointer?
    fun ecitygml_PointProperty_href(handle: Pointer): Pointer?
}
/** A point property (inline point and/or `xlink:href`), borrowed from a city model.
*/
class PointProperty internal constructor (
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

    private class PointPropertyCleaner(val handle: Pointer, val lib: PointPropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_PointProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, PointProperty.PointPropertyCleaner(handle, PointProperty.lib));
    }

    companion object {
        internal val libClass: Class<PointPropertyLib> = PointPropertyLib::class.java
        internal val lib: PointPropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline point; none if the property only references one via `href`.
    */
    fun object_(): Point? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_PointProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Point(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_PointProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}