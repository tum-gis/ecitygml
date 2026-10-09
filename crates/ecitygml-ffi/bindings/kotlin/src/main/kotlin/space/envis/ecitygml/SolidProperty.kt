package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface SolidPropertyLib: Library {
    fun ecitygml_SolidProperty_destroy(handle: Pointer)
    fun ecitygml_SolidProperty_object(handle: Pointer): Pointer?
    fun ecitygml_SolidProperty_href(handle: Pointer): Pointer?
}
/** A solid property (inline solid and/or `xlink:href`), borrowed from a city model.
*/
class SolidProperty internal constructor (
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

    private class SolidPropertyCleaner(val handle: Pointer, val lib: SolidPropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_SolidProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, SolidProperty.SolidPropertyCleaner(handle, SolidProperty.lib));
    }

    companion object {
        internal val libClass: Class<SolidPropertyLib> = SolidPropertyLib::class.java
        internal val lib: SolidPropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline solid; none if the property only references one via `href`.
    */
    fun object_(): Solid? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolidProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Solid(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolidProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}