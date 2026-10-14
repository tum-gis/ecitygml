package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface MultiCurvePropertyLib: Library {
    fun ecitygml_MultiCurveProperty_destroy(handle: Pointer)
    fun ecitygml_MultiCurveProperty_object(handle: Pointer): Pointer?
    fun ecitygml_MultiCurveProperty_href(handle: Pointer): Pointer?
}
/** A multi-curve property (inline multi curve and/or `xlink:href`), borrowed from a city model.
*/
class MultiCurveProperty internal constructor (
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

    private class MultiCurvePropertyCleaner(val handle: Pointer, val lib: MultiCurvePropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_MultiCurveProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, MultiCurveProperty.MultiCurvePropertyCleaner(handle, MultiCurveProperty.lib));
    }

    companion object {
        internal val libClass: Class<MultiCurvePropertyLib> = MultiCurvePropertyLib::class.java
        internal val lib: MultiCurvePropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline multi curve; none if the property only references one via `href`.
    */
    fun object_(): MultiCurve? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_MultiCurveProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = MultiCurve(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_MultiCurveProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}