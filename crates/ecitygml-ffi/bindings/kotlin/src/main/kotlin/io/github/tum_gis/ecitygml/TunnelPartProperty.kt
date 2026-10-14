package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TunnelPartPropertyLib: Library {
    fun ecitygml_TunnelPartProperty_destroy(handle: Pointer)
    fun ecitygml_TunnelPartProperty_object(handle: Pointer): Pointer?
    fun ecitygml_TunnelPartProperty_href(handle: Pointer): Pointer?
}
/** A tunnel part property (inline tunnel part and/or `xlink:href`), borrowed from a city model.
*/
class TunnelPartProperty internal constructor (
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

    private class TunnelPartPropertyCleaner(val handle: Pointer, val lib: TunnelPartPropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_TunnelPartProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TunnelPartProperty.TunnelPartPropertyCleaner(handle, TunnelPartProperty.lib));
    }

    companion object {
        internal val libClass: Class<TunnelPartPropertyLib> = TunnelPartPropertyLib::class.java
        internal val lib: TunnelPartPropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline tunnel part; none if the property only references one via `href`.
    */
    fun object_(): TunnelPart? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TunnelPartProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = TunnelPart(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TunnelPartProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}