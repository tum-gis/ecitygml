package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface HolePropertyLib: Library {
    fun ecitygml_HoleProperty_destroy(handle: Pointer)
    fun ecitygml_HoleProperty_object(handle: Pointer): Pointer?
    fun ecitygml_HoleProperty_href(handle: Pointer): Pointer?
}
/** A hole property (inline hole and/or `xlink:href`), borrowed from a city model.
*/
class HoleProperty internal constructor (
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

    private class HolePropertyCleaner(val handle: Pointer, val lib: HolePropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_HoleProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, HoleProperty.HolePropertyCleaner(handle, HoleProperty.lib));
    }

    companion object {
        internal val libClass: Class<HolePropertyLib> = HolePropertyLib::class.java
        internal val lib: HolePropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline hole; none if the property only references one via `href`.
    */
    fun object_(): Hole? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_HoleProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Hole(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_HoleProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}