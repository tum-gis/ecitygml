package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TinPropertyLib: Library {
    fun ecitygml_TinProperty_destroy(handle: Pointer)
    fun ecitygml_TinProperty_object(handle: Pointer): Pointer?
    fun ecitygml_TinProperty_href(handle: Pointer): Pointer?
}
/** A TIN property (inline triangulated surface and/or `xlink:href`), borrowed from a city model.
*/
class TinProperty internal constructor (
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

    private class TinPropertyCleaner(val handle: Pointer, val lib: TinPropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_TinProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TinProperty.TinPropertyCleaner(handle, TinProperty.lib));
    }

    companion object {
        internal val libClass: Class<TinPropertyLib> = TinPropertyLib::class.java
        internal val lib: TinPropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline triangulated surface; none if the property only references one via `href`.
    */
    fun object_(): TriangulatedSurface? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TinProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = TriangulatedSurface(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TinProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}