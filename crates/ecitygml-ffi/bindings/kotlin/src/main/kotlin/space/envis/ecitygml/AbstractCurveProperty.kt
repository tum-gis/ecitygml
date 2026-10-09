package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractCurvePropertyLib: Library {
    fun ecitygml_AbstractCurveProperty_destroy(handle: Pointer)
    fun ecitygml_AbstractCurveProperty_object(handle: Pointer): Pointer?
    fun ecitygml_AbstractCurveProperty_href(handle: Pointer): Pointer?
}
/** A curve property (inline curve and/or `xlink:href`), borrowed from a city model.
*/
class AbstractCurveProperty internal constructor (
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

    private class AbstractCurvePropertyCleaner(val handle: Pointer, val lib: AbstractCurvePropertyLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractCurveProperty_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractCurveProperty.AbstractCurvePropertyCleaner(handle, AbstractCurveProperty.lib));
    }

    companion object {
        internal val libClass: Class<AbstractCurvePropertyLib> = AbstractCurvePropertyLib::class.java
        internal val lib: AbstractCurvePropertyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** The inline curve; none if the property only references one via `href`.
    */
    fun object_(): AbstractCurveKind? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractCurveProperty_object(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractCurveKind(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun href(): HRef? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractCurveProperty_href(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HRef(handle, selfEdges, false)
        return returnOpaque
    }

}