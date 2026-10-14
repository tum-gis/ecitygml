package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface BridgePartPropertyLib: Library {
    fun ecitygml_BridgePartProperty_destroy(handle: Pointer)
    fun ecitygml_BridgePartProperty_object(handle: Pointer): Pointer?
    fun ecitygml_BridgePartProperty_href(handle: Pointer): Pointer?
}
/** A bridge part property (inline bridge part and/or `xlink:href`), borrowed from a city model.
*/
class BridgePartProperty internal constructor (
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

    private class BridgePartPropertyCleaner(val handle: Pointer, val lib: BridgePartPropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_BridgePartProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, BridgePartProperty.BridgePartPropertyCleaner(handle, BridgePartProperty.lib));
    }

    companion object {
        internal val libClass: Class<BridgePartPropertyLib> = BridgePartPropertyLib::class.java
        internal val lib: BridgePartPropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline bridge part; none if the property only references one via `href`.
    */
    fun object_(): BridgePart? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BridgePartProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = BridgePart(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BridgePartProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}